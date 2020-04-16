#include <iostream>
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "DijkstraAlgorythm.hh"


using namespace std;

int FindBestWayBetween(int Node1,int Node2,Graph* graph){
    int *tab=DijkstraAlgorythm(Node1,dynamic_cast <ListGraph*>(graph));
    return tab[Node2-1];
}



int main(){

    Graph *graph1=new AdjacencyMatGraph();
    if(!graph1->ReadFromFile("graf.txt"))    
    cerr << endl << "Operacja zakonczyla sie niepowodzeniem. Najprawdopodobniej zla nazwa pliku." << endl;
    

    graph1->PrintGraph();
    WriteDijkstraToFile(graph1);

}