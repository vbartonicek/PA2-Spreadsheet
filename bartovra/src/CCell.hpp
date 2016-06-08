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


/**
 * @brief Class representing single cell.
 * @details It stores cell data.
 */
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
    virtual ~CCell();
    
    /**
     * @brief Set cell show value
     * @details Method to set the show value of the cell
     * @param[in] new_show_value New show value of the cell
     */
    virtual void SetShowValue(string new_show_value);
    
    /**
     * @brief Get show value
     * @details Method to provide show value of the cell
     * @return Returns show value of the cell
     */
    string GetShowValue() const;
    
    /**
     * @brief Set cell edit value
     * @details Method to set the edit value of the cell
     * @param[in] new_edit_value New edit value of the cell
     */
    virtual void SetEditValue(string new_edit_value);
    
    /**
     * @brief Get edit value
     * @details Method to provide edit value of the cell
     * @return Returns edit value of the cell
     */
    string GetEditValue() const;

    /**
     * @brief Get cell type
     * @details Method to provide type of the cell
     * @return Returns the cell type
     */
    int GetType() const;
    
    /**
     * @brief Get cell type name
     * @details Method to provide type name of the cell
     * @return Returns the name of cell type
     */
    string GetTypeName() const;
    
    
    /**
     * @brief Set cell to be dependent on given cell
     * @details Method to add dependency on cell described by given value
     * @param[in] col Column of cell to add to dependency container
     * @param[in] row Row of cell to add to dependency container
     */
    void setDependency(const int& col, const int& row);
    
    /**
     * @brief Dependency check
     * @details Method to check whether the cell is dependent on Cell on given position
     * @param[in] col Column of cell to check
     * @param[in] row Row of cell to check
     * @return Returns true if cells are dependent. If not it returns false
     */
    bool isDependent(const int& col, const int& row);
    
    /**
     * @brief Empty the dependencies container
     * @details Method to clear all records in the dependencies container
     */
    void clearDependencies();
    
protected:
    int m_type;
    string m_show_value;
    string m_edit_value;
    set < pair<int, int> > m_dependencies;
private:
    
};

#endif /* CCell_hpp */
