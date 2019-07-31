/*****************************************************************************
  Title          : _hash_table.h
  Author         : Stewart Weiss
  Created on     : March 31, 2019
  Description    : Interface description for a hash table class
  Purpose        : To define the minimal requirements of a hash table
  Usage          : Derive a concrete hash table class from this interface
  Build with     : no building
  Modifications  :
      4/4/2019 by SW
      The constructor for the abstract class was removed. Abstract classes
      cannot have constructors. (I should have known that!)

******************************************************************************/
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <string>
#include "../HashItem/_hash_item.h"

using namespace std;

// The INITIAL_SIZE should be large enough that it will not need to be
// resized, but you might want to implement resizing in your class.
#define INITIAL_SIZE 4096

class __HashTable{
    public:
    
    /** find() searches in table for given item
     *  @precondition: item's key value is initialized
     *  @postcondition: if matching item is found, it is filled with value from
     *                  table.
     *  @param  ItemType [in,out] item : item to search for
     *  @return int 0 if item is not in table, and 1 if it is
     */
    virtual int find(__ItemType &item) const = 0;
    
    /** insert() inserts the given item into the table
     *  @precondition: item is initialized
     *  @postcondition: if item is not in table already, it is inserted
     *  @param  ItemType [in] item : item to insert
     *  @return int 0 if item is not inserted in table, and 1 if it is
     */
    virtual int insert(__ItemType item) = 0;
    
    /** remove() removes the specified  item from the table, if it is there
     *  @precondition: item's key is initialized
     *  @postcondition: if item was in table already, it is removed and copied
     *                  into the parameter, item
     *  @param  ItemType [in, out] item : item to remove
     *  @return int 0 if item is not removed from the table, and 1 if it is
     */
    virtual int remove(__ItemType item) = 0;
    
    /** size() returns the number of items in the table
     *  @precondition: none
     *  @postcondition: none
     *  @return int the number of items in the table
     */
    virtual int size() const = 0;
    
    /** listall() lists all items currently in the table
     *  @note   This function writes each item in the tabel onto the given stream.
     *          Items should be written one per line, in whatever format the
     *          underlying _ItemType output operator formats them.
     *  @param  ostream [in,out] the stream onto which items are written
     *  @return int the number of items written to the stream
     */
    virtual int listall ( ostream & os ) const = 0;
    
    
};

#endif /* __HASH_TABLE_H__ */




