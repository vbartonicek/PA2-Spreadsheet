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
#include <string>
#include <iostream>
#include <map>
#include <regex.h>
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
     * @param[in] rows How many rows will be created. Default value is 9
     */
    CSheet(const int columns = 10, const int rows = 9);
    
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
     * @brief Deletes cell on given position
     * @details Method to delete a Cell on specific column and row
     * @param[in] column Column number of requested cell
     * @param[in] row Row number of requested cell
     */
    void DeleteCell (const int column, const int row);
    
    /**
     * @brief Edit Number cell
     * @details Method to edit cell of Number type on specific position
     * @param[in] column Column number to specific cell position
     * @param[in] row Row number to specific cell position
     * @param[in] new_value A new value to save to the specific cell
     */
    void EditNumberCell (const int column, const int row, const char * new_value);
    
    /**
     * @brief Edit String cell
     * @details Method to edit cell of String type on specific position
     * @param[in] column Column number to specific cell position
     * @param[in] row Row number to specific cell position
     * @param[in] new_value A new value to save to the specific cell
     */
    void EditStringCell (const int column, const int row, const char * new_value);
    
    /**
     * @brief Edit Expression cell
     * @details Method to edit cell of Expression type on specific position
     * @param[in] column Column number to specific cell position
     * @param[in] row Row number to specific cell position
     * @param[in] new_value A new value to save to the specific cell
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
    
    /**
     * @brief Translates column name to column number
     * @details Method to provide column number by given column name (e.x. B -> 1)
     * @param[in] name Name of column
     * @return Returns index of the column
     */
    int GetColumnNumberByName(const char& name ) const;
    
    
    /**
     * @brief Checks if given position is valid
     * @details Method to check whether the given column and row numbers are valid ( = are inside the sheet)
     * @param[in] column Index of column
     * @param[in] row Index of row
     * @return Returns true if the position is valid or false if the position is invalid
     */
    bool isPositionValid (const int column, const int row) const;
    
    /**
     * @brief Get absolute value
     * @details Method to provide an absolute value of given number
     * @param[in] number Number to get an absolute number from
     * @return Returns the absolute number of given number
     */
    double ABS(const double& number) const;
    
    /**
     * @brief Get sinus value
     * @details Method to provide sinus value of given number
     * @param[in] number Number to get sinus value from
     * @return Returns the sinus value of given number
     */
    double SIN(const double& number) const;
    
    /**
     * @brief Get cosinus value
     * @details Method to provide cosinus value of given number
     * @param[in] number Number to get cosinus value from
     * @return Returns the cosinus value of given number
     */
    double COS(const double& number) const;
    
    /**
     * @brief Get tangens value
     * @details Method to provide tangens value of given number
     * @param[in] number Number to get tangens value from
     * @return Returns the tangens value of given number
     */
    double TAN(const double& number) const;
    
    /**
     * @brief Get random double value
     * @details Method to provide random double value
     * @return Returns the random double value
     */
    double RAND() const;
    
    /**
     * @brief Calculate sum value of numbers in given area
     * @details Method to calculate sum of all numbers and expressions in given area
     * @param[in] co1 Column index of first area edge
     * @param[in] ro1 Row index of first area edge
     * @param[in] co2 Column index of second area edge
     * @param[in] ro2 Row index of second area edge
     * @return Returns calculated sum value of given area
     */
    double SUM(const int& co1, const int& ro1,const int& co2, const int& ro2 ) const;
    
    /**
     * @brief Calculate average value of numbers in given area
     * @details Method to calculate average value of all numbers and expressions in given area
     * @param[in] co1 Column index of first area edge
     * @param[in] ro1 Row index of first area edge
     * @param[in] co2 Column index of second area edge
     * @param[in] ro2 Row index of second area edge
     * @return Returns calculated average value of given area
     */
    double AVG(const int& co1, const int& ro1,const int& co2, const int& ro2 ) const;

    /**
     * @brief Basic cell operation handler
     * @details Method to handle basic cell operations (e.g. =B1+C3)
     * @param[in] column Index of column
     * @param[in] row Index of row
     * @param[in] new_value Expression to handle
     */
    void HandleBasicCellOperation(const int column, const int row, const char * new_value);
    
    /**
     * @brief function handler
     * @details Method to handle functions (e.g. =ABS(B1))
     * @param[in] column Index of column
     * @param[in] row Index of row
     * @param[in] new_value Expression to handle
     */
    void HandleFunctionOperation(const int column, const int row, const char * new_value);
    
    /**
     * @brief Special function handler
     * @details Method to handle special functions (e.g. =AVG(A1:J9))
     * @param[in] column Index of column
     * @param[in] row Index of row
     * @param[in] new_value Expression to handle
     */
    void HandleFunctionSpecOperation(const int column, const int row, const char * new_value);
    
    /**
     * @brief Expressions recalculator
     * @details Method to recalculate all existing expressions
     */
    void RecalculateExpressions();
    
    
    /**
     * @brief Calculate total value of two given numbers
     * @details Method to provide total value of two given numbers
     * @param[in] number1 First number
     * @param[in] number2 Second number
     * @return Returns the calculated total value
     */
    double Total( const double& number1, const double& number2 ) const;
    
    /**
     * @brief Calculate difference value of two given numbers
     * @details Method to provide difference value of two given numbers
     * @param[in] number1 First number
     * @param[in] number2 Second number
     * @return Returns the calculated difference value
     */
    double Difference( const double& number1, const double& number2 ) const;
    
    /**
     * @brief Calculate product value of two given numbers
     * @details Method to provide product value of two given numbers
     * @param[in] number1 First number
     * @param[in] number2 Second number
     * @return Returns the calculated product value
     */
    double Product( const double& number1, const double& number2 ) const;
    
    /**
     * @brief Calculate division value of two given numbers
     * @details Method to provide division value of two given numbers
     * @param[in] number1 First number
     * @param[in] number2 Second number
     * @return Returns the calculated division value
     */
    double Division( const double& number1, const double& number2 ) const;
    
    /**
     * @brief Calculate modulo value of two given numbers
     * @details Method to provide modulo value of two given numbers
     * @param[in] number1 First number
     * @param[in] number2 Second number
     * @return Returns the calculated modulo value
     */
    double Modulo( const double& number1, const double& number2 ) const;
    
    /**
     * @brief Calculate power value of two given numbers
     * @details Method to provide power value of two given numbers
     * @param[in] number1 First number
     * @param[in] number2 Second number
     * @return Returns the calculated power value
     */
    double Power( const double& number1, const double& number2 ) const;
    
private:
    int m_columns;
    int m_rows;
    map < pair<int, int>, CCell * > m_sheet;
};

#endif /* CSheet_hpp */
