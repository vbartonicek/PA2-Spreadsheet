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
#include <ncurses.h>
#include <iostream>

#include "CSheet.hpp"

using namespace std;

/**
 * @brief Class representing sheet.
 * @details It stores sheet data.
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
    
    void ScreenManager();
    void PrintTable(const int& x_start, const int& y_start) const;
    void PrintHeaders(const int& x_start, const int& y_start) const;
    void PrintValues(const int& x_start, const int& y_start) const;
    void PrintStatus(const int& x_start, const int& y_start) const;
    
    void PrintEditInstructions(const int& x_start, const int& y_start) const;
    void CloseWindow() const;
    
    void HandleCellInput ();
    
    void SetColumnPositionNext();
    void SetColumnPositionPrevious();
    int GetColumnPosition() const;
    char GetColumnName(const int& number) const;
    
    void SetRowPositionNext();
    void SetRowPositionPrevious();
    int GetRowPosition() const;
    
private:
    CSheet * m_sheet;
    int m_curr_column;
    int m_curr_row;
};

#endif /* CScreen_hpp */
