CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11
SRC= src/server.cc src/main.cc
OBJ= $(SRC:.cc=.o)
EXEC=serv

all: $(EXEC)

clean:
	rm $(EXEC) $(OBJ)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS)
