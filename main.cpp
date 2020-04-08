#include <iostream>
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "DijkstraAlgorythm.hh"


using namespace std;

int FindBestWayBetween(int Node1,int Node2,Graph* graph){
    int *tab=DijkstraAlgorythm(Node1,dynamic_cast <AdjacencyMatGraph*>(graph));
    return tab[Node2-1];
}

int main(){

    Edge e1;e1.first=2;e1.second=3;e1.weight=900;
    Edge e2;e2.first=2;e2.second=4;e2.weight=40;
    Edge e3;e3.first=4;e3.second=3;e3.weight=500;


    Graph *graph1=new AdjacencyMatGraph(4);
    dynamic_cast <AdjacencyMatGraph*>(graph1)->AddEdge(e1);
    dynamic_cast <AdjacencyMatGraph*>(graph1)->AddEdge(e2);
    dynamic_cast <AdjacencyMatGraph*>(graph1)->AddEdge(e3);
    
    graph1->PrintGraph();
    cout << FindBestWayBetween(2,3,graph1) << endl;

}