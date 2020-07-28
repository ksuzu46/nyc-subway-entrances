/**
    subway_route.cpp
    @author Keisuke Suzuki
    @version 1.0 7/28/20
    Purpose: To implement SubwayRoute class
    
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

#include <iostream>
#include "subway_route.h"

bool is_route_id(const string &s)
{
    bool return_val = false;
    for(size_t i = 0; i < MAX_ROUTES; i++)
    {
        if(id[i] == s)
            return_val = true;
    }
    return return_val;
}

string str_from_routeset(route_set s)
{
    string return_val;
    for(int i = 0; i < MAX_ROUTES; ++i)
    {
        if(s & (1ul << i))
        {
            if(!return_val.empty())
                return_val += ',';
            
            return_val += id[i];
        }
    }
    return return_val;
}

int routestring2int(const string &s)
{
    int return_val = 0;
    for(int i = 0; i < MAX_ROUTES; ++i)
    {
        if(s == id[i])
            return_val = i;
    }
    return return_val;
}

string int2route_id(int k)
{
    return id.at(k);
}

//member functions
SubwayRoute::SubwayRoute() = default;

list<int> SubwayRoute::station_list() const
{
    return stations;
}

void SubwayRoute::add_station_to_route(int station_id)
{
    stations.push_back(station_id);
}

route_set SubwayRoute::get_routeset() const
{
    return routes;
}