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
#include <map>
#include <sstream>
#include <set>
#include "CCell.hpp"

using namespace std;

/**
 * @brief Class representing single cell of Expression type.
 * @details It stores expression data.
 */
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
    
    /**
     * @brief Set number value of the cell
     * @details Method to set value of the processed expression
     * @param[in] newNumber New number to set
     */
    void SetNumber(const double& newNumber);
    
    /**
     * @brief Set number value of the cell
     * @details Method to set value of the processed expression
     * @param[in] newNumber New number to set
     */
    void SetNumber(const char * newNumber);
    
    /**
     * @brief Set status of the expression
     * @details Method to set the status of the expression
     * @param[in] newProcessed New status to set
     */
    void SetProcessed(const bool& newProcessed);
    
    /**
     * @brief Get the status of expression
     * @details Method to return the expression status
     * @return Returns the expression status
     */
    bool IsProcessed() const;
    
    /**
     * @brief Get calculated number value
     * @details Method to provide value of calculated number
     * @return Returns the number value of the expression
     */
    double GetNumber() const;
    
private:
    double m_number;
    bool m_processed;
};

#endif /* CExpression_hpp */
