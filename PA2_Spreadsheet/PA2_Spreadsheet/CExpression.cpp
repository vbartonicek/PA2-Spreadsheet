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
    m_show_value = "";
    m_edit_value = "";
    m_processed = false;
}

CExpression::~CExpression(){
    
}

void CExpression::SetNumber(const double& newNumber){
    std::ostringstream ss;
    m_number  = newNumber;
    
    ss << m_number;
    std::string str = ss.str();
    SetShowValue(str);
}

void CExpression::SetNumber(const char * newNumber){
    m_number  = stoi(newNumber);
    
    SetShowValue(newNumber);
}

double CExpression::GetNumber() const {
    return m_number;
}

void CExpression::SetProcessed(const bool& newProcessed){
    m_processed = newProcessed;
}

bool CExpression::IsProcessed() const {
    return m_processed;
}