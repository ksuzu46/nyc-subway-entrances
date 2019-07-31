#include <iostream>
#include <subway_portal.h>
#include <subway_system.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

template <typename T>
std::string COLLECT(T lon, T lat){
    return "BadPoint called on (lon="+std::to_string(lon)+", lat="+
           std::to_string(lat)+")";
}
template <typename T>
std::string FAILED(T lon, T lat){
    return "Expected BadPoint on (lon="+std::to_string(lon)+", lat="+
           std::to_string(lat)+")";
}

namespace{
    TEST(portal_test,constructor_exception){
        try{
            SubwayPortal a_portal("");
            FAIL();
        }
        catch(Invalid_Portal_Data const &e){
            EXPECT_EQ(e.what(),std::string("Invalid Portal Data"));
        }
        
        try{
            SubwayPortal a_portal("BMT,4 Avenue,4 Avenue-25th St,40.660397,"
                                  "-73.998091,R,,,,,,,,,,,Stair,YES,,YES,NONE,,"
                                  "FALSE,,FALSE,4th Ave,25th St,SW,2,40.660489,"
                                  "-73.99822,\"(40.660397, -173.998091)\","
                                  "\"(40.660489, -73.998220)\"");
            FAIL();
        }
        catch(Invalid_Portal_Data const &e){
            EXPECT_EQ(e.what(),std::string("Invalid Portal Data"));
        }
        
        try{
            
            SubwayPortal a_portal("BMT,4 Avenue,,40.660397,"
                                  "-73.998091,R,,,,,,,,,,,Stair,YES,,YES,NONE,,"
                                  "FALSE,,FALSE,4th Ave,25th St,SW,2,40.660489,"
                                  "-73.99822,\"(40.660397, -173.998091)\","
                                  "\"(40.660489, -73.998220)\"");
            FAIL();
        }
        catch(Invalid_Portal_Data const &e){
            EXPECT_EQ(e.what(),std::string("Invalid Portal Data"));
        }
    }
    TEST(portal_test,distance_from){
        SubwayPortal a_portal("BMT,4 Avenue,4 Avenue-25th St,40.660397,"
                              "73.998091,R,,,,,,,,,,,Stair,YES,,YES,NONE,,"
                              "FALSE,,FALSE,4th Ave,25th St,SW,2,40.660489,"
                              "73.99822,\"(40.660397, 73.998091)\","
                              "\"(40.660489, 73.998220)\"");
        try{
            a_portal.distance_from(40.660397,-173.998091);
            FAIL()<<FAILED(40.660397,-173.998091);
        }
        catch(BadPoint const &e){
            EXPECT_EQ(e.what(),std::string("BadPoint"));
        }
    }
}
    
