# Makefile for Subway Project

SRCS       = $(wildcard *.cpp)
OBJS       := $(patsubst %.cpp, %.o, $(SRCS))  
EXEC       := project2 
CXX        := /usr/bin/g++
CXXFLAGS   += -Wall -g -static -std=c++11 

$(EXEC): $(OBJS) subway_route.o 
	$(CXX) $(CXXFLAGS)  -o $@  $(OBJS) subway_route.o

.PHONY: clean cleanall
cleanall: clean
	$(RM) $(EXEC)

clean:
	$(RM) $(OBJS)




