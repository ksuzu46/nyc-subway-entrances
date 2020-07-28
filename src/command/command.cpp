/******************************************************************************
  Title          : command.cpp
  Author         : Stewart Weiss
  Created on     : April 12, 2018
  Description    : Implementation of the Command class
  Purpose        : Represents a Command object
  Usage          :
  Build with     : g++ -c command.cpp
  Modifications  :
******************************************************************************/

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <climits>
#include "command.h"

#define MAXBUF 4096

using namespace std;

/******************************************************************************/
/*                               Utilities                                    */
/******************************************************************************/

void die(string s)
{
    std::cerr << "\t" << s << ".";
}

long get_long(char *str)
{
    long val;
    errno = 0;    /* To distinguish success/failure after call */
    val = strtol(str, nullptr, 0);
    if((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
       || (errno != 0 && val == 0))
    {
        perror("strtol");
        return -1;
    }
    return val;
}

/* A function to convert C strings to doubles */
double get_double(char *str)
{
    double val;
    char *endptr;
    
    errno = 0;    /* To distinguish success/failure after call */
    val = strtod(str, &endptr);
    if(errno != 0)
    {
        perror("strtod");
        return -1;
    }
    return val;
}

/******************************************************************************/
/*                       Methods of Command Class                             */
/******************************************************************************/


Command::Command(): type(null_cmmd)
{
}

bool Command::get_next(istream &in)
{
    string firstword;
    string rest_of_line;
    char line[MAXBUF];
    bool result = false;
    istringstream iss;
    
    if(in.good())
    {
        in.getline(line, MAXBUF);
        if(in.eof())
            return false;
        iss.str(line);
        iss >> firstword;
        if(!iss)
        {
            std::cerr << line << ": ";
            die(" Error in command file syntax");
            return false;
        }
        
        if(firstword == "list_route_stations")
        {
            getline(iss, rest_of_line);
            if(!iss)
            {
                std::cerr << line << ": ";
                die(" Missing line identifier for list_line_stations command");
                return false;
            }
            this->type = list_route_stations_cmmd;
            
            size_t found = rest_of_line.find_first_not_of(' ');
            this->route_id = rest_of_line.substr(found);
            if(this->route_id.empty())
                return false;
        }
        else if(firstword == "list_all_stations")
        {
            this->type = list_all_stations_cmmd;
        }
        else if(firstword == "list_station_portals")
        {
            getline(iss, rest_of_line);
            if(!iss)
            {
                std::cerr << line << ": ";
                die(" Missing station name for list_entrances command");
                return false;
            }
            this->type = list_station_portals_cmmd;
            size_t found = rest_of_line.find_first_not_of(' ');
            this->station_name = rest_of_line.substr(found);
        }
        else if(firstword == "list_routes")
        {
            getline(iss, rest_of_line);
            if(!iss)
            {
                std::cerr << line << ": ";
                die(" Missing portal name for list_routes command");
                return false;
            }
            this->type = list_routes_cmmd;
            size_t found = rest_of_line.find_first_not_of(' ');
            this->portal_name = rest_of_line.substr(found);
        }
        else if(firstword == "nearest_routes")
        {
            this->type = nearest_routes_cmmd;
            iss >> latitude;
            if(!iss)
            {
                std::cerr << line << ": ";
                die(" Failed to get latitude argument for nearest_routes command");
                return false;
            }
            if((latitude < -90) || (latitude > 90))
            {
                die(" Latitude must be in range [-90,90]");
                return false;
            }
            
            iss >> longitude;
            if(!iss)
            {
                std::cerr << line << ": ";
                die(" Failed to get longitude argument for nearest_routes command");
                return false;
            }
            if((longitude <= -180) || (longitude >= 180))
            {
                die(" Longitude must be in range (-180,180)");
                return false;
            }
        }
        else if(firstword == "nearest_portal")
        {
            this->type = nearest_portal_cmmd;
            iss >> latitude;
            if(!iss)
            {
                std::cerr << line << ": ";
                die(" Failed to get latitude argument for nearest_routes command");
                return false;
            }
            if((latitude < -90) || (latitude > 90))
            {
                die(" Latitude must be in range [-90,90]");
                return false;
            }
            
            iss >> longitude;
            if(!iss)
            {
                std::cerr << line << ": ";
                die(" Failed to get longitude argument for nearest_routes command");
                return false;
            }
            if((longitude <= -180) || (longitude >= 180))
            {
                die(" Longitude must be in range (-180,180)");
                return false;
            }
        }
        else
            this->type = bad_cmmd;
    }
    else
    {
        this->type = null_cmmd;
    }
    result = true;
    return result;
}

Command_type Command::type_of() const
{
    return type;
}

void Command::get_args(
    string &arg_route_id,
    string &arg_station_name,
    string &arg_portal_name,
    double &arg_longitude,
    double &arg_latitude,
    bool &result
) const
{
    result = true;
    if(list_station_portals_cmmd == type)
        arg_station_name = station_name;
    else if(list_route_stations_cmmd == type)
        arg_route_id = route_id;
    else if(list_routes_cmmd == type)
        arg_portal_name = portal_name;
    else if(nearest_portal_cmmd == type || nearest_routes_cmmd == type)
    {
        arg_latitude = latitude;
        arg_longitude = longitude;
    }
    else
        result = false;
}

