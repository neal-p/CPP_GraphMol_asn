# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Creator:  Tony Drummond, PhD. 
# Date Created: October 10, 2022
# Last Modified: October 2, 2023

# Directory Path: Week9/Source/Sort
# This creates executables for tests of sorting functions. 

# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version -c create a library object
CPPFLAGS    = -O3

# The directory where Week 9's main library include files are stored.
INC_DIR = ../include

# The directory where the include files for utilities are stored
UINC_DIR = ../util/include

# The directory where Week 9's main library object files are stored
LIB_DIR     = ../lib

# The directory where the library object files for utilities are stored
ULIB_DIR     = ../util/lib

# Executable programs
BIN_DIR     = ../bin

# The next line contains a list of executable object files 
# created by this Makefile.
TESTS = test_graph_al_directed test_graph_al_undirected test_graph_am_directed test_graph_am_undirected test_ethane test_octane test_distmat

test_graph_al_directed: test_graph_al_directed.cpp
	$(CPP) $(CPPFLAGS) test_graph_al_directed.cpp \
	-o $(BIN_DIR)/test_graph_al_directed \
	-I$(INC_DIR) \

test_graph_al_undirected: test_graph_al_undirected.cpp
	$(CPP) $(CPPFLAGS) test_graph_al_undirected.cpp \
	-o $(BIN_DIR)/test_graph_al_undirected \
	-I$(INC_DIR) \

test_graph_am_directed: test_graph_am_directed.cpp
	$(CPP) $(CPPFLAGS) test_graph_am_directed.cpp \
	-o $(BIN_DIR)/test_graph_am_directed \
	-I$(INC_DIR) \

test_graph_am_undirected: test_graph_am_undirected.cpp
	$(CPP) $(CPPFLAGS) test_graph_am_undirected.cpp \
	-o $(BIN_DIR)/test_graph_am_undirected \
	-I$(INC_DIR) \


test_ethane: test_ethane.cpp
	$(CPP) $(CPPFLAGS) test_ethane.cpp \
	-o $(BIN_DIR)/test_ethane \
	-I$(INC_DIR) \


test_octane: test_octane.cpp
	$(CPP) $(CPPFLAGS) test_octane.cpp \
	-o $(BIN_DIR)/test_octane \
	-I$(INC_DIR) \

test_distmat: test_distmat.cpp
	$(CPP) $(CPPFLAGS) test_distmat.cpp \
	-o $(BIN_DIR)/test_distmat \
	-I$(INC_DIR) \
	-I$(UINC_DIR) \
	$(ULIB_DIR)/libmymetrics.a



all: $(TESTS)

cleanall:
	cd $(BIN_DIR); rm $(TESTS)

