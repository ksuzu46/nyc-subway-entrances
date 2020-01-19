gcc_options = -std=c++17 -Wall --pedantic-error
objects = main.o command.o gps.o _hash_item.o \
		  hash_table.o subway_system.o subway_portal.o\
		  subway_station.o subway_route.o

bin/exe: $(objects)
	g++ $(gcc_options) -o bin/exe $(objects)
	rm -rf *.o
main.o: src/main.cpp
	g++ $(gcc_options) -c src/main.cpp
command.o: src/Command/command.cpp
	g++ $(gcc_options) -c src/Command/command.cpp
gps.o: src/GPS/gps.cpp
	g++ $(gcc_options) -c src/GPS/gps.cpp
_hash_item.o: src/HashItem/_hash_item.cpp
	g++ $(gcc_options) -c src/HashItem/_hash_item.cpp
hash_table.o: src/HashTable/hash_table.cpp
	g++ $(gcc_options) -c src/HashTable/hash_table.cpp
subway_system.o: src/SubwaySystem/subway_system.cpp
	g++ $(gcc_options) -c src/SubwaySystem/subway_system.cpp
subway_station.o: src/SubwayStation/subway_station.cpp
	g++ $(gcc_options) -c src/SubwayStation/subway_station.cpp
subway_portal.o: src/SubwayPortal/subway_portal.cpp
	g++ $(gcc_options) -c src/SubwayPortal/subway_portal.cpp
subway_route.o: src/SubwayRoute/subway_route.cpp
	g++ $(gcc_options) -c src/SubwayRoute/subway_route.cpp

run: ./bin/exe
	./bin/makeRunAll
clean:
	rm -rf *.o bin/exe

.PHONY: clean bin/exe
