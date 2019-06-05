/******************************************************************************
  Title          : _subway_portal.cpp
  Author         : Keisuke Suzuki
  Created on     : April 18, 2018
  Description    : Implementation file for SubwayPortal class
  Purpose        : To implement SubwayPortal class
  
******************************************************************************/
#include <utility>
#include "subway_portal.h"

/***************function prototypes for helper functions**********************/

/** getColumns() set a columns of a CVS string line in to a vector
 *  @param: string orig_str
 *  @param: vector columns
 *  @precondition: orig_str is a line of a CVS string, and columns is empty
 *  @postcondition: orig_str is empty and each elements in columns are set to
 *                  a string separated by commas
 */
void getColumns(string &orig_str, vector<string> &columns);


/**************************public methods************************************/

SubwayPortal::SubwayPortal():station_name(""),portal_name(""),corner(""),
                        bit_string(0),station_location(0),entrance_location(0){
}

SubwayPortal::SubwayPortal(string data_row) throw(Invalid_Portal_Data)
:station_name(""),portal_name(""),corner(""),bit_string(0),station_location
(0),entrance_location(0){
    
    bool valid_data=true;     //a boolean flag which stays true if data isvalid
    
    //store columns of a line of CVS file to row_arr
    vector<string> row_arr(33);
    getColumns(data_row,row_arr);
    
    station_name=row_arr[2];
    if(station_name.empty())
        valid_data=false;
    
    corner=row_arr[27];
    
    //initialize portal_name by adding row_arr[25]to row_arr[27]
    for(auto i=25;i<29;i++)
        portal_name+=i==28 ? row_arr[i]:row_arr[i]+',';
    
    //get route id from the route string in row_arr and set '1' to a string
    // whose index is the route id string
    for(int i=5;i<16;i++)
        if(is_route_id(row_arr[i])&&!row_arr[i].empty())
            bit_string+=(1<<routestring2int(row_arr[i]));
    
    //convert string location info of the portal and its station to double
    double station_lat=stod(row_arr[3]);
    double station_lon=stod(row_arr[4]);
    double entrance_lat=stod(row_arr[29]);
    double entrance_lon=stod(row_arr[30]);
    
    //throw Invalid_Portal_Data if catches BadPoint
    try{
        GPS station_loc(station_lat,station_lon);
        GPS entrance_loc(entrance_lat,entrance_lon);
        station_location=station_loc;
        entrance_location=entrance_loc;
    }
    catch(BadPoint &e){
        cerr<<"bad point cought"<<endl;
        throw Invalid_Portal_Data();
    }
    if(!valid_data){
        cout<<portal_name<<endl;
        throw Invalid_Portal_Data();
    }
}

SubwayPortal::SubwayPortal(const SubwayPortal &other)=default;

SubwayPortal &SubwayPortal::operator=(const SubwayPortal &other)=default;

SubwayPortal& SubwayPortal::operator=(SubwayPortal&& other)=default;

double SubwayPortal::distance_from(double latitude,double longitude)const{
        try{
            GPS a_location(latitude,longitude);
            return distance_between(a_location,entrance_location);
        }
        catch(BadPoint &b){
            throw Invalid_Portal_Data();
        }
}

double distance_between(SubwayPortal portal1,SubwayPortal portal2){
    try{
        return distance_between(portal1.entrance_location,portal2
            .entrance_location);
    }
    catch(BadPoint &b){
        throw Invalid_Portal_Data();
    }
}

bool same_routes(SubwayPortal portal1,SubwayPortal portal2){
    
    //route set1 and route set2 are identical by xor operation
    return ((portal1.bit_string^portal2.bit_string)==0);
}

bool same_station(SubwayPortal portal1,SubwayPortal portal2){
    return portal1.station_name==portal2.station_name;
}

ostream &operator<<(ostream &out,SubwayPortal e){
    return out<<e.portal_name<<endl;
}

string SubwayPortal::name() const{
    return portal_name;
}

bool SubwayPortal::can_access(route_set route) const{
    return route==(bit_string&route);
}

GPS SubwayPortal::p_location() const{
    return entrance_location;
}

GPS SubwayPortal::s_location() const{
    return station_location;
}

route_set SubwayPortal::routes() const{
    return bit_string;
}

/****************************helper functions**********************************/

void getColumns(string &orig_str,vector<string> &columns){
   
   for(auto &column:columns){
        size_t comma_loc=orig_str.find_first_of(',');
        size_t quotes_loc=orig_str.find_first_of('"');
        
        //comma found before double quotes
        if(comma_loc<quotes_loc&&comma_loc!=std::string::npos&&
                                            quotes_loc!=std::string::npos){
            column=orig_str.substr(0,comma_loc);
            orig_str=orig_str.substr(comma_loc+1);
        }
        
        //quotes found before comma and quotes_loc is greater than -1
        else if(quotes_loc!=std::string::npos){
            quotes_loc=orig_str.find_first_of('"',quotes_loc+1);
            comma_loc=orig_str.find_first_of(',',quotes_loc+1);
            column=orig_str.substr(0,comma_loc);
            orig_str=orig_str.substr(comma_loc+1);
        }
    }
}