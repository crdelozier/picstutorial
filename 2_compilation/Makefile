CXXFLAGS = -std=c++11

all: debugging list

debugging: debugging.cpp
	g++ -o debugging debugging.cpp -g

list: main.o list.o
	g++ -o list main.o list.o

list.o: list.cpp
	g++ -c list.cpp $(CXXFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)

clean:
	rm debugging list *.o
