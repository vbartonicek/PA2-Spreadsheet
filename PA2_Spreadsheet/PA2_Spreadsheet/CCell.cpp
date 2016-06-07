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
    m_show_value = "";
    m_edit_value = "";
}

CCell::~CCell(){

}


void CCell::SetShowValue(string new_show_value){
    m_show_value = new_show_value;
}

string CCell::GetShowValue() const {
    return m_show_value;
}

void CCell::SetEditValue(string new_edit_value){
    m_edit_value = new_edit_value;
    SetShowValue(m_edit_value);
}

string CCell::GetEditValue() const {
    return m_edit_value;
}

int CCell::GetType() const {
    return m_type;
}

string CCell::GetTypeName() const {
    string name;
    
    switch (m_type){
        case TYPE_NOTSET:
            name = "NOTSET";
            break;
        case TYPE_NUMBER:
            name = "NUMBER";
            break;
        case TYPE_STRING:
            name = "STRING";
            break;
        case TYPE_EXPRESSION:
            name = "EXPRESSION";
            break;
        default:
            name = "UNKNOWN";
            break;
    }
    
    return name;
}

//ostream& operator<< (ostream& os, const CCell& cell) {
//    os << cell.getShowValue();
//    return os;
//}
