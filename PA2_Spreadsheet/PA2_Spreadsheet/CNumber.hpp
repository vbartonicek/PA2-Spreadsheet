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
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
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
    
private:
};

#endif /* CNumber_hpp */
