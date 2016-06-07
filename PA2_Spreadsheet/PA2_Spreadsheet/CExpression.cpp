//
//  CExpression.cpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#include "CExpression.hpp"


#define REGEX_NUMBER "-?[0-9]+(\\.?[0-9]+)?"
#define REGEX_OPERATOR "[\\/\\%\\*\\+-]" // options: / % * + -
#define REGEX_EXPRESSION "^=[A-Z0-9\\(\\):\\+\\*-/////ˆ%]*"
#define REGEX_CELL "[A-J][1-9]"
#define REGEX_SPECIAL "[():]"
#define REGEX_FUNCTION "(ABS)|(SIN)|(COS)|(TAN)|(RAN)|(SIN)"

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
}

void CExpression::SetNumber(const char * newNumber){
    m_number  = stoi(newNumber);
    
    SetShowValue(newNumber);
}

long long CExpression::GetNumber() const {
    return m_number;
}

bool CExpression::Validate() const {
    //string stringToValidate = GetShowValue();
    regex test_regex(REGEX_FUNCTION);
    
    string stringToValidate = "=SIN";
    
    // Delete all white spaces
    stringToValidate.erase( std::remove_if( stringToValidate.begin(), stringToValidate.end(), ::isspace ), stringToValidate.end() );
    
    // Check if expression starts with = and remove it
    if ( stringToValidate.at(0) != '=' ) return false;
    stringToValidate.erase ( stringToValidate.begin() );
    
    string test = "=SIN (B1)";
    regex regRep(REGEX_CELL);
    test = regex_replace(test, regRep, "253");
    cout << "test = |" <<  test << "|" << endl;
    
    
    if ( regex_match(stringToValidate, test_regex) ) {
        cout << "v poho" << endl;
    }
    else cout << "neni validni" << endl;
    
    cout << "Validating: |" << stringToValidate << "|" << endl;
    //if ( )
    
    return true;
}