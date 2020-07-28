/**
    hash_table.cpp
    @author Keisuke Suzuki
    @version 1.0 7/28/20
    Purpose: To Implement HashTable class
    
    License: Copyright (c) 7/28/20 Keisuke Suzuki
    	This program is free software: you can redistribute it and/or modify
    	it under the terms of the GNU General Public License as published by
    	the Free Software Foundation, either version 3 of the License, or
    	(at your option) any later version.
  
    	This program is distributed in the hope that it will be useful,
    	but WITHOUT ANY WARRANTY; without even the implied warranty of
    	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    	GNU General Public License for more details
*/

#include "../hash-item/_hash_item.h"
#include "_hash_table.h"
#include "hash_table.h"
#include <cmath>
#include <climits>
#include <iostream>


/***************function prototypes for helper functions**********************/

/** isPrime checks if the value passed is a prime number
*  @param int
 *  @return true if the number is prime otherwise false
 */
bool isPrime(int);

/** nextPrime returns the next prime number of the value passed
 *  @param unsigned long
 *  @return the next prime number
 */
unsigned long nextPrime(unsigned long);


/*****************public methods**********************************************/

//parametrized constructor
HashTable::HashTable(int size): hash_table(nextPrime(size)),
                                table_status(nextPrime(size)), current_size(0)
{
    
    //initialize all keys and data in the table
    for(auto &i:hash_table)
    {
        i.set("", -1);
    }
    
    //make all elements marked as EMPTY
    makeEmpty();
}

HashTable::HashTable(const HashTable &rhs) = default;

HashTable &HashTable::operator =(const HashTable &other) = default;

int HashTable::find(__ItemType &item) const
{
    int current_pos = findPos(item);
    if(isActive(current_pos))
    {
        item = hash_table[current_pos];
        return 1;
    }
    else return 0;
}

int HashTable::insert(__ItemType item)
{
    int return_value;
    //cout<<"the address of hash table is: "<<this<<endl;
    //get empty index
    int current_pos = findPos(item);
    if(isActive(current_pos))
    {
        return_value = 0;
    }
    else
    {
        return_value = 1;
        
        // insert item as active
        hash_table[current_pos] = item;
        table_status[current_pos] = "ACTIVE";
        current_size++;
        
        // rehash if current_size is greater than half of the maximum capacity
        if(current_size > hash_table.size() / 2)
            rehash();
    }
    return return_value;
}

int HashTable::remove(__ItemType item)
{
    int return_value;
    // item not found in the table
    int current_pos = findPos(item);
    if(!isActive(current_pos))
        return_value = 0;
    else
    {
        return_value = 1;
        table_status[current_pos] = "DELETED";
        current_size--;
    }
    return return_value;
}

int HashTable::size() const
{
    return current_size;
}

int HashTable::listall(ostream &os) const
{
    int item_count = 0;
    for(size_t i = 0; i < current_size; i++)
    {
        if(isActive(i))
        {
            os << hash_table[i] << endl;
            item_count++;
        }
    }
    return item_count;
}

/*****************private methods**********************************************/

void HashTable::makeEmpty()
{
    current_size = 0;
    
    for(auto &i:table_status)
    {
        i = "EMPTY";
    }
}

int HashTable::findPos(const __ItemType &item) const
{
    int collision_num = 0;
    int current_pos = 0;       //number of collision
    // current_pos is a index value by hashing the value of item
    
    if(!hash_table.empty())
    {
        current_pos = hash(item.code(), hash_table.size());
    }
    
    // quadratic probing
    // in the loop until hash_table[current_pos] has info with value EMPTY
    // and element which is not identical to item
    while(table_status[current_pos] == "EMPTY" &&
          hash_table[current_pos] == item)
    {
        current_pos += 2 * ++collision_num - 1; // Compute ith probe
        if(current_pos >= hash_table.size())
        {
            current_pos -= hash_table.size();
        }
    }
    
    return current_pos;    //found the index
}

unsigned int HashTable::hash(unsigned int key, int table_size) const
{
    return key % table_size;         //hash(x)=x%table_size
}

bool HashTable::isActive(int current_pos) const
{
    return table_status[current_pos] == "ACTIVE";
}

void HashTable::rehash()
{
    //deep copy
    vector <__ItemType> old_table = hash_table;
    vector <string> old_status = table_status;
    auto old_size = hash_table.size();
    
    //resize hash_table with next prime value of double of TABLE_SIZE
    //and initialize TABLE_SIZE with that value
    hash_table.resize(nextPrime(2 * hash_table.size()));
    table_status.resize(nextPrime(2 * table_status.size()));
    
    //make hash_table empty
    makeEmpty();
    
    //insert the elements in old_table to new table by hashing
    //with the new table size
    for(size_t i = 0; i < old_size; i++)
    {
        if(old_status[i] == "ACTIVE")
        {
            insert(old_table[i]);
        }
    }
}

/************helper functions*************************************************/

bool isPrime(unsigned long num)
{
    // number is a prime number
    if(num == 2 || num == 3)
        return true;
    // number is not a prime number
    if(num % 2 == 0 || num % 3 == 0)
        return false;
    // num is not prime but not divisible by 2 or 3
    // loop until it finds if it is prime or not
    int divisor = 6;
    while(divisor * divisor - 2 * divisor + 1 <= num)
    {
        if(num % (divisor - 1) == 0)
            return false;
        if(num % (divisor + 1) == 0)
            return false;
        divisor += 6;
    }
    // num is a prime number
    return true;
}

unsigned long nextPrime(unsigned long num)
{
    // adding one until it becomes a prime number
    while(!isPrime(++num))
    {}
    //number is a prime number
    return num;
}