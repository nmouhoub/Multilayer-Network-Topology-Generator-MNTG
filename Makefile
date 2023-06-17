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


mntg: $(OBJ_PROG)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "****************Make Program Successful********************"   

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<


clean :
	$(RM) -f mntg $(OBJ_PROG) $(OBJ_TEST)
	@echo "************Clean Program Successful**************"