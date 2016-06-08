//
//  CScreen.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 02/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CScreen.hpp"
#include <string.h>

CScreen::CScreen(CSheet * sheet){
    m_sheet = sheet;
    m_curr_column = 0;
    m_curr_row = 0;
}

CScreen::~CScreen(){
    
}


void CScreen::ScreenManager() {
    int c = 0;
    int x_start = 0;
    int y_start = 0;
    int screenSize_x;
    int screenSize_y;
    bool help = false;
    
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    
    PrintTable(x_start, y_start);
    PrintHeaders(x_start, y_start);
    ClearHelp(x_start, y_start);
    
    while (1){
        getmaxyx(stdscr, screenSize_x, screenSize_y);
        while ( screenSize_x < (x_start + 30) || screenSize_y < (y_start + 110)) {
            clear();
            mvprintw(0,0,"Screen must be a least %dx%d\n",(y_start + 110),(x_start + 30));
            refresh();
            getmaxyx(stdscr, screenSize_x, screenSize_y);
        }
        PrintValues(x_start, y_start);
        PrintStatus(x_start, y_start);
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
            case KEY_F(5):
                if ( help ) ClearHelp(x_start, y_start);
                else PrintHelp(x_start, y_start);
                help = ! help;
                break;
            case KEY_F(2):
                PrintEditInstructions(x_start, y_start);
                HandleCellInput();
                ClearEditInstructions(x_start, y_start);
                break;
            case KEY_F(3):
                m_sheet->DeleteCell(m_curr_column, m_curr_row);
                break;
            case KEY_F(4):
                CloseWindow();
                return;
            default:
                break;
                
        }
        
    }
    //mvprintw(y_start + 3, x_start + 20,"123456789");
}

void CScreen::PrintTable(const int& x_start, const int& y_start) const {
    // HORIZONTAL LINES
    attron(COLOR_PAIR(2));
    move(y_start, x_start + 0);
    hline(0, 110);
    move(y_start + 2, x_start + 1);
    hline(0, 109);
    attroff(COLOR_PAIR(2));
    
    // inner lines
    for (int i = 1; i != m_sheet->getRows(); i++){
        move(y_start + 2 + 2 * i , x_start + 10);
        hline(0, 100);
    }
    
    attron(COLOR_PAIR(2));
    move(y_start + 2 + 2 * m_sheet->getRows() , x_start + 0);
    hline(0, 110);
    attroff(COLOR_PAIR(2));
    
    //HEADER HORIZONTAL INNER LINES
    attron(COLOR_PAIR(1));
    for (int i = 1; i != m_sheet->getRows(); i++){
        move(y_start + 2 + 2 * i , x_start + 1);
        hline(0, 8);
    }
    attroff(COLOR_PAIR(1));
    
    
    // VERTICAL LINES
    attron(COLOR_PAIR(2));
    move(y_start + 1, x_start + 0);
    vline(0, 19);
    move(y_start + 1, x_start + 9);
    vline(0, 19);
    attroff(COLOR_PAIR(2));
    
    // inner lines
    for (int i = 1; i != m_sheet->getColumns(); i++){
        move(y_start + 2 , x_start + 9 + 10 * i);
        vline(0, 18);
    }
    
    attron(COLOR_PAIR(2));
    move(y_start + 1 , x_start + 9 + 10 * m_sheet->getColumns());
    vline(0, 19);
    attroff(COLOR_PAIR(2));
    
    
    //HEADER VERTICAL INNER LINES
    attron(COLOR_PAIR(1));
    for (int i = 1; i != m_sheet->getColumns(); i++){
        move(y_start + 1 , x_start + 9 + 10 * i);
        vline(0, 1);
    }
    attroff(COLOR_PAIR(1));
}

void CScreen::PrintHeaders(const int& x_start, const int& y_start) const {
    
    // COLUMN HEADERS
    attron(COLOR_PAIR(1));
    for (int i = 0; i != m_sheet->getColumns(); i++){
        mvprintw(y_start + 1, x_start + 10 + 10 * i,"    %c    ", GetColumnName(i));
    }
    attroff(COLOR_PAIR(1));
    
    // ROW HEADERS
    attron(COLOR_PAIR(1));
    for (int i = 1; i != m_sheet->getRows() + 1; i++){
        if (i < 10) mvprintw(y_start + 1 + 2 * i, x_start + 1," ROW  %d ", i);
        else if (i < 100) mvprintw(y_start + 1 + 2 * i, x_start + 1," ROW %d ", i);
        else mvprintw(y_start + 1 + 2 * i, x_start + 1," ROW >< ");
    }
    attroff(COLOR_PAIR(1));

}

void CScreen::PrintValues(const int& x_start, const int& y_start) const {
    string value;
    
    m_sheet->RecalculateExpressions();
    
    for (int row = 0; row != m_sheet->getRows(); row++)
    {
        for (int col = 0; col != m_sheet->getColumns(); col++)
        {
            if (GetColumnPosition() == col && GetRowPosition() == row) attron(COLOR_PAIR(1));
            value = m_sheet->GetCell(col, row)->GetShowValue();
            
            
            if (value.length() > 9) {
                mvprintw(y_start + 3 + 2 * row, x_start + 10 + 10 * col,"%c%c%c%c%c ...", value[0],value[1],value[2],value[3],value[4]);
            }
            else {
                unsigned int i;
                for ( i = 0; i != (9 - value.length()); i++ ) {
                    mvprintw(y_start + 3 + 2 * row, x_start + 10 + (int) i + 10 * col," ");
                }
            
                for ( unsigned int j = 0; j != value.length(); j++ ) {
                    mvprintw(y_start + 3 + 2 * row, x_start + 10 + (int) i + (int) j + 10 * col,"%c", value[j]);
                }
            }
            
            if (GetColumnPosition() == col && GetRowPosition() == row) attroff(COLOR_PAIR(1));
        }
        
    }
}

void CScreen::PrintStatus(const int& x_start, const int& y_start) const{
    
    move(y_start + 3 + 2 * m_sheet->getRows() , x_start + 0);
    
    attron(A_BOLD);
    printw("Position: ");
    attroff(A_BOLD);
    printw("%c%d\n", GetColumnName(GetColumnPosition()), GetRowPosition() + 1);
    
    attron(A_BOLD);
    printw("Value: ");
    attroff(A_BOLD);
    printw("%s\n", m_sheet->GetCell(GetColumnPosition(), GetRowPosition())->GetShowValue().c_str());
    
    attron(A_BOLD);
    printw("Expression: ");
    attroff(A_BOLD);
    printw("%s\n", m_sheet->GetCell(GetColumnPosition(), GetRowPosition())->GetEditValue().c_str());

    attron(A_BOLD);
    printw("Type: ");
    attroff(A_BOLD);
    printw("%s\n\n", m_sheet->GetCell(GetColumnPosition(), GetRowPosition())->GetTypeName().c_str());

}

void CScreen::PrintEditInstructions(const int& x_start, const int& y_start) const{
    move(y_start + 8 + 2 * m_sheet->getRows() , x_start + 0);
    attron(A_BOLD);
    printw("Insert new value: ");
    attroff(A_BOLD);
}

void CScreen::ClearEditInstructions(const int& x_start, const int& y_start) const{
    move(y_start + 8 + 2 * m_sheet->getRows() , x_start + 0);
    clrtoeol();
}


void CScreen::PrintHelp(const int& x_start, const int& y_start) const{
    move(y_start + 10 + 2 * m_sheet->getRows() , x_start + 0);
    clrtoeol();
    attron(A_BOLD);
    printw("HELP\n");
    attroff(A_BOLD);
    printw("F5 - Hide help\t\tF2 - Edit cell\t\tF3 - Exit\t Arrows - movement");
}

void CScreen::ClearHelp(const int& x_start, const int& y_start) const{
    move(y_start + 10 + 2 * m_sheet->getRows() , x_start + 0);
    clrtoeol();
    printw("For help press F5");
    move(y_start + 11 + 2 * m_sheet->getRows() , x_start + 0);
    clrtoeol();
}

void CScreen::CloseWindow() const {
    endwin();
}

void CScreen::HandleCellInput() {
    char str [1000];
    
    regex_t num_regex_exp;
    regex_t num_expression_exp;
    
    regcomp(&num_regex_exp, REGEX_NUMBER, REG_EXTENDED);
    regcomp(&num_expression_exp, REGEX_EXPRESSION, REG_EXTENDED);
    
    
    getstr(str);
    
    if ( strlen(str) > 99){
        printw("WRONG INPUT\n");
        return;
    }
    else if ( !regexec(&num_regex_exp, str, 0, NULL, 0) ){
        // NUMBER
        m_sheet->EditNumberCell(m_curr_column, m_curr_row, str);
    }
    else if ( !regexec(&num_expression_exp, str, 0, NULL, 0) ){
        // EXPRESSION CANDIDATE
        m_sheet->EditExpressionCell(m_curr_column, m_curr_row, str);
    }
    else {
        // STRING
        if ( str[0] == '=' ) m_sheet->EditExpressionCell(m_curr_column, m_curr_row, "NaN");
        else m_sheet->EditStringCell(m_curr_column, m_curr_row, str);
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
