//
//  CNumber.hpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#ifndef CNumber_hpp
#define CNumber_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <set>
#include "CCell.hpp"

using namespace std;

class CNumber : public CCell {
public:
    /**
     * @brief Constructor of the class.
     * @details
     */
    CNumber();
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CNumber();
    
    void SetNumber(const long long& newNumber);
    void SetNumber(const char * newNumber);
    
    long long GetNumber() const;
    
private:
    long long m_number;
};

#endif /* CNumber_hpp */
