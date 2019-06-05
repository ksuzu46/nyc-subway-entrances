# A Sample Makefile

SRCS       = $(wildcard *.cpp)
OBJS       := $(patsubst %.cpp, %.o, $(SRCS))  
EXEC       := project2 
CXX        := /usr/bin/g++
CXXFLAGS   += -Wall -g -std=c++11

$(EXEC): $(OBJS) main.o subway_route.o 
	$(CXX) $(CXXFLAGS)  -o $@  $(OBJS) main.o subway_route.o

.PHONY: clean cleanall
cleanall: clean
	$(RM) $(EXEC)

clean:
	$(RM) $(OBJS)




