# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# 
# Creator:  Tony Drummond, PhD.  Faculty
# Date Created: September, 2022
# Date Updated: September 22, 2023 Patick Neal
#
# Directory Path: Assignment2/Utils/Metrics
#
# This makefile creates an object file containing timing utility 
# functions. After compiling all source program files, it creates a
# metrics library (libmymetrics.a), which is relocated to 
# Week7/Utils/Lib after its successful creation.

# GNU C++ Compiler
CPP         = g++      

# compiler flags -g debug, -O3 optimized version -c create a library object file
CPPFLAGS    = -O3 -c    

# The directory where the include files needed to create the library objects are
INC_DIR = ../include

# The directory where all object files are going to moved afer creation
LIB_DIR = ../lib

# The next line contains the list of timing utility object files created 
# with this Makefile (i.e. they are the targets this makefile builds)
TIMING_OBJS = timings.o
METRICS_LIB = libmymetrics.a

timings.o: $(INC_DIR)/timings.h
	$(CPP) $(CPPFLAGS) timings.cpp -I$(INC_DIR)

$(METRICS_LIB): $(TIMING_OBJS)
	ar -ru $(METRICS_LIB) $(TIMING_OBJS) 
	mv $(METRICS_LIB) $(LIB_DIR)
	rm $(TIMING_OBJS)

all: $(METRICS_LIB)

cleanall:
	cd $(LIB_DIR); rm $(METRICS_LIB)
