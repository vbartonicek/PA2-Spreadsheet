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

void CSheet::Print() const{
    // Column
    for ( int column = 0; column != m_columns; column++){
        // Row
        for ( int row = 0; row != m_rows; row++){
            //cout << m_sheet.at(make_pair(column,row)) << ",\t" << endl;
        }
        printf("\n");
    }
}


CCell * CSheet::GetCell (const int column, const int row) const{
    return m_sheet.at( make_pair(column,row) );

}

void CSheet::EditNumberCell (const int column, const int row, const char * new_value){
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_NUMBER ) {
        delete m_sheet.at( make_pair(column, row));
        CNumber * newCell = new CNumber;
        m_sheet[make_pair(column,row)] = newCell;
    }
    
    m_sheet.at( make_pair(column, row))->SetEditValue(new_value);
}

void CSheet::EditStringCell (const int column, const int row, const char * new_value){
    if ( m_sheet.at( make_pair(column, row))->GetType() != TYPE_STRING ) {
        delete m_sheet.at( make_pair(column, row));
        CString * newCell = new CString;
        m_sheet[make_pair(column,row)] = newCell;
    }
    
    m_sheet.at( make_pair(column, row))->SetEditValue(new_value);
}

int CSheet::getColumns() const{
    return m_columns;
}

int CSheet::getRows() const{
    return m_rows;
}