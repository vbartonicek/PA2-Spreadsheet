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

    regex basic_op_regex("^=[A-J][1-9].[A-J][1-9]$");
    regex function_regex("^=(ABS|SIN|COS|TAN)\\([A-J][1-9]\\)$");
    regex function_special_regex("^=(SUM|AVG)\\([A-J][1-9]:[A-J][1-9]\\)$");
    regex rand_regex("^=RAND\\(\\)$");
    
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_EXPRESSION ) {
        delete m_sheet.at( make_pair(column, row));
        CExpression * newCell = new CExpression;
        m_sheet[make_pair(column,row)] = newCell;
    }
    
    string str(new_value);
    
    // BASIC Expression CELL op CELL
    if ( regex_match(str, basic_op_regex) ) {
        HandleBasicCellOperation(column, row, new_value);
        return;
    }
    
    // RAND
    else if ( regex_match(str, rand_regex) ) {
        dynamic_cast<CNumber*>(m_sheet.at( make_pair(column, row)))->SetNumber(RAND());
        return;
    }
    
    // ABS SIN COS TAN (cell)
    else if ( regex_match(str, basic_op_regex) ) {
        HandleFunctionOperation(column, row, new_value);
        return;
    }
    // SUM AVG (cell:cell)
    else if ( regex_match(str, function_special_regex) ) {
        HandleFunctionSpecOperation(column, row, new_value);
        return;
    }

    else m_sheet.at( make_pair(column, row))->SetEditValue("NaN - Wrong syntax");
}


void CSheet::HandleBasicCellOperation(const int column, const int row, const char * new_value){
    string str(new_value);
    CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
    CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
    
    int co1 = GetColumnNumberByName(new_value[1]);
    int ro1 = new_value[2] - '0' -1;
    int co2 = GetColumnNumberByName(new_value[4]);
    int ro2 = new_value[5] - '0' -1;
    
    if ( !isPositionValid(co1, ro1) || !isPositionValid(co2, ro2)) {
        expression->SetEditValue("NaN - Wrong cell position");
        return;
    }
    
    if (m_sheet.at( make_pair(co1, ro1))->GetTypeName() != "NUMBER" || m_sheet.at( make_pair(co2, ro2))->GetTypeName() != "NUMBER" ){
        expression->SetEditValue("NaN - Both cells must be numbers");
        return;
    }
    
    auto number1 = dynamic_cast<CNumber *>( m_sheet.at( make_pair(co1, ro1)));
    auto number2 = dynamic_cast<CNumber *>( m_sheet.at( make_pair(co2, ro2)));
    
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
    
    return;
}

void CSheet::HandleFunctionOperation(const int column, const int row, const char * new_value){
    string str(new_value);
    string functionName = str.substr(1,3);
    CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
    CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
    
    int co = GetColumnNumberByName(new_value[5]);
    int ro = new_value[6] - '0' -1;
    
    if ( !isPositionValid(co, ro)) {
        expression->SetEditValue("NaN - Wrong cell position");
        return;
    }
    
    if (m_sheet.at( make_pair(co, ro))->GetTypeName() != "NUMBER"){
        expression->SetEditValue("NaN - Both cells must be numbers");
        return;
    }
    
    auto number = dynamic_cast<CNumber *>( m_sheet.at( make_pair(co, ro)));
    
    
    expression->SetEditValue(str);
    if ( functionName == "ABS" ) expression->SetNumber(ABS(number));
    else if ( functionName == "SIN" ) expression->SetNumber(SIN(number));
    else if ( functionName == "COS" ) expression->SetNumber(COS(number));
    else if ( functionName == "TAN" ) expression->SetNumber(TAN(number));
    else expression->SetEditValue("NaN - Wrong function");
    
    return;
}

void CSheet::HandleFunctionSpecOperation(const int column, const int row, const char * new_value){
    string str(new_value);
    string functionName = str.substr(1,3);
    CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
    CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
    
    //0123456789
    //=SUM(B1:C2)
    
    int co1 = GetColumnNumberByName(new_value[5]);
    int ro1 = new_value[6] - '0' -1;
    
    int co2 = GetColumnNumberByName(new_value[8]);
    int ro2 = new_value[9] - '0' -1;
    
    if ( !isPositionValid(co1, ro1) || !isPositionValid(co2, ro2)) {
        expression->SetEditValue("NaN - Wrong cell position");
        return;
    }

    expression->SetEditValue(str);
    if ( functionName == "SUM" ) expression->SetNumber(SUM(co1, ro1, co2, ro2));
    else if ( functionName == "AVG" ) expression->SetNumber(AVG(co1, ro1, co2, ro2));
    else expression->SetEditValue("NaN - Wrong function");
    
    return;
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


long long CSheet::ABS(const CNumber * number) const {
    if (number->GetNumber() < 0) return (-1) * number->GetNumber();
    else return number->GetNumber();
}

long long CSheet::SIN(const CNumber * number) const {
    return sin( number->GetNumber() );
}

long long CSheet::COS(const CNumber * number) const {
    return cos( number->GetNumber() );
}

long long CSheet::TAN(const CNumber * number) const {
    return tan( number->GetNumber() );
}

long long CSheet::RAND() const {
    return rand();
}

long long CSheet::SUM(const int& co1, const int& ro1,const int& co2, const int& ro2 ) const {
    long long sum = 0;
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
            if ( m_sheet.at( make_pair(col, row))->GetTypeName() == "NUMBER" ) sum += stoi( m_sheet.at( make_pair(col, row))->GetShowValue() );
        }
    }
    
    
    return sum;
}

long long CSheet::AVG(const int& co1, const int& ro1,const int& co2, const int& ro2 ) const {
    long long sum = 0;
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
            if ( m_sheet.at( make_pair(col, row))->GetTypeName() == "NUMBER" ) {
                sum += stoi( m_sheet.at( make_pair(col, row))->GetShowValue() );
                count++;
            }
        }
    }
    
    
    return (sum / count);
}

long long CSheet::Total( const CNumber * number1, const CNumber * number2) const {
    return number1->GetNumber() + number2->GetNumber();
}

long long CSheet::Difference( const CNumber * number1, const CNumber * number2) const {
    return number1->GetNumber() - number2->GetNumber();
}

long long CSheet::Product( const CNumber * number1, const CNumber * number2) const {
    return number1->GetNumber() * number2->GetNumber();
}

long long CSheet::Division( const CNumber * number1, const CNumber * number2) const {
    return number1->GetNumber() / number2->GetNumber();
}

long long CSheet::Modulo( const CNumber * number1, const CNumber * number2) const {
    return number1->GetNumber() % number2->GetNumber();
}

long long CSheet::Power( const CNumber * number1, const CNumber * number2) const {
    return pow (number1->GetNumber(), number2->GetNumber());
}
