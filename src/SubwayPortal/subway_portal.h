/******************************************************************************
  Title          : _subway_portal.h
  Author         : Stewart Weiss
  Created on     : April 18, 2018
  Description    : Interface file for the SubwayPortal object
  Purpose        : Encapsulates data and methods of a subway portal

******************************************************************************/

#ifndef __SUBWAY_PORTAL_H__
#define __SUBWAY_PORTAL_H__
#include <sstream>

#include <string>
#include <vector>
#include <algorithm>
#include "../GPS/gps.h"
#include "../SubwayRoute/subway_route.h"

#define DEBUG(x) {std::cout<<x<<endl;}
#define MAX_ROW 32

using namespace std;

struct Invalid_Portal_Data{
    string what() const{
        return "Invalid Portal Data";
    }
};

class SubwayStation;

class SubwayPortal{
    
    public:
    /** SubwayPortal is a default constructor
     *  @param none
     */
    SubwayPortal();
    
    /** SubwayPortal() is a parametrized constructor which reads a line of
     *  CSV string and store part of the information in data members
     *  @param: string data_row
     */
    explicit SubwayPortal(const string &data_row);
    
    /** SubwayPortal() is a copy constructor
     *  @param: SubwayPortal other
     */
    SubwayPortal(const SubwayPortal &other);
    
    /** operator=() is a assignment operator
     * @param: portal
     * @return: this pointer after copying data from other
     */
    SubwayPortal& operator=(const SubwayPortal& portal);
    
    /** operator=() is move assignment operator
     * @param: portal
     * @return: this pointer after copying data from other
     */
    SubwayPortal& operator=(SubwayPortal &&portal);
    
    /** distance_from() returns the distance between station and a gps
     *  location
     *  @param: latitude
     *  @param: longnitude
     *  @return: double distance between this portal location and the point of
     *  argument
     */
    double distance_from(double latitude,double longitude) const;
    
    /** distance_between() is a friend function which returns the distance
     *  between tow portals
     *  @param: SubwayPortal portal1
     *  @param: SubwayPortal portal2
     *  @return:
     */
    friend double distance_between(const SubwayPortal& portal1, const SubwayPortal&
    portal2);
    
    
    /** returns true if the two portals have the exact same set of routes  */
    friend bool same_routes(const SubwayPortal& portal1,
                            const SubwayPortal& portal2);
    
    /** returns true if the two portals belong to the same station */
    friend bool same_station(const SubwayPortal& portal1,
                             const SubwayPortal& portal2);
    
    friend ostream &operator<<(ostream &out,const SubwayPortal& e);
    
    friend class SubwayStation;
    
    /*  Accessor  Functions */
    
    /**  name() returns name of portal as a unique string */
    string name() const;
    
    /** can_access() returns true if given route is accessible
     *  @param route_set [in]  a bitstring with a 1 bit for route
     *  @return bool  true iff route is accessible from this portal
     */
    bool can_access(route_set route) const;
    
    /**  p_location() returns GPS location of portal  */
    GPS p_location() const;
    
    /**  s_location() returns GPS location of portal's station */
    GPS s_location() const;
    
    /**  routes() returns route set of portal */
    route_set routes() const;
    
    private:
    string station_name;            //station name where the portal belongs
    string portal_name;              //contains either NW,NE,SW,SE
    route_set bit_string;           //a unique integer of combination of routes
    GPS station_location;           //GPS class with station info
    GPS entrance_location;          //GPS class with entrance info
};

#endif /* __SUBWAY_PORTAL_H__ */

