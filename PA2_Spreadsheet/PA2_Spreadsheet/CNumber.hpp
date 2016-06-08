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

/**
 * @brief Class representing single cell of Number type.
 * @details It stores number data.
 */
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
    
    /**
     * @brief Set number value of the cell
     * @details Method to set number value of the cell
     * @param[in] newNumber New number to set
     */
    void SetNumber(const double& newNumber);
    
    /**
     * @brief Set number value of the cell
     * @details Method to set number value of the cell
     * @param[in] newNumber New number to set
     */
    void SetNumber(const char * newNumber);
    
    /**
     * @brief Get number value of the cell
     * @details Method to get number value of the cell
     * @return Returns the number value;
     */
    double GetNumber() const;
    
private:
    double m_number;
};

#endif /* CNumber_hpp */
