//
//  CString.hpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#ifndef CString_hpp
#define CString_hpp

#include <stdio.h>
#include <string>
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "CCell.hpp"

using namespace std;

class CString : public CCell {
public:
    /**
     * @brief Constructor of the class.
     * @details
     */
    CString();
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CString();
    
private:
};

#endif /* CString_hpp */
