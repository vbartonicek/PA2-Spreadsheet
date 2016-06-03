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
#include <string>
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
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
    
private:
};

#endif /* CExpression_hpp */
