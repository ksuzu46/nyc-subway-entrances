/******************************************************************************
  Title          : hash_table.cpp
  Author         : Keisuke Suzuki
  Created on     : March 31, 2019
  Description    : Implementation for a class __ItemType
  Purpose        : To implement a class __ItemType

******************************************************************************/

#include "_hash_item.h"
#include <iostream>


/***************function prototypes for helper functions**********************/

/** toLower() returns string only with lower charactors
 *  @param string
 *  @precondition non
 *  @postcondition return string has only lower charactors
 *  @return string with only lower charactors
 */
string toLower(const string &);



/************public methods **************************************************/

__ItemType::__ItemType()=default;

void __ItemType::set(string s, int _data){
    key=s;
    data=_data;
}

void __ItemType::get( string &_key, int &_data){
    _key=key;
    _data=data;
}

bool __ItemType::operator==( const __ItemType& rhs) const{
    return toLower(key)==toLower(rhs.key);
}


bool __ItemType::operator!=( const __ItemType& rhs) const{
    return key!=rhs.key;
}


unsigned int __ItemType::code() const{
    //using ullong in case the value gets too large
    unsigned long long hashVal=0;
    
    
    for(char i : key)
        hashVal=95*hashVal+i;        //95 printable letters
    auto return_val=(unsigned int)hashVal;  //static cast
    return return_val;
}

ostream & operator<<(ostream &os, const __ItemType& item){
    return os<<item.key<<", "<<item.data;
}

__ItemType::__ItemType(string s,int _data):key(s),data(_data){
}


/************helper functions*************************************************/

string toLower(const string &str){
    string lower_str;
    for(char i : str)
        lower_str+=char(tolower(i));
    return lower_str;
}
