CXX = g++
CXXFLAGS = -Wall -std=c++11
EXENAME = prog

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

$(EXENAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXENAME) $(OBJ)

rebuild:
	make clean
	make

.PHONY: clean rebuild
