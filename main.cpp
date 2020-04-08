#include <iostream>
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "DijkstraAlgorythm.hh"


using namespace std;

int main(){

 //   Edge e1;e1.first=2;e1.second=3;e1.weight=900;
    Edge e2;e2.first=2;e2.second=4;e2.weight=990;
    Edge e3;e3.first=4;e3.second=3;e3.weight=500;

    graph g(4);
    //g.List.FillListGraph(1);
   // g.MatGraph.AddEdge(e1);
    g.MatGraph.AddEdge(e2);g.MatGraph.AddEdge(e3);
    g.List.AddEdge(e2);g.List.AddEdge(e3);
    g.List.PrintListGraph();
    g.MatGraph.PrintGraph();
    
    g.choice=adjacencylist;
    int *tab=DijkstraAlgorythm(2,g);
  

      for(int i=0;i<4;i++){
        cout << "Odleglosc 2 od " << i+1 << " : "<< tab[i]<< endl ; 
    }


}