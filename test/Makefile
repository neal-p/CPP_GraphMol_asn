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
UINC_DIR = ../utils/include

# The directory where Week 9's main library object files are stored
LIB_DIR     = ../lib

# The directory where the library object files for utilities are stored
ULIB_DIR     = ../utils/lib

# Executable programs
BIN_DIR     = ../bin

# The next line contains a list of executable object files 
# created by this Makefile.
#SORT_EXECUTABLES = 

test_graph: test_graph.cpp
	$(CPP) $(CPPFLAGS) test_graph.cpp \
	-o $(BIN_DIR)/test_graph \
	-I$(INC_DIR) \


#all: $(SORT_EXECUTABLES)

cleanall:
	cd $(BIN_DIR); rm $(EXECUTABLES)

