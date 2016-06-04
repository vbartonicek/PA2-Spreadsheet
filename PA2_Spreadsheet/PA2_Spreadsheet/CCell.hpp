//
//  CCell.hpp
//  PA2_Spreadsheet
//
//  Created by Vratislav Bartonicek on 03/06/16.
//  Copyright © 2016 Vratislav Bartonicek. All rights reserved.
//

#ifndef CCell_hpp
#define CCell_hpp

#include <stdio.h>
#include <string>
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define TYPE_NOTSET 0
#define TYPE_NUMBER 1
#define TYPE_STRING 2
#define TYPE_EXPRESSION 3

using namespace std;

class CCell {
public:
    /**
     * @brief Constructor of the class.
     * @details
     */
    CCell();
    
    /**
     * @brief Destructor of the class.
     * @details
     */
    ~CCell();
    
    virtual void SetShowValue(string new_show_value);
    string GetShowValue() const;
    
    void SetEditValue(string new_edit_value);
    string GetEditValue() const;
    
    int GetType() const;
    string GetTypeName() const;
    
    // TODO Methods for dependencies
    
protected:
    //friend ostream& operator<< (ostream& os, const CCell& cell);
    int m_type;
    string m_show_value;
    string m_edit_value;
    set <CCell *> m_dependencies;
private:
    
};

#endif /* CCell_hpp */