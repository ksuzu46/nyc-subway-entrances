/******************************************************************************
  Title          : subway_system.cpp
  Author         : Keisuke Suzuki
  Created on     : April 18, 2018
  Description    : An implementation for the SubwaySystem class
  Purpose        : To implement SubwaySystem class

******************************************************************************/
#include "subway_system.h"

SubwaySystem::SubwaySystem():stations(),portal_table(MAX_STATIONS),
station_table(MAX_STATIONS),routes(35,SubwayRoute()){
    
    //and store route_ids of string of route
    unsigned long j=0;
    for(auto i:ids){
        if(is_route_id(i)){
            //set route_id th bit of route_set to 0
            route_set route_set=0;
            route_set|=1UL<<(unsigned long) routestring2int(i);
            routes[j].routes=route_set;
            j++;
        }
    }
}

SubwaySystem::SubwaySystem(const SubwaySystem &other)=default;

SubwaySystem &SubwaySystem::operator=(const SubwaySystem &other)=default;

int SubwaySystem::add_portal(const SubwayPortal &portal){
    
    //add portal to the vector
    SubwayStation station(portal);
    __ItemType item;
    //add stations to disjoint set
    stations.push_back(station);
    
    //hash entry with name as a key, and the index stored in the vector
    item.set(station.portal_name(),(int)stations.size()-1);
    
    //insert portal to the hash table and return 1 if it is successful
    int return_val=portal_table.insert(item);
    
    return return_val;
}

void SubwaySystem::list_all_stations(ostream &out) const{
    
    for(const auto &station:stations){
        //root of disjoint set
        if(station.parent_id()<0){
            //root has unique set of names
            for(const auto &name:station.names())
                out<<name<<endl;
        }
    }
}

void SubwaySystem::list_all_portals(ostream &out,string station_name) const{
    
    __ItemType item(station_name);
    int index;
    list<int> portal_list;
    
    if(station_table.find(item)){
        
        //get root of disjoint station set
        item.get(station_name,index);
        portal_list=stations[index].portal_list();
        
        //print root and its children' portal_name
        out<<stations[index].portal_name()<<endl;
        for(auto &c_index:portal_list){
            out<<stations[c_index].portal_name()<<endl;
        }
    }
}


void SubwaySystem::list_stations_of_route(ostream &out,const route_id& route) const{
    
    //get station list for this route
    list<int> temp_list;
    auto _route_set=(unsigned long) routestring2int(route);
    const auto mask=ULONG_MAX;
    _route_set&=mask;
    
    //look for identical route
    for(const auto &i:routes){
        if(i.routes==(1<<_route_set|1>>(_route_set&mask)))  //route is identical
            temp_list=i.station_list();
    }
    
    //traverse through temp_list and station names in the index
    for(const auto &i:temp_list){
        for(const auto &name:stations.at(i).names())
            out<<name<<endl;
    }
}

int SubwaySystem::form_stations(){
    
    const auto begin=stations.begin();
    const auto end=stations.end();
    int station_count=0;
    
    //union identical portals
    for(auto i=begin;i!=end;++i)
        for(auto j=begin;j!=end;++j){
            
            //i and j both are root of set and they are connected
            if(i->parent_id()<0&&j->parent_id()<0&&connected(*i,*j))
                union_set(i-begin,j-begin);  //union two stations
        }
    
    //perform find operation for all entrances
    for(auto it=begin;it!=end;++it)
        find(it-begin);
    
    //store indexes of root of each disjoint to station table and station
    //list of routes accessible to station set
    for(auto it=begin;it!=end;++it){
        
        //current element is root of the set
        if(it->parent_id()<0){
            auto cur_pos=int(it-begin);  //current index
            SubwayPortal portal;
            it->get_portal(portal);  //store portal member at cur_pos to portal
            route_set mask=portal.routes();  //route_set of the station
    
            //store names to station table
            for(const auto &name:it->names()){
                __ItemType item(name,cur_pos);
                //increment count if successfully inserted
                station_table.insert(item);
                station_count++;
            }
            
            //store current index to list in SubwayRoute class
            for(auto &route:routes){
                //the route is part of the route set of the root station
                if((route.routes&mask)==route.routes)
                    route.add_station_to_route(cur_pos);
            }
        }
    }
    return station_count;
}

bool SubwaySystem::get_portal(string name_to_find,SubwayPortal &portal) const{
    
    __ItemType item;
    int i;
    item.set(name_to_find);  //set key member of ItemType to name_to_find
    
    //find() sets members if found in the table
    int return_val=portal_table.find(item);
    if(return_val){
        item.get(name_to_find,i);   //copy name and index from item
    
        //get the portal member data stored at index and copy it to portal
        stations[i].get_portal(portal);
    }
    
    return (bool)return_val;
}

string SubwaySystem::nearest_portal(double latitude,double longitude) const{
    
    double min_distance=DBL_MAX_EXP;  //maximum value double can store
    string return_name;
    
    for(const auto &i:stations){
        SubwayPortal portal;
        i.get_portal(portal);
        double dist=portal.distance_from(latitude,longitude);
        
        if(dist<min_distance){
            min_distance=dist;
            return_name=portal.name();
        }
    }
    return return_name;
}

string SubwaySystem::nearest_routes(double latitude,double longitude) const{
    
    __ItemType item;
    SubwayPortal portal;
    int i;
    
    //get name of nearest portal of the rest
    string portal_name=nearest_portal(latitude,longitude);
    item.set(portal_name);              //set portal_name to item's key
    portal_table.find(item);            //get portal from portal_table
    
    //set portal_name to item.key and index to item.data
    item.get(portal_name,i);
    
    //set portal to a portal stored subway_station[index]
    stations[i].get_portal(portal);
    
    return str_from_routeset(portal.routes());
}

void SubwaySystem::union_set(size_t root1,size_t root2){
    
    if(root1!=root2){
        
        SubwayStation *ptr1=&stations[root1];  //pointer to s[root1]
        SubwayStation *ptr2=&stations[root2];  //pointer to s[root2]
        int p_id1=ptr1->parent_id();           //temp copy parent_id s[root1]
        int p_id2=ptr2->parent_id();           //temp copy parent_id s[root1]
    
        //set parent_id of root1 to sum of the p_ids
        ptr1->set_parent(p_id1+p_id2);
        //set parent of station at root two to root1
        ptr2->set_parent(root1);
        //add station names of s[root2] to s[root1]
        for(auto &i:ptr2->names())
            ptr1->add_station_name(i);
    }
}

int SubwaySystem::find(int i){
    
    //pointer for current station
    SubwayStation* cur_station=&stations[i];
    
    //parent station does not have parent cell
    if(cur_station->parent_id()<0)
        return i;
    
    int root_id=find(cur_station->parent_id());  //find the root recursively
    cur_station->set_parent(root_id);   //set cur_station's parent id to root_id
    stations[root_id].add_child(i); //set i as a child of root station
    
    return root_id;
}


