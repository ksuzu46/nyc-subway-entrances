gcc_options = -std=c++17 -Wall --pedantic-error
objects = main.o command.o gps.o _hash_item.o \
		  hash_table.o subway_system.o subway_portal.o\
		  subway_station.o subway_route.o

bin/exe: $(objects)
	g++ $(gcc_options) -o bin/exe $(objects)
	rm -rf *.o
main.o: src/main.cpp
	g++ $(gcc_options) -c src/main.cpp
command.o: src/command/command.cpp
	g++ $(gcc_options) -c src/command/command.cpp
gps.o: src/gps/gps.cpp
	g++ $(gcc_options) -c src/gps/gps.cpp
_hash_item.o: src/hash-item/_hash_item.cpp
	g++ $(gcc_options) -c src/hash-item/_hash_item.cpp
hash_table.o: src/hash-table/hash_table.cpp
	g++ $(gcc_options) -c src/hash-table/hash_table.cpp
subway_system.o: src/subway-system/subway_system.h
	g++ $(gcc_options) -c src/subway-system/subway_system.cpp
subway_station.o: src/subway-station/subway_station.cpp
	g++ $(gcc_options) -c src/subway-station/subway_station.cpp
subway_portal.o: src/subway-portal/subway_portal.cpp
	g++ $(gcc_options) -c src/subway-portal/subway_portal.cpp
subway_route.o: src/subway-route/subway_route.cpp
	g++ $(gcc_options) -c src/subway-route/subway_route.cpp

run: ./bin/exe
	./bin/makeRunAll
clean:
	rm -rf *.o bin/exe

.PHONY: clean
