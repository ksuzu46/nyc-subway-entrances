/******************************************************************************
  Title          : subway_route.cpp
  Author         : Keisuke Suzuki
  Created on     : April 18, 2018
  Description    : Implementation file for subway-portal class
  Purpose        : To implement subway-portal class
  
******************************************************************************/

#include "subway_route.h"

bool is_route_id(const string& s){
    bool return_val=false;
    for(size_t i=0;i<MAX_ROUTES;i++){
        if(id[i]==s)
            return_val=true;
    }
    return return_val;
}

string str_from_routeset(route_set s){
    string return_val;
    bitset<64> bit_set(s);
    for(size_t i=0;i<MAX_ROUTES;i++){
        if(bit_set[i])
            return_val+=id[i]+' ';
    }
    return return_val;
}

int routestring2int(const string& s){
    int return_val=-1;
    for(size_t i=0;i<MAX_ROUTES;i++){
        if(s==id[i])
            return_val=i;
    }
    return return_val;
}

string int2route_id(int k){
    return id.at(k);
}


//member functions
SubwayRoute::SubwayRoute()=default;

list<int> SubwayRoute::station_list() const{
    return stations;
}

void SubwayRoute::add_station_to_route(int station_id){
    stations.push_back(station_id);
}

route_set SubwayRoute::get_routeset() const{
    return routes;
}