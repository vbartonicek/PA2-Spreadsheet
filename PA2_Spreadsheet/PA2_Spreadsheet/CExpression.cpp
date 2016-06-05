//
//  CExpression.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CExpression.hpp"

CExpression::CExpression(){
    m_type = TYPE_EXPRESSION;
    m_show_value = "EXP";
    m_edit_value = "Not processed";
}

CExpression::~CExpression(){
    
}

void CExpression::SetNumber(const long long& newNumber){
    std::ostringstream ss;
    m_number  = newNumber;
    
    ss << m_number;
    std::string str = ss.str();
    SetShowValue(str);
    SetEditValue(str);
}

void CExpression::SetNumber(const char * newNumber){
    m_number  = stoi(newNumber);
    
    SetShowValue(newNumber);
}

long long CExpression::GetNumber() const {
    return m_number;
}