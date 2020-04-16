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
    
    //graph1->FillGraph(1);
   
 /*  
    dynamic_cast <ListGraph*>(graph1)->AddEdge(2,3,900);
    dynamic_cast <ListGraph*>(graph1)->AddEdge(2,4,50);
    dynamic_cast <ListGraph*>(graph1)->AddEdge(4,3,30);
*/    

    WriteDijkstraToFile(graph1);

}