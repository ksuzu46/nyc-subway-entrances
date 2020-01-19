/******************************************************************************
  Title          : gps.h
  Author         : Stewart Weiss
  Created on     : April 18, 2018
  Description    : The interface to a GPS class that encapsulates GPS points
  
******************************************************************************/
#include <cstdio>
#include <iostream>
#include <string>
#include <exception>
using namespace std;

#ifndef __GPS_H__
#define __GPS_H__

struct BadPoint{
    string what() const{
        return "BadPoint";
    }
};

class GPS{
    public:
    /** GPS() constructor
     *  If the longitude or latitude is out of range, it throws a BadPoint
     *  error.
     */
    explicit GPS(double =0,double =0);
    
    /** GPS() copy constructor
     *  If the longitude or latitude is out of range, it throws a BadPoint
     *  error.
     */
    GPS(const GPS &other);
    
    GPS& operator=(const GPS &rhs);
    
    /** distance_between() computes the distance between two points on a sphere
     *  given by their latitudes and longitudes expressed in decimal degrees.
     *  Distance is measured in kilometers.
     */
    friend double distance_between(const GPS& point1,const GPS& point2);
    
    /** operator<<() prints the point in the same format as it is in the
     * input file, POINT( fixed_decimal fixed_decimal)
     */
    friend ostream &operator<<(ostream &out,const GPS& point);
    
    private:
    double longitude;
    double latitude;
};


#endif /* __GPS_H__ */


