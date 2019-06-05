## [Click here to see ditailed project specification](http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci335/assignments_s19/project2_phase2.pdf)

### Brief Instruction

A School project which processes a dataset of NYC subway entrances using parent
tree, and it creates disjoint sets of stations. Two stations are connected if 
they have free transfer which means station has same set of routes and the 
distance between them is less than 0.28km by the definition in the project
specification. The dataset holds info such as station name, line name, 
route name, corner, GPS info of station and entrance, and etc. There are 
main program, and class SubwaySystem,SubwayStation, SubwayPortal, SubwayRoute, 
HashTable, HashItem, and GPS.

#### Provided files:

main.o           -A binally o.file of main program which handles getting line of 
                  the CVS file, it also processes the command argument specified 
                  by the project instruction linked below.

subway_route.h   -A interface file for SubwayRoute class whose implementation
                  is given as an o.file  
                 
subway_route.o   -A banally o.file of SubwayRoute class which stores bit_mask
                  which indicates the route, and Indexes of parent tree where
                  the station is stored.

_subway_system.h -A interface file that has _SubwaySystem class that specifies
                  minimal requirement for SubwaySystem which derives that class.

_subway_portal.h -A interface file that has _SubwayPortal class that specifies
                  minimal requirement for SubwayPortal. Renamed this filed 
                  as SubwayPortal to not have to derive the class.


           
