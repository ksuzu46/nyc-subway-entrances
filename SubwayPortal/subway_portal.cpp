/******************************************************************************
  Title          : _subway_portal.cpp
  Author         : Keisuke Suzuki
  Created on     : April 18, 2018
  Description    : Implementation file for SubwayPortal class
  Purpose        : To implement SubwayPortal class
  
******************************************************************************/
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

bool is_number(const std::string& s);
/**************************public methods************************************/

SubwayPortal::SubwayPortal()=default;

SubwayPortal::SubwayPortal(const string &data_row): bit_string(0){

    stringstream ss(data_row);
    string temp,s_lat,s_lon,e_lat,e_lon;
    bool valid_data=true;
    int i=0;
    
    //get and set data to corresponding elements
    while(getline(ss,temp,'"')){
        stringstream tss(temp);
        while(getline(tss,temp,',')){
            //get rid of '(' and ')' from temp
            if(*temp.begin()=='(')
                temp.substr(1);
            else if(tss.eof()&&!temp.empty())
                temp.pop_back();
            
            if(i==2){
                if(temp.empty())
                    valid_data=false;
                station_name=temp;
            }
            if(i==3){
                if(temp.empty())
                    valid_data=false;
                s_lat=temp;
                //DEBUG("s_lat: "+s_lat);
            }
            if(i==4){
                if(temp.empty())
                    valid_data=false;
                s_lon=temp;
                //DEBUG("s_lon: "+s_lon);
            }
            if(i>=5&&i<=15&&!temp.empty()){
                bit_string+=1UL<<(route_set) routestring2int(temp);
            }
            if(i>=25&&i<=28){
                portal_name+=i==28 ? temp:temp+',';
            }
            if(i==29){
                if(temp.empty())
                    valid_data=false;
                e_lat=temp;
                //DEBUG("e_lat: "+e_lat);
            }
            if(i==30){
                if(temp.empty())
                    valid_data=false;
                e_lon=temp;
                //DEBUG("e_lon: "+e_lon)
            }
            
            //throw Invalid_Portal_Data if not valid
            if(!valid_data)
                throw Invalid_Portal_Data();
            i++;
        }
    }
    
    //check if locations are valid
    try{
        GPS station_loc(stod(s_lat),stod(s_lon));
        GPS entrance_loc(stod(e_lat),stod(e_lon));
        station_location=station_loc;
        entrance_location=entrance_loc;
    }
    catch(BadPoint const &e){
        cerr<<"exception caught: "<<e.what()<<endl;
    }
}

SubwayPortal::SubwayPortal(const SubwayPortal &other)=default;

SubwayPortal &SubwayPortal::operator=(const SubwayPortal &other)=default;

SubwayPortal& SubwayPortal::operator=(SubwayPortal&& other)=default;

double SubwayPortal::distance_from(double latitude,double longitude)const{
    GPS a_location(latitude,longitude);
    return distance_between(a_location,entrance_location);
}

double distance_between(const SubwayPortal& portal1,const SubwayPortal& portal2){
    return distance_between(portal1.entrance_location,portal2
    .entrance_location);
}

bool same_routes(const SubwayPortal& portal1,const SubwayPortal& portal2){
    
    //route set1 and route set2 are identical by xor operation
    return ((portal1.bit_string^portal2.bit_string)==0);
}

bool same_station(const SubwayPortal& portal1,const SubwayPortal& portal2){
    return portal1.station_name==portal2.station_name;
}

ostream &operator<<(ostream &out,const SubwayPortal& e){
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

bool is_number(const std::string& s){
    std::string::const_iterator it=s.begin();
    while(it!=s.end()&&(std::isdigit(*it)||*it=='.')) ++it;
    return !s.empty()&&it==s.end();
}