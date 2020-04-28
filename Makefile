ListGraph.out: AdjacencyList.o AdjacencyListGraph.o AdjacencyMatGraph.o DijkstraAlgorythm.o 
	g++ -g -Wall -pedantic -std=c++11 AdjacencyList.o AdjacencyListGraph.o main.cpp AdjacencyMatGraph.o DijkstraAlgorythm.o -o graph -lpanel -lcurses

AdjacencyList.o: AdjacencyList.hh AdjacencyList.cpp
	g++ -g -Wall -Iinc -pedantic -std=c++11 -c -o AdjacencyList.o AdjacencyList.cpp

AdjacencyListGraph.o: AdjacencyListGraph.hh AdjacencyListGraph.cpp 
	g++ -g -Wall -Iinc -pedantic -std=c++11 -c -o AdjacencyListGraph.o AdjacencyListGraph.cpp

AdjacencyMatGraph.o: AdjacencyMatGraph.hh AdjacencyMatGraph.cpp 
	g++ -g -Wall -Iinc -pedantic -std=c++11 -c -o AdjacencyMatGraph.o AdjacencyMatGraph.cpp

DijkstraAlgorythm.o: DijkstraAlgorythm.hh DijkstraAlgorythm.cpp 
	g++ -g -Wall -Iinc -pedantic -std=c++11 -c -o DijkstraAlgorythm.o DijkstraAlgorythm.cpp

clean:
	rm -f *.o  
