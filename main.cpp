/*******************************************************************************
  Title          : main.cpp
  Author         : Stewart Weiss
  Created on     : April 12, 2018
  Description    : The main program for Project3, processing MTA Subway Entrance
                   data.
  Purpose        : reads the data file and a command file, applying
                   commands to the subway entrance data.
  Usage          : project3  datafile  commandfile
  Build with     : g++ -o project3 main.cpp

  Modifications  : made by Keisuke Suzuki on 7/31/2019
  	           Added " break" in command reading while loop, and a new line
		   to command files so that it does not ignore the last command  

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <climits>


#include "Command/command.h"
#include "GPS/gps.h"
#include "HashItem/_hash_item.h"
#include "HashTable/hash_table.h"
#include "SubwaySystem/_subway_system.h"
#include "SubwaySystem/subway_system.h"


using namespace std;

/******************************************************************************
Data Dictionary for Input File:
 Position   Type   Name        Description
 1          uint   ObjectID    Unique identifier for subway entrance
 3          string Name        Name of this station (actually its address)
 4          string The_Geom    GPS coordinates of the form POINT(decimal decimal)
                               where first is longitude and second, latitude
 5          string Line        Representation of lines accessed at this entrance
                               See the assignment spec for details.

 ******************************************************************************/

/******************************************************************************
Commands:

list_route_stations route_identifier
    Lists the station_names of all subway stations that service the given route.

list_all_stations
    Lists the station_names of all subway stations in the subway system.

list_routes portal_name
    Lists the routes that can be accessed at this portal. Routes should be
    printed in the form "route,route,..., route" where route is a route id
    like A, B, 7, FS. portal_name is the unique string for the portal.

list_station_portals station_name
    Lists the names of all subway portals for the given station.

nearest_routes latitude longitude
    Lists the route_ids of all subway routes that are closest to the
    point (latitude, longitude). There may be more than one because two or
    more lines might be at a station that is nearest to the point, or
    because two stations might be at the same distance from the point.

nearest_portal latitude longitude
    Lists the name of the subway portal that is closest to the
    point (latitude, longitude).  The two numbers are checked for validity -
    no absolute value greater than 180 degrees is allowed. In the very unlikely
    event that two portals are exactly the same distance from the point, the
    first found is chosen.

******************************************************************************/



int main( int argc, char* argv[]){
    
    ifstream inputfile;
    ifstream commandfile;
    string portal_row;
    Command command;
    string station_name;
    string routestr;
    bool result;
    string prev;
    SubwayPortal temp_portal;
    SubwaySystem MTA_subways;
    
    
    if(argc<3){
        cerr<<"\n Usage: "<<argv[0]<<" input_file  command_file"<<endl;
        exit(1);
    }
    
    inputfile.open(argv[1]);
    if(inputfile.fail()){
        cerr<<"Could not open file "<<argv[1]<<" for reading"<<endl;
        exit(1);
    }
    
    commandfile.open(argv[2]);
    if(commandfile.fail()){
        cerr<<"Could not open file "<<argv[2]<<" for reading"<<endl;
        exit(1);
    }
    
    
    int num_portals=0;
    SubwayPortal prev_portal;
    while(getline(inputfile,portal_row)){
        temp_portal=SubwayPortal(portal_row);
        MTA_subways.add_portal(temp_portal);
        num_portals++;
    }
    
    int number_of_stations=MTA_subways.form_stations();
    
    inputfile.close();
    
    
    while(!commandfile.eof()){
        if(!command.get_next(commandfile)){
            if(!commandfile.eof()){
                cerr<<"Error getting command.\n";
                continue;
            }
            else break;
        }
        
        string id;
        string portal_name;
        double longitude;
        double latitude;
        
        command.get_args(id,station_name,portal_name,longitude,latitude,
                         result);
        
        switch(command.type_of()){
            case list_route_stations_cmmd:
                cout<<"\nStations of the "<<id<<" line:\n";
                MTA_subways.list_stations_of_route(cout,id);
                break;
            
            case list_all_stations_cmmd:
                cout<<"\nAll "<<number_of_stations<<" stations:"<<endl;
                MTA_subways.list_all_stations(cout);
                break;
            
            case list_station_portals_cmmd:
                cout<<"\nEntrances at station "<<"\""<<station_name
                    <<"\":\n\n";
                MTA_subways.list_all_portals(cout,station_name);
                cout<<endl;
                break;
            
            case list_routes_cmmd:
                MTA_subways.get_portal(portal_name,temp_portal);
                cout<<"\nThe routes that can be accessed from this "
                    <<"entrance are "
                    <<str_from_routeset(temp_portal.routes())
                    <<endl;
                break;
            case nearest_routes_cmmd:
                routestr=MTA_subways.nearest_routes(latitude,longitude);
                if(routestr.length()==1)
                    cout<<"\nThe closest subway line to point ("
                        <<latitude<<","<<longitude<<") is the "
                        <<routestr
                        <<endl;
                else
                    cout<<"\nThe closest subway lines to point ("
                        <<latitude<<","<<longitude<<") are "
                        <<routestr
                        <<endl;
                break;
            case nearest_portal_cmmd:
                cout<<"\nThe closest entrance to point ("
                    <<latitude<<","<<longitude<<") is "
                    <<MTA_subways.nearest_portal(latitude,longitude)
                    <<endl;
                break;
            case bad_cmmd:
                break;
            case null_cmmd:
            default:
                break;
        }
    }
    commandfile.close();
    return 0;
}
