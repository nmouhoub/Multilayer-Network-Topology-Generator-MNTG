CXX = g++        
INCLUDES =  -I/usr/local/include
CXXFLAGS = -g -Wall -Wextra -std=c++17
LDFLAGS = -L/usr/local/lib 
LDLIBS = -ligraph -pthread -ldl 
MAKEDOC = make doc
CMAKE = cmake 
MKDIR = mkdir
MAKE = make
CD = cd
CP = cp
RM = rm

SRC_PROG = $(wildcard src/*.cpp)
OBJ_PROG = $(SRC_PROG:.cpp=.o)

all: 
	$(MAKE) mntg doc

mntg: $(OBJ_PROG)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "****************Make Program Successful********************"   

doc: 
	$(CP) -rf src readme.md licence.md lib/DoxygenCMake
	$(CD) doc && $(CMAKE) ../lib/DoxygenCMake
	$(MAKEDOC) -C doc 
	$(CXX) -o doc doc/doc.cpp
	$(CD) libs/DoxygenCMake && $(RM) -rf model readme.md licence.md
	@echo "********************Make Doc Successful********************"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

clean_all : clean clean_doc

clean :
	$(RM) -f mntg $(OBJ_PROG) $(OBJ_TEST)
	@echo "************Clean Program And Test Successful**************"

clean_doc : 
	$(RM) -rf $(filter-out doc/doc.cpp, $(wildcard doc/*) )
	@echo "*******************Clean Doc Successful********************"
