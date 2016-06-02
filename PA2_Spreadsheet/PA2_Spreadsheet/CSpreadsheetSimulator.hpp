//
//  CSpreadsheetSimulator.hpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#ifndef CSpreadsheetSimulator_hpp
#define CSpreadsheetSimulator_hpp

#include <stdio.h>
#include "CSheet.hpp"
#include "CScreen.hpp"

/**
 * @brief Class representing the application Spreadsheet Simulator.
 * @details It inicialises the application and handles the application run.
 */
class CSpreadsheetSimulator {
public:
    /**
     * @brief Constructor of the class.
     * @details
     */
    CSpreadsheetSimulator();
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CSpreadsheetSimulator();
    
    /**
     * @brief Runs the application.
     * @details
     */
    void Run();
    
private:
    CSheet * m_sheet;
    CScreen * m_screen;
};

#endif /* CSpreadsheetSimulator_hpp */
