//
//  CScreen.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CScreen.hpp"

CScreen::CScreen(CSheet * sheet){
    m_sheet = sheet;
}

CScreen::~CScreen(){
    
}

void CScreen::Print() const{
    
    initscr();
    curs_set(0);
    attron(A_UNDERLINE);
    mvprintw(0,35,"SPREADSHEET SIMULATOR\n");
    printw("\n\t");
    
    
    //header
    attron(A_UNDERLINE);
    for (int col = 0; col!= m_sheet->getColumns(); col++)
    {
        printw("  ");
        char letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[col];
        printw("%c",letter);
        addch(A_ALTCHARSET);
        addch('\t');
    }
    printw(" ");
    printw("\n");
    
    //table
    
    for (int row = 0; row!= m_sheet->getRows(); row++)
    {
        attron(A_UNDERLINE);
        
        printw("ROW %d\t", row + 1);
        for (int col = 0; col!= m_sheet->getColumns(); col++)
        {
            addch(ACS_VLINE);
            printw(" ");
            printw("%s", m_sheet->GetCell(col, row)->getShowValue().c_str());
            addch(A_ALTCHARSET);
            addch('\t');
        }
        addch(ACS_VLINE);
        printw("\n");
    }
    getch();
    endwin();
}