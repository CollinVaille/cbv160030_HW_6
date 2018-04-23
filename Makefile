
#Collin Vaille (cbv160030), CS 3377 Section 501, Homework 6

#This makefile is based off of the CDK example in the class notes.
#Manages hw6.h, hw6.cc, and hw6Helper.cc.

CXX = g++
CXXFLAGS = -Wall -g -std=c++11 #Need c++11 for uint32_t and uint64_t
CPPFLAGS = -I/scratch/perkins/include -I./
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

EXECFILE = hw6

OBJS = hw6.o hw6Helper.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

