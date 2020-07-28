/**
    subway_station.cpp
    @author Keisuke Suzuki
    @version 1.0 7/28/20
    Purpose: To Implement SubwayStation class
    
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

#include "subway_station.h"

SubwayStation::SubwayStation(): m_parent_id(-1)
{
}

SubwayStation::SubwayStation(const SubwayPortal &portal):
    m_parent_id(-1),
    m_primary_name(portal.station_name),
    portal_unique_name(portal.portal_name),
    portal(portal)
{
    m_station_names.insert(portal.station_name);
}

SubwayStation &SubwayStation::operator =(const SubwayStation &other) = default;

void SubwayStation::set_parent(int newparent)
{
    m_parent_id = newparent;
}

void SubwayStation::add_child(int child)
{
    children.push_back(child);
}

bool connected(const SubwayStation &s1, const SubwayStation &s2)
{
    if(same_station(s1.portal, s2.portal))
        return true;
    
    //distance between two portals are less than or equal to 0.32km
    bool distance = distance_between(s1.portal, s2.portal) <= 0.32;
    
    //route set1 and route set2 are identical by xor operation
    bool route = same_routes(s1.portal, s2.portal);
    
    //return true if distance and route are both true
    return distance && route;
}

int SubwayStation::add_station_name(const string &newname)
{
    auto result = m_station_names.insert(newname);
    return !result.second;    //return true if inserted otherwise false
}

list <string> SubwayStation::names() const
{
    list <string> names;  //temp station names
    
    //copy set of names to temp list
    for(const auto &m_station_name : m_station_names)
    {
        names.push_back(m_station_name);
    }
    
    return names;
}

string SubwayStation::primary_name() const
{
    return m_primary_name;
}

int SubwayStation::parent_id() const
{
    return m_parent_id;
}

list<int> SubwayStation::portal_list() const
{
    return children;
}

string SubwayStation::portal_name() const
{
    return portal_unique_name;
}

void SubwayStation::get_portal(SubwayPortal &_portal) const
{
    _portal = portal;
}

