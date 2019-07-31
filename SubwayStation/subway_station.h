/******************************************************************************
  Title          : subway_station.h
  Author         : Keisuke Suzuki
  Created on     : April 18, 2018
  Description    : Interface file for SubwayStation class
  Purpose        : Interface for SubwayStation class which interacts with
                   the main program
                   
******************************************************************************/

#ifndef SW2_SUBWAY_STATION_H
#define SW2_SUBWAY_STATION_H

#include "../SubwayPortal/subway_portal.h"
#include "../SubwayRoute/subway_route.h"

#include <set>



class SubwayStation{
    public:
    /** SubwayStation() is a default constructor which initializes any
      * private members with suitable default values.
      */
    SubwayStation();
    
    /** SubwayStation() is a constructor that creates a SubwayStation object
      * from a portal and makes the portal embedded portal of this station
      * @param SubwayPortal portal
      */
    explicit SubwayStation(const SubwayPortal& portal);
    
    /** SubwayStation() is a copy constructor
     *  @param other
     */
    SubwayStation(const SubwayStation &other);
    
    /** operator=() is a assignment operator
     *  @param other
     *  @return
     */
    SubwayStation& operator=(const SubwayStation &other);
    
    /** set_parent() sets the parent id of the station
     *  @param int [in] the id of the parent
     */
    void set_parent(int newparent);
    
    /** add_child() adds a new child to the station's list of children
     *  @param int [in] the index of the child to add
     */
    void add_child(int child);
    
    /** A friend function that determines when two stations are connected
     *  @param SubwayStation [in] s1
     *  @param SubwayStation [in] s2
     *  @return bool true iff s1 and s2 are connected according to rules defined
     *  in the assignment specification
     */
    friend bool connected(const SubwayStation& s1,const SubwayStation& s2);
    
    /** add_station_name() adds a new name to station
     *  @Note: It does not add a name if it is already in the set of names for
     *  the station.
     *  @param string [in] new name is name to be added
     *  @return 1 if name is added and 0 if not
     */
    int add_station_name(const string& newname);
    
    /** names() returns a list of the names of the station as a list of strings
     */
    list <string> names() const;
    
    /** primary_name() is the first station name in its set of names
     *  @return string
     */
    string primary_name() const;
    
    /** parent_id() is the index in the array of the parent of the station
     *  @return
     */
    int parent_id() const;
    
    /** portal_list() returns a list of the ids in the list of the portals in
     *  this station set
     *  @return list<int>
     */
    list<int> portal_list() const;
    
    /** portal_name() returns the name of the embedded portal
     *  @return string
     */
    string portal_name() const;
    
    /** get_portal() returns the portal that is embedded in this station object
     *
     */
    void get_portal(SubwayPortal &) const;
    
    private:
    int m_parent_id;                       //parent id for the integer
    set<string> m_station_names;           //set of station names
    string m_primary_name;                 //first station name stored in set
    list<int> children;                    //indexes of children
    string portal_unique_name;             //embedded portal name
    SubwayPortal portal;                   //embedded portal
};




#endif //SW2_SUBWAY_STATION_H
