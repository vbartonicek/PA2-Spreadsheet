//
//  main.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CSpreadsheetSimulator.hpp"

/**
 * @mainpage PA2 Spreadsheet Simulator
 * @author Vratislav Bartonicek
 *
 * PA2 Spreadsheet Simulator is a basic spreadsheet simulator
 *
 *\n
 * CONTROLS:\n
 * Arrows - movement inside the sheet\n
 * F2 - Edit value of selected cell (and confirm by hitting ENTER button)\n
 * F3 - Delete value of selected cell\n
 * F4 - Exit\n
 * F5 - Show/hide help\n
 *\n
 *\n
 * FUNCTIONS:\n
 * AVG - Calculates average value of given area - e.g. =AVG(B1:F4)\n
 * SUM - Calculates sum value of given area - e.g. =SUM(B1:F4)\n
 *\n
 * SIN - Calculates sin value of given cell - e.g. =SIN(B1)\n
 * COS - Calculates cos value of given cell - e.g. =COS(B1)\n
 * TAN - Calculates tan value of given cell - e.g. =TAN(B1)\n
 * RAND - Returns pseudorandom number - e.g. =RAND()\n
 *\n
 * \+ - Summarize given cells - e.g. =B1+F4\n
 * \- - Deduct given cells - e.g. =B1-F4\n
 * \* - Multiply given cells - e.g. =B1*F4\n
 * / - Divide given cells - e.g. =B1/F4\n
 * % - Modular division of given cells - e.g. =B1%F4\n
 * ^ - Calculate power of twos given cells - e.g. =B1^F4\n
 */

int main(int argc, const char * argv[]) {

    CSpreadsheetSimulator application;
    application.Run();
    
    return 0;
}
