//
//  CExpression.hpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#ifndef CExpression_hpp
#define CExpression_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <regex>
#include "CCell.hpp"

using namespace std;

class CExpression : public CCell {
public:
    /**
     * @brief Constructor of the class.
     * @details
     */
    CExpression();
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CExpression();
    
    void SetNumber(const double& newNumber);
    void SetNumber(const char * newNumber);
    
    bool Validate() const;
    
    void SetProcessed(const bool& newProcessed);
    bool IsProcessed() const;
    
    double GetNumber() const;
    
private:
    double m_number;
    bool m_processed;
};

#endif /* CExpression_hpp */
