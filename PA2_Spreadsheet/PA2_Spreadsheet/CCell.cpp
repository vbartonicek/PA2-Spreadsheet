//
//  CCell.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CCell.hpp"


CCell::CCell(){
    m_type = TYPE_NOTSET;
    m_show_value = "N" + to_string(rand() % 100);
    m_edit_value = "";
}

CCell::~CCell(){

}


void CCell::setShowValue(string new_show_value){
    m_show_value = new_show_value;
}

string CCell::getShowValue() const {
    return m_show_value;
}

void CCell::setEditValue(string new_edit_value){
    m_edit_value = new_edit_value;
}

string CCell::getEditValue() const {
    return m_edit_value;
}

//ostream& operator<< (ostream& os, const CCell& cell) {
//    os << cell.getShowValue();
//    return os;
//}