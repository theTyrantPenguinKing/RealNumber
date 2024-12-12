CXX = g++
CXXFLAGS = -Wall -std=c++17
EXENAME = prog.x86_64

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

$(EXENAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.x86_64 *.o
