//
//  CNumber.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CNumber.hpp"

CNumber::CNumber(){
    m_type = TYPE_NUMBER;
    m_edit_value = "";
    m_show_value = m_edit_value;
}

CNumber::~CNumber(){
    
}