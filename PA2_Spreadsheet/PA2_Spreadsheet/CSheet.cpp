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
    regex abs_regex("=ABS\\([A-J][1-9]\\)");
    regex sin_regex("=SIN\\([A-J][1-9]\\)");
    regex cos_regex("=COS\\([A-J][1-9]\\)");
    regex tan_regex("=TAN\\([A-J][1-9]\\)");
    regex rand_regex("=RAND\\(\\)");

    
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_EXPRESSION ) {
        delete m_sheet.at( make_pair(column, row));
        CExpression * newCell = new CExpression;
        m_sheet[make_pair(column,row)] = newCell;
    }
    
        string str(new_value);
    
    if ( regex_match(str, rand_regex) ) {
        dynamic_cast<CExpression *>(m_sheet.at( make_pair(column, row)))->SetNumber(RAND());
        return;
    }
    
    int co = GetColumnNumberByName(new_value[5]);
    int ro = new_value[6] - '0' -1;
    auto number = dynamic_cast<CNumber *>( m_sheet.at( make_pair(co, ro)));
    //cout << "CHECK01 = " << number->GetNumber() << endl;
    CCell* cellToEdit  = m_sheet.at( make_pair(column, row));
    CExpression* expression = dynamic_cast<CExpression *>(cellToEdit);
    
    if ( regex_match(str, abs_regex) ) {
        expression->SetNumber(ABS(number));
    } else if ( regex_match(str, sin_regex) ) {
        expression->SetNumber(SIN(number));
    } else if ( regex_match(str, cos_regex) ) {
        expression->SetNumber(COS(number));
    } else if ( regex_match(str, tan_regex) ) {
        expression->SetNumber(TAN(number));
    }
    else m_sheet.at( make_pair(column, row))->SetEditValue(new_value);
}

int CSheet::getColumns() const{
    return m_columns;
}

int CSheet::getRows() const{
    return m_rows;
}

int CSheet::GetColumnNumberByName(const char& name) const {
    int x = name;
    x -= 65;
    printf("NUMBER of %c = %d",name, x);
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