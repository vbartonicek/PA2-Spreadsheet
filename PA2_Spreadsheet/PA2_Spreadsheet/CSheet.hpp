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
#include <regex>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
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
     * @param[in] columns How many columns will be created. Default value is 10
     * @param[in] rows How many rows will be created. Default value is 10
     */
    CSheet(const int columns = 10, const int rows = 10);
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CSheet();
    
    /**
     * @brief Get cell on specific position
     * @details Method to provide a Cell on specific column and row
     * @param[in] column Column number of requested cell
     * @param[in] row Row number of requested cell
     * @return Returns the requested cell
     */
    CCell * GetCell (const int column, const int row) const;
    
    /**
     * @brief Edit Number cell
     * @details Method to edit cell of Number type on specific position
     * @param[in] column Column number to specific cell position
     * @param[in] row Row number to specific cell position
     * @param[in] new_Value A new value to save to the specific cell
     */
    void EditNumberCell (const int column, const int row, const char * new_value);
    
    /**
     * @brief Edit String cell
     * @details Method to edit cell of String type on specific position
     * @param[in] column Column number to specific cell position
     * @param[in] row Row number to specific cell position
     * @param[in] new_Value A new value to save to the specific cell
     */
    void EditStringCell (const int column, const int row, const char * new_value);
    
    /**
     * @brief Edit Expression cell
     * @details Method to edit cell of Expression type on specific position
     * @param[in] column Column number to specific cell position
     * @param[in] row Row number to specific cell position
     * @param[in] new_Value A new value to save to the specific cell
     */
    void EditExpressionCell (const int column, const int row, const char * new_value);
    
    /**
     * @brief Get number of sheet columns
     * @details Method to provide number of sheet columns
     * @return Returns the number of columns
     */
    int getColumns() const;
    
    /**
     * @brief Get number of sheet rows
     * @details Method to provide number of sheet rows
     * @return Returns the number of rows
     */
    int getRows() const;
    
    int GetColumnNumberByName(const char& name ) const;
    
    long long ABS(const CNumber * number) const;
    long long SIN(const CNumber * number) const;
    long long COS(const CNumber * number) const;
    long long TAN(const CNumber * number) const;
    long long RAND() const;
    
    
private:
    int m_columns;
    int m_rows;
    map < pair<int, int>, CCell * > m_sheet;
};

#endif /* CSheet_hpp */
