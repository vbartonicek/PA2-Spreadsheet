//
//  CScreen.hpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#ifndef CScreen_hpp
#define CScreen_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <regex>
#include <ncurses.h>
#include <iostream>

#define REGEX_NUMBER "-?[0-9]+(\\.?[0-9]+)?"
#define REGEX_EXPRESSION "^=[A-Z0-9\\(\\):\\+\\*-/////ˆ%]*"

#include "CSheet.hpp"

using namespace std;

/**
 * @brief Class representing screen.
 * @details It handles the screen and user's input
 */
class CScreen {
public:
    /**
     * @brief Constructor of the class.
     * @details
     */
    CScreen(CSheet * sheet);
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CScreen();
    
    
    /**
     * @brief Screen manager
     * @details Handles the screen cycle and reacts to user's inputs
     */
    void ScreenManager();
    
    /**
     * @brief Table lines printer
     * @details Method to print the table lines
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void PrintTable(const int& x_start, const int& y_start) const;
    
    /**
     * @brief Table header printer
     * @details Method to print the table headers
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void PrintHeaders(const int& x_start, const int& y_start) const;
    
    /**
     * @brief Cell printer
     * @details Method to print the cell values
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void PrintValues(const int& x_start, const int& y_start) const;
    
    /**
     * @brief Status printer
     * @details Method to print the current status of the table
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void PrintStatus(const int& x_start, const int& y_start) const;
    
    /**
     * @brief Edit instructions printer
     * @details Method to print the edit instructions
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void PrintEditInstructions(const int& x_start, const int& y_start) const;
    
    
    /**
     * @brief Edit instructions cleaner
     * @details Method to hide the edit instructions
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void ClearEditInstructions(const int& x_start, const int& y_start) const;
    
    /**
     * @brief Help printer
     * @details Method to print the help information
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void PrintHelp(const int& x_start, const int& y_start) const;
    
    
    /**
     * @brief Help printer
     * @details Method to print the help information
     * @param[in] x_start Top left table corner
     * @param[in] y_start Bottom right table corner
     */
    void ClearHelp(const int& x_start, const int& y_start) const;
    
    /**
     * @brief Window closer
     * @details Closes the used Window
     */
    void CloseWindow() const;
    
    /**
     * @brief Cell input handler
     * @details Method to handle user's input to edit a cell
     */
    void HandleCellInput ();
    
    /**
     * @brief Set Column Position to right
     * @details Method to move cursor to right
     */
    void SetColumnPositionNext();
    
    /**
     * @brief Set Column Position to left
     * @details Method to move cursor to left
     */
    void SetColumnPositionPrevious();
    
    /**
     * @brief Get column position
     * @details Method to return the number of current column
     * @return Returns the current column number
     */
    int GetColumnPosition() const;
    
    /**
     * @brief Get name for column number
     * @details Method to translate column position to column name
     * @param[in] x_number Column number to translate
     * @return Returns the column name
     */
    char GetColumnName(const int& number) const;
    
    
    /**
     * @brief Set Row Position to down
     * @details Method to move cursor down
     */
    void SetRowPositionNext();
    
    /**
     * @brief Set Row Position to up
     * @details Method to move cursor up
     */
    void SetRowPositionPrevious();
    
    /**
     * @brief Get row position
     * @details Method to return the number of current row
     * @return Returns the current row number
     */
    int GetRowPosition() const;
    
private:
    CSheet * m_sheet;
    int m_curr_column;
    int m_curr_row;
};

#endif /* CScreen_hpp */
