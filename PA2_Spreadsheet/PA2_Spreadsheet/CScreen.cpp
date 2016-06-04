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
    m_curr_column = 0;
    m_curr_row = 0;
}

CScreen::~CScreen(){
    
}

void CScreen::ScreenManager() {
    int c = 0;
    
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    
    while (1){
        PrintHeader();
        PrintSheet();
        PrintStatus();
        refresh();
        c = getch();
        
        switch (c){
            case KEY_DOWN:
                SetRowPositionNext();
                break;
            case KEY_UP:
                SetRowPositionPrevious();
                break;
            case KEY_LEFT:
                SetColumnPositionPrevious();
                break;
            case KEY_RIGHT:
                SetColumnPositionNext();
                break;
            case KEY_F(2):
                PrintEditInstructions();
                HandleCellInput();
                break;
            case KEY_F(3):
                CloseWindow();
                return;
            default:
                break;
        
        }
        //if (getch() == "q") break;
    };
}

void CScreen::PrintHeader() const{
    attron(A_BOLD);
    mvprintw(0,35,"SPREADSHEET SIMULATOR\n");
    attroff(A_BOLD);
    printw("\n");
}

void CScreen::PrintSheet() const{
    
    //header
    attron(A_UNDERLINE);
    attron(A_BOLD);
    for (int col = 0; col!= m_sheet->getColumns(); col++)
    {
        addch('\t');
        printw("  ");
        printw("%c",GetColumnName(col));
        addch(A_ALTCHARSET);
    }
    addch('\t');
    addch(' ');
    attroff(A_BOLD);
    printw("\n");
    
    //table
    
    for (int row = 0; row!= m_sheet->getRows(); row++)
    {
        attron(A_BOLD);
        printw("ROW %d\t", row + 1);
        attroff(A_BOLD);
        for (int col = 0; col!= m_sheet->getColumns(); col++)
        {
            addch(ACS_VLINE);
            if (GetColumnPosition() == col && GetRowPosition() == row) attron(COLOR_PAIR(1));
            printw(" ");
            printw("%s", m_sheet->GetCell(col, row)->GetShowValue().c_str());
            addch(A_ALTCHARSET);
            addch('\t');
            if (GetColumnPosition() == col && GetRowPosition() == row) attroff(COLOR_PAIR(1));
        }
        addch(ACS_VLINE);
        printw("\n");
    }
    attroff(A_UNDERLINE);
}

void CScreen::PrintStatus() const{
    printw("\n");
    
    attron(A_BOLD);
    mvprintw(15,2,"Position: ");
    attroff(A_BOLD);
    printw("%c%d\n", GetColumnName(GetColumnPosition()), GetRowPosition() + 1);
    
    attron(A_BOLD);
    mvprintw(17,2,"Value: ");
    attroff(A_BOLD);
    printw("%s\n", m_sheet->GetCell(GetColumnPosition(), GetRowPosition())->GetShowValue().c_str());
    
    attron(A_BOLD);
    mvprintw(19,2,"Expression: ");
    attroff(A_BOLD);
    printw("%s\n\n", m_sheet->GetCell(GetColumnPosition(), GetRowPosition())->GetEditValue().c_str());
    
    
    attron(A_BOLD);
    mvprintw(20,2,"Type: ");
    attroff(A_BOLD);
    printw("%s\n\n", m_sheet->GetCell(GetColumnPosition(), GetRowPosition())->GetTypeName().c_str());

}

void CScreen::PrintEditInstructions() const{
    attron(A_BOLD);
    printw("Insert new value: ");
    attroff(A_BOLD);
}

void CScreen::CloseWindow() const {
    endwin();
}

void CScreen::HandleCellInput() {
    char str [100];
    getstr(str);
    
    if ( str[0] == '=') {
        printw("EXPRESSION Candidate: %s\n", str);
        return;
    }
    else {
        int i = 0;
        
        while (str[i]){
            if (i == 99) {
                printw("WRONG INPUT\n");
                return;
            }
            
            if ( !isdigit(str[i]) ) {
                while (str[i]){
                    if (i == 99) {
                        printw("WRONG INPUT\n");
                        return;
                    }
                    
                    if ( !isalnum(str[i]) ) {
                        printw("WRONG INPUT\n");
                        return;
                    }
                    i++;
                }
                // STRING
                m_sheet->EditStringCell(m_curr_column, m_curr_row, str);
                //printw("STRING\n");
                return;
            }
            i++;
        }
        // NUMBER
        m_sheet->EditNumberCell(m_curr_column, m_curr_row, str);
        //printw("NUMBER\n");
        return;
    }
    
}

void CScreen::SetColumnPositionNext() {
    if (m_curr_column + 1 < m_sheet->getColumns()) m_curr_column++;
}

void CScreen::SetColumnPositionPrevious(){
    if (m_curr_column > 1) m_curr_column--;
    else m_curr_column = 0;
}

int CScreen::GetColumnPosition() const {
    return m_curr_column;
}

char CScreen::GetColumnName(const int& number) const {
    char letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[number];
    return letter;
}

void CScreen::SetRowPositionNext() {
    if (m_curr_row + 1 < m_sheet->getRows()) m_curr_row++;
}

void CScreen::SetRowPositionPrevious(){
    if (m_curr_row> 1) m_curr_row--;
    else m_curr_row = 0;
}

int CScreen::GetRowPosition() const {
    return m_curr_row;
}