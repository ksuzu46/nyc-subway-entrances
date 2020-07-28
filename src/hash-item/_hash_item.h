/******************************************************************************
  Title          : _hash_item.h
  Author         : Stewart Weiss
  Created on     : March 31, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     :
  Modifications  :
     4/4/2019 by SW - Added a code() member function
     4/30/2019 by Keisuke Suzuki - Added a parametrized constructor
******************************************************************************/

#ifndef __HASH_ITEM_H__
#define __HASH_ITEM_H__

#include <string>
#include <climits>
#include <ostream>

using namespace std;

class __ItemType
{
    public:
    /** __ItemType is a default constructor
     *  @param none
     */
    __ItemType();
    
    /** __ItemType is a parametrized constructor
     *  @param string s
     */
    explicit __ItemType(string s, int= -1);
    
    /** set() sets the item's data
     *  @param string s
     */
    void set(string s, int= -1);
    
    /** get() retrieves the item's data
     *  @param string
     *  @param int
     */
    void get(string &, int &);
    
    /** operator==() returns true if given parameter equal item
     *  @precondition: rhs is initialized
     *  @param  __ItemType [in] rhs : item to compare
     *  @return bool 0 if rhs is not equal, 1 if it is.
     */
    bool operator ==(const __ItemType &rhs) const;
    
    /** operator!=() returns true if given parameter is not equal item
     *  @precondition: rhs is initialized
     *  @param  __ItemType [in] rhs : item to compare
     *  @return bool 1 if rhs is not equal, 0 if it is.
     */
    bool operator !=(const __ItemType &rhs) const;
    
    /** code() returns an unsigned integer for the item
     *  @note Every item, regardless of its key type, should be mapped
     *        to a positive integer value. If the key is a string, this
     *        assigns a number to the string. If it is a number already, this
     *        has the option to assign a different number.
     *  @precondition: item is initialized
     *  @return unsigned int
     */
    unsigned int code() const;
    
    /** operator<<()
     *  @precondition: none
     *  @param os, item
     *  @return os
     */
    friend ostream &operator <<(ostream &os, const __ItemType &item);
    
    private:
    string key; //a private member of string
    int data{};   //a private member of int
};

#endif /* __HASH_ITEM_H__ */

