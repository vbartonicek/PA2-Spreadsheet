//
//  CSheet.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CSheet.hpp"

CSheet::CSheet(const int columns, const int rows){
    m_columns = columns;
    m_rows = rows;
    
    // Column
    for ( int column = 0; column != m_columns; column++){
        // Row
        for ( int row = 0; row != m_rows; row++){
            CCell * newCell = new CCell;
            m_sheet[make_pair(column,row)] = newCell;
        }
    }
}

CSheet::~CSheet(){
    // deleting all CCell objects
    for ( map < pair<int, int>, CCell * >::iterator it = m_sheet.begin(); it != m_sheet.end(); it++ ){
        delete it->second;
    }
    
}

CCell * CSheet::GetCell (const int column, const int row) const{
    return m_sheet.at( make_pair(column,row) );

}

void CSheet::DeleteCell (const int column, const int row) {
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_NOTSET ) {
        delete m_sheet.at( make_pair(column, row));
        CCell * newCell = new CCell;
        m_sheet[make_pair(column,row)] = newCell;
    }
}

void CSheet::EditNumberCell (const int column, const int row, const char * new_value){
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_NUMBER ) {
        delete m_sheet.at( make_pair(column, row));
        CNumber * newCell = new CNumber;
        m_sheet[make_pair(column,row)] = newCell;
    }
    
    CCell* cell  = m_sheet.at( make_pair(column, row));
    CNumber* number = dynamic_cast<CNumber *>(cell);
    number->SetNumber(new_value);
}

void CSheet::EditStringCell (const int column, const int row, const char * new_value){
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_STRING ) {
        delete m_sheet.at( make_pair(column, row));
        CString * newCell = new CString;
        m_sheet[make_pair(column,row)] = newCell;
    }
    
    m_sheet.at( make_pair(column, row))->SetEditValue(new_value);
}

void CSheet::EditExpressionCell (const int column, const int row, const char * new_value){
    
    regex_t basic_op_exp;
    regex_t function_exp;
    regex_t function_special_exp;
    regex_t rand_exp;
    
    regcomp(&basic_op_exp, "^=[A-J][1-9].[A-J][1-9]$", REG_EXTENDED);
    regcomp(&function_exp, "^=(ABS|SIN|COS|TAN)\\([A-J][1-9]\\)$", REG_EXTENDED);
    regcomp(&function_special_exp, "^=(SUM|AVG)\\([A-J][1-9]:[A-J][1-9]\\)$", REG_EXTENDED);
    regcomp(&rand_exp, "^=RAND\\(\\)$", REG_EXTENDED);
    
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_EXPRESSION ) {
        delete m_sheet.at( make_pair(column, row));
        CExpression * newCell = new CExpression;
        m_sheet[make_pair(column,row)] = newCell;
    }
    
    string str(new_value);
    
    // BASIC Expression CELL op CELL
    if ( !regexec(&basic_op_exp, new_value, 0, NULL, 0) ) {
        HandleBasicCellOperation(column, row, new_value);
        return;
    }
    
    // RAND
    else if ( !regexec(&rand_exp, new_value, 0, NULL, 0) ) {
        CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
        CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
        expression->SetEditValue(str);
        expression->SetNumber(RAND());
        expression->SetProcessed(true);
        return;
    }
    
    // ABS SIN COS TAN (cell)
    else if ( !regexec(&function_exp, new_value, 0, NULL, 0) ) {
        HandleFunctionOperation(column, row, new_value);
        return;
    }
    // SUM AVG (cell:cell)
    else if ( !regexec(&function_special_exp, new_value, 0, NULL, 0) ) {
        HandleFunctionSpecOperation(column, row, new_value);
        return;
    }

    else {
    m_sheet.at( make_pair(column, row))->SetEditValue("NaN - Wrong syntax");
    }
}


void CSheet::HandleBasicCellOperation(const int column, const int row, const char * new_value){
    string str(new_value);
    double number1;
    double number2;
    
    int co1 = GetColumnNumberByName(new_value[1]);
    int ro1 = new_value[2] - '0' -1;
    int co2 = GetColumnNumberByName(new_value[4]);
    int ro2 = new_value[5] - '0' -1;
    
    // dependency
    if (m_sheet.at( make_pair(column, row))->isDependent(co1, co2) || m_sheet.at( make_pair(column, row))->isDependent(co1, co2)) {
        delete m_sheet.at( make_pair(column, row));
        CNumber * newCell = new CNumber;
        m_sheet[make_pair(column,row)] = newCell;
        newCell->SetNumber(0.0);
        
        return;
    } else m_sheet.at( make_pair(column, row))->clearDependencies();
        
    CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
    CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
    
    if ( !isPositionValid(co1, ro1) || !isPositionValid(co2, ro2)) {
        expression->SetEditValue("NaN - Wrong cell position");
        return;
    }
    
    auto cell1 =m_sheet.at( make_pair(co1, ro1));
    auto cell2 =m_sheet.at( make_pair(co2, ro2));
    
    if (cell1->GetType() == TYPE_NUMBER){
        number1 = dynamic_cast<CNumber *> (cell1)->GetNumber();
    }
    else if (cell1->GetType() == TYPE_EXPRESSION && dynamic_cast<CExpression *>(cell1)->IsProcessed()){
        number1 = stod(cell1->GetShowValue());
    }
    else {
        expression->SetEditValue("NaN - Cell must be number");
        return;
    }
    
    if (cell2->GetType() == TYPE_NUMBER){
        number2 = dynamic_cast<CNumber *> (cell2)->GetNumber();
    }
    else if (cell2->GetType() == TYPE_EXPRESSION && dynamic_cast<CExpression *>(cell2)->IsProcessed()){
        number2 = stod(cell2->GetShowValue());
    }
    else {
        expression->SetEditValue("NaN - Cell must be number");
        return;
    }
    
    expression->SetEditValue(str);
    
    switch ( str.at(3) )
    {
        case '+':
            expression->SetNumber(Total(number1, number2));
            break;
        case '-':
            expression->SetNumber(Difference(number1, number2));
            break;
        case '/':
            expression->SetNumber(Division(number1, number2));
            break;
        case '*':
            expression->SetNumber(Product(number1, number2));
            break;
        case '%':
            expression->SetNumber(Modulo(number1, number2));
            break;
        case '^':
            expression->SetNumber(Power(number1, number2));
            break;
        default:
            expression->SetEditValue("NaN - Wrong operand");
            return;
    }
    
    expression->setDependency(co1, ro1);
    expression->setDependency(co2, ro2);
    expression->SetProcessed(true);
    
    return;
}

void CSheet::HandleFunctionOperation(const int column, const int row, const char * new_value){
    string str(new_value);
    string functionName = str.substr(1,3);
    double number;
    
    int co = GetColumnNumberByName(new_value[5]);
    int ro = new_value[6] - '0' -1;
    
    // dependency
    if (m_sheet.at( make_pair(column, row))->isDependent(co, co)) {
        delete m_sheet.at( make_pair(column, row));
        CNumber * newCell = new CNumber;
        m_sheet[make_pair(column,row)] = newCell;
        newCell->SetNumber(0.0);
        
        return;
    } else m_sheet.at( make_pair(column, row))->clearDependencies();
    
    CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
    CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
    
    if ( !isPositionValid(co, ro)) {
        expression->SetEditValue("NaN - Wrong cell position");
        return;
    }
    
    auto cell =m_sheet.at( make_pair(co, ro));
    
    if (cell->GetType() == TYPE_NUMBER){
        number = dynamic_cast<CNumber *> (cell)->GetNumber();
    }
    else if (cell->GetType() == TYPE_EXPRESSION && dynamic_cast<CExpression *>(cell)->IsProcessed()){
        number = stod(cell->GetShowValue());
    }
    else {
        expression->SetEditValue("NaN - Cell must be number");
        return;
    }
    
    expression->SetEditValue(str);
    if ( functionName == "ABS" ) expression->SetNumber(ABS(number));
    else if ( functionName == "SIN" ) expression->SetNumber(SIN(number));
    else if ( functionName == "COS" ) expression->SetNumber(COS(number));
    else if ( functionName == "TAN" ) expression->SetNumber(TAN(number));
    else {
        expression->SetEditValue("NaN - Wrong function");
        return;
    }
    
    expression->setDependency(co, ro);
    expression->SetProcessed(true);

    return;
}

void CSheet::HandleFunctionSpecOperation(const int column, const int row, const char * new_value){
    string str(new_value);
    string functionName = str.substr(1,3);
    
    int co1 = GetColumnNumberByName(new_value[5]);
    int ro1 = new_value[6] - '0' -1;
    
    int co2 = GetColumnNumberByName(new_value[8]);
    int ro2 = new_value[9] - '0' -1;
    
    // dependency
    if (m_sheet.at( make_pair(column, row))->isDependent(co1, co2) || m_sheet.at( make_pair(column, row))->isDependent(co1, co2)) {
        delete m_sheet.at( make_pair(column, row));
        CNumber * newCell = new CNumber;
        m_sheet[make_pair(column,row)] = newCell;
        newCell->SetNumber(0.0);
        
        return;
    } else m_sheet.at( make_pair(column, row))->clearDependencies();
    
    CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
    CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
    expression->SetProcessed(false);
    
    if ( !isPositionValid(co1, ro1) || !isPositionValid(co2, ro2)) {
        expression->SetEditValue("NaN - Wrong cell position");
        return;
    }

    expression->SetEditValue(str);
    if ( functionName == "SUM" ) expression->SetNumber(SUM(co1, ro1, co2, ro2));
    else if ( functionName == "AVG" ) expression->SetNumber(AVG(co1, ro1, co2, ro2));
    else {
        expression->SetEditValue("NaN - Wrong function");
        return;
    }
    
    expression->setDependency(co1, ro1);
    expression->setDependency(co2, ro2);
    expression->SetProcessed(true);
    
    return;
}

void CSheet::RecalculateExpressions(){
    regex_t rand_exp;
    regcomp(&rand_exp, "^=RAND\\(\\)$", REG_EXTENDED);
    
    for (int col = 0; col < m_columns; col++){
        
        for (int row = 0; row < m_rows; row++){
            auto cell = m_sheet.at( make_pair(col, row));
            if ( cell->GetType() == TYPE_EXPRESSION && dynamic_cast<CExpression *>(cell)->IsProcessed() ) {
                const char * edit_value = cell->GetEditValue().c_str();
                if ( !regexec(&rand_exp, edit_value, 0, NULL, 0)) continue;
                EditExpressionCell(col, row, cell->GetEditValue().c_str());
            }
        }
    }
    
}


int CSheet::getColumns() const{
    return m_columns;
}

int CSheet::getRows() const{
    return m_rows;
}

bool CSheet::isPositionValid (const int column, const int row) const {

    if (column < 0 || column > (m_columns - 1) || row < 0 || row > (m_rows - 1)) {
        return false;
    }
    else return true;
}

int CSheet::GetColumnNumberByName(const char& name) const {
    int x = name;
    x -= 65;
    //printf("NUMBER of %c = %d",name, x);
    return x;
}


double CSheet::ABS(const double& number) const {
    if (number < 0) return (-1) * number;
    else return number;
}

double CSheet::SIN(const double& number) const {
    return sin( number );
}

double CSheet::COS(const double& number) const {
    return cos( number );
}

double CSheet::TAN(const double& number) const {
    return tan( number );
}

double CSheet::RAND() const {
    return (double)rand();
}

double CSheet::SUM(const int& co1, const int& ro1,const int& co2, const int& ro2 ) const {
    double sum = 0;
    int col_start;
    int row_start;
    
    int col_end;
    int row_end;

    if ( co1 < co2) {
        col_start = co1;
        col_end = co2;
    }
    else  {
        col_start = co2;
        col_end = co1;
    }
    
    if ( ro1 < ro2) {
        row_start = ro1;
        row_end = ro2;
    }
    else  {
        row_start = ro2;
        row_end = ro1;
    }
    
    
    for (int col = col_start; col <= col_end; col++){
    
        for (int row = row_start; row <= row_end; row++){
            auto cell = m_sheet.at( make_pair(col, row));
            if ( cell->GetType() == TYPE_NUMBER ) {
                sum += stod( cell->GetShowValue() );
            }
            else if ( cell->GetType() == TYPE_EXPRESSION && dynamic_cast<CExpression *>(cell)->IsProcessed() ) {
                sum += stod( cell->GetShowValue() );
            }
        }
    }
    
    
    return sum;
}

double CSheet::AVG(const int& co1, const int& ro1,const int& co2, const int& ro2 ) const {
    double sum = 0;
    int count = 0;
    int col_start;
    int row_start;
    
    int col_end;
    int row_end;
    
    
    if ( co1 < co2) {
        col_start = co1;
        col_end = co2;
    }
    else  {
        col_start = co2;
        col_end = co1;
    }
    
    if ( ro1 < ro2) {
        row_start = ro1;
        row_end = ro2;
    }
    else  {
        row_start = ro2;
        row_end = ro1;
    }
    
    
    for (int col = col_start; col <= col_end; col++){
        
        for (int row = row_start; row <= row_end; row++){
            auto cell = m_sheet.at( make_pair(col, row));
            if ( cell->GetType() == TYPE_NUMBER ) {
                sum += stod( cell->GetShowValue() );
                count++;
            }
            else if ( cell->GetType() == TYPE_EXPRESSION && dynamic_cast<CExpression *>(cell)->IsProcessed() ) {
                sum += stod( cell->GetShowValue() );
                count++;
            }
        }
    }
    
    
    return (sum / count);
}

double CSheet::Total( const double& number1, const double& number2 ) const {
    return number1 + number2;
}

double CSheet::Difference( const double& number1, const double& number2 ) const {
    return number1 - number2;
}

double CSheet::Product( const double& number1, const double& number2 ) const {
    return number1 * number2;
}

double CSheet::Division( const double& number1, const double& number2 ) const {
    return number1 / number2;
}

double CSheet::Modulo( const double& number1, const double& number2 ) const {
    return fmod(number1, number2);
}

double CSheet::Power( const double& number1, const double& number2 ) const {
    return pow (number1, number2);
}
