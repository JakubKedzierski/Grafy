ListGraph.out: AdjacencyList.o AdjacencyMatGraph.o
	g++ -Wall -pedantic -std=c++11 -o graph AdjacencyList.o main.cpp AdjacencyMatGraph.o -lpanel -lcurses

obj/AdjacencyList.o: AdjacencyList.hh AdjacencyList.cpp 
	g++ -Wall -pedantic -std=c++11 -c -o AdjacencyList.o AdjacencyList.cpp

obj/AdjacencyMatGraph.o: AdjacencyMatGraph.hh AdjacencyMatGraph.cpp 
	g++ -Wall -pedantic -std=c++11 -c -o AdjacencyMatGraph.o AdjacencyMatGraph.cpp

clean:
	rm -f *.o 
