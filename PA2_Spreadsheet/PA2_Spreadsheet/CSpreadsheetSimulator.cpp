//
//  CSpreadsheetSimulator.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CSpreadsheetSimulator.hpp"


CSpreadsheetSimulator::CSpreadsheetSimulator(){
    m_sheet = new CSheet();
    m_screen = new CScreen(m_sheet);
}

CSpreadsheetSimulator::~CSpreadsheetSimulator(){
    delete m_screen;
    delete m_sheet;
}

void CSpreadsheetSimulator::Run(){
    m_screen->ScreenManager();
}
