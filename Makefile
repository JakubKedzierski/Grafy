ListGraph.out: AdjacencyList.o AdjacencyMatGraph.o DijkstraAlgorythm.o
	g++ -g -Wall -pedantic -std=c++17 AdjacencyList.o main.cpp AdjacencyMatGraph.o DijkstraAlgorythm.o -o graph -lpanel -lcurses

obj/AdjacencyList.o: AdjacencyList.hh AdjacencyList.cpp 
	g++ -g -Wall -Iinc -pedantic -std=c++17 -c -o AdjacencyList.o AdjacencyList.cpp

obj/AdjacencyMatGraph.o: AdjacencyMatGraph.hh AdjacencyMatGraph.cpp 
	g++ -g -Wall -Iinc -pedantic -std=c++17 -c -o AdjacencyMatGraph.o AdjacencyMatGraph.cpp

obj/DijkstraAlgorythm.o: DijkstraAlgorythm.hh DijkstraAlgorythm.cpp 
	g++ -g -Wall -Iinc -pedantic -std=c++17 -c -o DijkstraAlgorythm.o DijkstraAlgorythm.cpp

clean:
	rm -f *.o 
