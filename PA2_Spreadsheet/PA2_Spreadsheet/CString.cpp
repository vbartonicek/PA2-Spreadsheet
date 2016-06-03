//
//  CString.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CString.hpp"

CString::CString(){
    m_type = TYPE_STRING;
    m_show_value = "S" + to_string(rand() % 100);
    m_edit_value = "";
}

CString::~CString(){
    
}