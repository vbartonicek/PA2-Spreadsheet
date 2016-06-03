//
//  CSheet.hpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#ifndef CSheet_hpp
#define CSheet_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include "CCell.hpp"
#include "CString.hpp"
#include "CNumber.hpp"
#include "CExpression.hpp"

using namespace std;

/**
 * @brief Class representing sheet.
 * @details It stores sheet data.
 */
class CSheet {
public:
    /**
     * @brief Constructor of the class.
     * @details
     */
    CSheet(const int columns = 10, const int rows = 10);
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CSheet();
    
    
    CCell * GetCell (const int column, const int row) const;
    void EditCell (const int column, const int row, const int new_value);
    
    int getColumns() const;
    int getRows() const;
    
    void Print() const;

private:
    int m_columns;
    int m_rows;
    map < pair<int, int>, CCell * > m_sheet;
};

#endif /* CSheet_hpp */
