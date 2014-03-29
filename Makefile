CXX=clang++
CXXFLAGS=-Wall -pedantic -std=c++11 -g
LDXXFLAGS= -lboost_thread
SRC= src/server.cc src/main.cc
OBJ= $(SRC:.cc=.o)
EXEC=serv

all: $(EXEC)

clean:
	rm $(EXEC) $(OBJ)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDXXFLAGS)

%.o: %.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS)
