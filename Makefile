graph.out: AdjacencyList.o 
	g++ -Wall -pedantic -std=c++11 -o graph AdjacencyList.o main.cpp -lpanel -lcurses

obj/AdjacencyList.o: AdjacencyList.hh AdjacencyList.cpp 
	g++ -Wall -pedantic -std=c++11 -c -o AdjacencyList.o AdjacencyList.cpp

clean:
	rm -f *.o 
