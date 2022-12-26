CCXX = g++        
INCLUDES = -I/usr/local/include/igraph 
CXXFLAGS = -Wall -Wextra -std=c++14 $(CPPUNIT_CFLAGS)
LDFLAGS = $(CPPUNIT_LIBS) -ldl -L/usr/local/lib 
LDLIBS = -ligraph -pthread -lcppunit 
MAKEDOC = make doc
CMAKE = cmake 
MKDIR = mkdir
MAKE = make
CD = cd
CP = cp
RM = rm

SRC_PROG = $(wildcard Model/Utils/*.cpp) $(wildcard Model/*.cpp)
SRC_TOPO = $(wildcard Topologies/*.dot Topologies/*.png Topologies/*.txt) 

OBJ_PROG = $(SRC_PROG:.cpp=.o)

install:
	sudo apt-get update
	sudo apt-get install libcppunit-dev
	sudo apt-get install cmake g++ graphviz plantuml 
	sudo apt-get install doxygen
	sudo apt-get install libxml2-dev
	sudo apt-get install build-essential
	$(CD) Libs/igraph-0.8.0 && ./configure
	$(MAKE) -C Libs/igraph-0.8.0
	$(CD) Libs/igraph-0.8.0 && sudo $(MAKE) install
	$(shell export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib")
	@echo "****************Make Install Successful********************"

all: 
	$(MAKE) prog doc

prog: $(OBJ_PROG)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "****************Make Program Successful********************"   

doc: 
	$(CP) -rf Model readme.md licence.md Libs/DoxygenCMake
	$(CD) Doc && $(CMAKE) ../Libs/DoxygenCMake
	$(MAKEDOC) -C Doc 
	$(CXX) -o doc Doc/Doc.cpp
	$(CD) Libs/DoxygenCMake && $(RM) -rf Model readme.md licence.md
	@echo "********************Make Doc Successful********************"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	$(MAKE) clean_prog clean_doc clean_topologies
	
clean_prog :
	$(RM) -f prog $(OBJ_PROG) $(OBJ_TEST)
	@echo "************Clean Program And Test Successful**************"

clean_doc : 
	$(RM) -rf $(filter-out Doc/Doc.cpp, $(wildcard Doc/*) )
	$(RM) -f doc
	@echo "*******************Clean Doc Successful********************"

clean_topologies : 
	$(RM) -f $(SRC_TOPO)
	@echo "**************Clean Topologies Successful******************"