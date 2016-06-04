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