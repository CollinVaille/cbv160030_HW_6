
#Collin Vaille (cbv160030), CS 3377 Section 501, Homework 6
#This makefile is based off of the CDK example in the class notes.
#Since there's only one .cc file for the project, it's just responsible for the object file and executable corresponding to that source file.

CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

EXECFILE = hw6

OBJS = hw6.o

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

