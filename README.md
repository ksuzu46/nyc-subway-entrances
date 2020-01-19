<h1 align="center">NYCSubwayEntrances</h1>
<br>
<p align="center"><strong>Description</strong>
<p align="center">This project processes a dataset of NYC subway 
entrances which has almost all entrances of subway stations in NYC. 
 It will allow user to obtain information about selected aspects of 
 data, such as which route is the nearest from a GPS point entered by an
  user, which entrance is the closest from the entered point, or which 
  entrance is connected to an arbitral route, where two stations are 
  connected if they have free transfer meaning station has same 
  set of routes and the distance between them is less than 0.28km. <p></p>


<h2>Command Description</h2>

> **list_route_stations** *route_identifier*
> > Lists the station_names of all subway stations that service the
> > given route. The route identifier is case insensitive - either upper
> > or lower case should identify a route, e.g. "A" and "a" specify the
> > A route.

>  **list_all_stations** 
> >  Lists the station_names of all subway stations in the entire subway
> >  system.
							
>  **list_routes**  *portal_name* 
> > Lists the routes that can be accessed at this portal. Routes should
> > be printed in the form "route,route,..., route", where route is a
> > route id like A, B, 7, FS. portal_name is the unique string for the
> > portal defined in the link below.

> **list_station_portals**  *station_name* 
> > Lists the names of all subway portals for the given station. The
> > station name is case sensitive.

> **nearest_portal**  *latitude* *longitude* 
> > Lists the portal name of the portal that is closest to the point
> > (latitude , longitude ). The two numbers should be checked for
> > validity - no absolute value greater than 180 degrees is allowed. In
> > the very unlikely event that two portals are exactly the same
> > distance from the point, either one can be listed.

> **nearest_routes**  *latitude* *longitude* 
> > Lists the route_identifiers of all subway routes that are closest to
> > the point (latitude , longitude ). There may be more than one
> > because two or more routes might be at a station that is nearest to
> > the point.


<h2>Usage</h2>

1. Download and extract or clone this repository, and cd into the directory.
2. There are two ways to build the project.
    - Using cmake:
        ```shell
        mkdir  build  &&  cd  build
        ```
        ```shell
        cmake.. && make
        ```
    - Using make:
        ```shell
        make
        ```
3. Set PATH to bin: <pre> cd ..  &&  export  PATH=$PATH:$PWD/bin</pre>
4. Execute the program:
    - If the project is build by cmake:
        - To run all the commands in command-file by typing:
            ```shell
            runAll
            ```
        - or run a custom command defined above:
            ``` shell
            NYCSubwayEntrancesExe [InputFilePath] [CommandFilePath]
            ```
    - If the project is build by make:
        - To run all the commands in command-file by typing:
            ```shell
            make run
            ```
        - or run a custom command:
            ```
            exe [InputFilePath] [CommandFilePath]
            ```


<h2></h2> 
<p>Please
     visit <a
     href="http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci335/assignments_s19/project2_phase1.pdf">
     here</a> for more detailed specification</p>
