/******************************************************************************
  Title          : hash_table.cpp
  Author         : Keisuke Suzuki
  Created on     : March 31, 2019
  Description    : Implementation of class HashTable
  Purpose        : To implement the class HashTable

******************************************************************************/

#include "_hash_item.h"
#include "_hash_table.h"
#include "hash_table.h"
#include <cmath>
#include <limits.h>
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
HashTable::HashTable(int size):current_size(0){
    
    //_size is next prime number of size
    auto _size=(size_t)nextPrime(size);
    
    //allocate hash_table and table_status dynamically
    hash_table=new vector<__ItemType>(_size);
    table_status=new vector<string>(_size);
    
    //initialize all keys and data in the table
    for(auto &i : *hash_table){
        i.set("",-1);
    }
    //make all elements marked as EMPTY
    makeEmpty();
}

HashTable::HashTable(const HashTable &rhs)=default;

HashTable::HashTable(HashTable &&other)=default;

HashTable &HashTable::operator=(const HashTable &other)=default;

HashTable &HashTable::operator=(HashTable &&other)=default;


int HashTable::find(__ItemType &item) const{
    int current_pos=findPos(item);
    if(isActive(current_pos)){
        item=hash_table->at(current_pos);
        return 1;
    }
    else return 0;
}

int HashTable::insert(__ItemType item){
    int return_value;
    //cout<<"the address of hash table is: "<<this<<endl;
    //get empty index
    int current_pos=findPos(item);
    if(isActive(current_pos))
        return_value=0;
    else{
        return_value=1;
        
        // insert item as active
        hash_table->at(current_pos)=item;
        table_status->at(current_pos)="ACTIVE";
        current_size++;
        
        // rehash if current_size is greater than half of
        // the maximum capacity
        if(current_size>hash_table->size()/2)
            rehash();
    }
    return return_value;
}

int HashTable::remove(__ItemType item){
    int return_value;
    // item not found in the table
    int current_pos=findPos(item);
    if(!isActive(current_pos))
        return_value=0;
    else{
        return_value=1;
        // mark as deleted so that the value cannot be used anymore
        table_status->at(current_pos)="DELETED";
        current_size--;
    }
    return return_value;
}


int HashTable::size() const{
    return current_size;
}

int HashTable::listall ( ostream & os ) const{
    int item_count=0;
    for(auto i=0;i<current_size;i++)
        if(isActive(i)){
            os<<hash_table->at(i)<<endl;
            item_count++;
        }
    return item_count;
}


/*****************private methods**********************************************/

void HashTable::makeEmpty(){
    current_size=0;
    for(auto &i : *table_status)
        i="EMPTY";
}


int HashTable::findPos(const __ItemType &item) const{
    int collision_num=0;            //number of collision
    
    // current_pos is a index value by hashing the value of item
    int current_pos=hash(item.code(),int(hash_table->size()));
    
    // quadratic probing
    
    // in the loop until hash_table[current_pos] has info with value EMPTY
    // and element which is not identical to item
    while(table_status->at(current_pos)=="EMPTY"&&
    hash_table->at(current_pos)==item){
        current_pos+=2*++collision_num-1; // Compute ith probe
        if(current_pos>=hash_table->size())
            current_pos-=hash_table->size();
    }
    
    //found the index
    return current_pos;
}

unsigned int HashTable::hash(unsigned int key,int table_size) const{
    return key%table_size;         //hash(x)=x%table_size
}

bool HashTable::isActive(int current_pos) const{
    return table_status->at(current_pos)=="ACTIVE";
}

void HashTable::rehash(){
    //deep copy
    vector<__ItemType> old_table=*hash_table;
    vector<string> old_status=*table_status;
    auto old_size=hash_table->size();
    
    //resize hash_table with next prime value of double of TABLE_SIZE
    //and initialize TABLE_SIZE with that value
    hash_table->resize(nextPrime(2*hash_table->size()));
    table_status->resize(nextPrime(2*table_status->size()));
    
    //make hash_table empty
    makeEmpty();
    
    //insert the elements in old_table to new table by hashing
    //with the new table size
    for(int i=0;i<old_size;i++)
        if(old_status[i]=="ACTIVE"){
            insert(old_table[i]);
        }
}

HashTable::~HashTable(){
    delete hash_table;
    delete table_status;
}

/************helper functions*************************************************/

bool isPrime(unsigned long num){
    // number is a prime number
    if(num==2||num==3)
        return true;
    // number is not a prime number
    if(num%2==0||num%3==0)
        return false;
    // num is not prime but not divisible by 2 or 3
    // loop until it finds if it is prime or not
    int divisor=6;
    while(divisor*divisor-2*divisor+1<=num){
        if(num%(divisor-1)==0)
            return false;
        if(num%(divisor+1)==0)
            return false;
        divisor+=6;
    }
    // num is a prime number
    return true;
}

unsigned long nextPrime(unsigned long num){
    // adding one until it becomes a prime number
    while(!isPrime(++num)){}
    //number is a prime number
    return num;
}