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

void CNumber::SetNumber(const double& newNumber){
    std::ostringstream ss;
    m_number  = newNumber;
    
    ss << m_number;
    std::string str = ss.str();
    SetShowValue(str);
    SetEditValue(str);
}

void CNumber::SetNumber(const char * newNumber){
    m_number  = stod(newNumber);
    
    SetShowValue(newNumber);
    SetEditValue(newNumber);
}

double CNumber::GetNumber() const {
    return m_number;
}
