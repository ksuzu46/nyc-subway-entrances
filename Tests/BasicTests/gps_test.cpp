#include <iostream>
#include <subway_portal.h>
#include "GPS/gps.h"
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
    TEST(gps_test,out_of_range){
        double lat,lon;
        try{
            lon=10,lat=-200;
            GPS(lon,lat);
            FAIL()<<FAILED(lon,lat);
        }
        catch(BadPoint const &err){
            EXPECT_EQ(err.what(),std::string("BadPoint"));
        }
        try{
            lon=-182,lat=50;
            GPS(lon,lat);
            FAIL()<<FAILED(lon,lat);
        }
        catch(BadPoint const &err){
            EXPECT_EQ(err.what(),std::string("BadPoint"));
        }
    }
}
