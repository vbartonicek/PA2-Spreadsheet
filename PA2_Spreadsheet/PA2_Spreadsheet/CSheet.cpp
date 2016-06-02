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
            m_sheet[make_pair(column,row)] = column + row + column * row;
        }
    }
}

CSheet::~CSheet(){
    
}

void CSheet::Print() const{
    // Column
    for ( int column = 0; column != m_columns; column++){
        // Row
        for ( int row = 0; row != m_rows; row++){
            printf("%d,\t", m_sheet.at(make_pair(column,row)));
        }
        printf("\n");
    }
}


int CSheet::GetCell (const int column, const int row) const{
    return m_sheet.at( make_pair(column,row) );

}

void CSheet::EditCell (const int column, const int row, const int new_value){

}

int CSheet::getColumns() const{
    return m_columns;
}

int CSheet::getRows() const{
    return m_rows;
}