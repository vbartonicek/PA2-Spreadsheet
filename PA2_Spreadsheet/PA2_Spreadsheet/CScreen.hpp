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
#include <map>
#include <ncurses.h>

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
    
    void Print() const;
    
private:
    CSheet * m_sheet;
};

#endif /* CScreen_hpp */
