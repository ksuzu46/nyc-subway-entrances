/**
    subway_portal.cpp
    @author Keisuke Suzuki
    @version 1.0 7/28/20
    Purpose: To Implement SubwayPortal class
    
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

#include "subway_portal.h"

/**************************public methods************************************/


SubwayPortal::SubwayPortal() = default;

SubwayPortal::SubwayPortal(const string &data_row): bit_string(0)
{
    
    stringstream ss(data_row);
    string temp, s_lat, s_lon, e_lat, e_lon;
    bool valid_data = true;
    int i = 0;
    
    //get and set data to corresponding elements
    while(getline(ss, temp, '"'))
    {
        stringstream tss(temp);
        while(getline(tss, temp, ','))
        {
            //get rid of '(' and ')' from temp
            if(*temp.begin() == '(')
                temp.substr(1);
            else if(tss.eof() && !temp.empty())
                temp.pop_back();
            
            if(i == 2)
            {
                if(temp.empty())
                    valid_data = false;
                station_name = temp;
            }
            if(i == 3)
            {
                if(temp.empty())
                    valid_data = false;
                s_lat = temp;
            }
            if(i == 4)
            {
                if(temp.empty())
                    valid_data = false;
                s_lon = temp;
            }
            if(i >= 5 && i <= 15 && !temp.empty())
            {
                bit_string |= route_set(1ul << routestring2int(temp));
            }
            if(i >= 25 && i <= 28)
            {
                portal_name += i == 28 ? temp : temp + ',';
            }
            if(i == 29)
            {
                if(temp.empty())
                    valid_data = false;
                e_lat = temp;
            }
            if(i == 30)
            {
                if(temp.empty())
                    valid_data = false;
                e_lon = temp;
            }
            
            //throw Invalid_Portal_Data if not valid
            if(!valid_data)
                throw Invalid_Portal_Data();
            i++;
        }
    }
    
    //check if locations are valid
    try
    {
        GPS station_loc(stod(s_lat), stod(s_lon));
        GPS entrance_loc(stod(e_lat), stod(e_lon));
        station_location = station_loc;
        entrance_location = entrance_loc;
    }
    catch(BadPoint const &e)
    {
        cerr << "exception caught: " << e.what() << endl;
    }
}

SubwayPortal::SubwayPortal(const SubwayPortal &other) = default;

SubwayPortal &SubwayPortal::operator =(const SubwayPortal &other) = default;

SubwayPortal &SubwayPortal::operator =(SubwayPortal &&other) = default;

double SubwayPortal::distance_from(double latitude, double longitude) const
{
    GPS a_location(latitude, longitude);
    return distance_between(a_location, entrance_location);
}

double
distance_between(const SubwayPortal &portal1, const SubwayPortal &portal2)
{
    return distance_between(portal1.entrance_location, portal2
        .entrance_location);
}

bool same_routes(const SubwayPortal &portal1, const SubwayPortal &portal2)
{
    return portal1.bit_string == portal2.bit_string;
}

bool same_station(const SubwayPortal &portal1, const SubwayPortal &portal2)
{
    return portal1.station_name == portal2.station_name;
}

ostream &operator <<(ostream &out, const SubwayPortal &e)
{
    return out << e.portal_name << endl;
}

string SubwayPortal::name() const
{
    return portal_name;
}

bool SubwayPortal::can_access(route_set route) const
{
    return (route & bit_string) != 0;
}

GPS SubwayPortal::p_location() const
{
    return entrance_location;
}

GPS SubwayPortal::s_location() const
{
    return station_location;
}

route_set SubwayPortal::routes() const
{
    return bit_string;
}

