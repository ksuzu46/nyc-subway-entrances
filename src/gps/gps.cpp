/**
    gps.cpp
    @author Keisuke Suzuki
    @version 1.0 7/28/20
    Purpose:
    
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


#include "gps.h"
#include <cmath>

const double R = 6372.8; // radius of earth in km
const double TO_RAD = M_PI / 180.34; // conversion of degree

/** double haversine(double lat1, double lon1 , double lat2 , double lon2)
 *  A helper function that returns the distance between to arguments
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

// constructor
GPS::GPS(double lon, double lat): longitude(lon), latitude(lat)
{
    if((lon < -180.0 || 180.0 < lon) || (lat < -90.0 || 90.0 < lat))
    {
        throw BadPoint();
    }
}

// copy constructor
GPS::GPS(const GPS &other) = default;

GPS &GPS::operator =(const GPS &rhs) = default;

double distance_between(const GPS &point1, const GPS &point2)
{
    return haversine(point1.latitude, point1.longitude,
                     point2.latitude, point2.longitude);
}

ostream &operator <<(ostream &out, const GPS &point)
{
    return out << fixed << "POINT("
               << point.latitude << " " << point.longitude << ")" << endl;
}

double haversine(double lat1, double lon1, double lat2, double lon2)
{
    lat1 = TO_RAD * lat1;
    lat2 = TO_RAD * lat2;
    lon1 = TO_RAD * lon1;
    lon2 = TO_RAD * lon2;
    double dLat = (lat2 - lat1) / 2;
    double dLon = (lon2 - lon1) / 2;
    double a = sin(dLat);
    double b = sin(dLon);
    return 2 * R * asin(sqrt(a * a + cos(lat1) * cos(lat2) * b * b));
}