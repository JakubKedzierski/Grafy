#include <iostream>
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "DijkstraAlgorythm.hh"


using namespace std;

int main(){
    ListGraph ListGraph1(3);   
    ListGraph1.FillListGraph(0.75);
   // ListGraph1.PrintListGraph();
    
    
    AdjacencyMatGraph mat(1000);
   // mat.FillGraph(1);
    Edge e1;e1.first=2;e1.second=3;e1.weight=900;
    Edge e2;e2.first=2;e2.second=4;e2.weight=40;
    Edge e3;e3.first=4;e3.second=3;e3.weight=870;
    mat.AddEdge(e1);mat.AddEdge(e2);mat.AddEdge(e3);
    mat.FillGraph(1);
   // mat.PrintGraph();

    int *tab=DijkstraAlgorythm(1,mat);

    for(int i=0;i<20;i++){
      //  cout << "Odleglosc 1 od " << i+1 << " : "<< tab[i]<< endl ; 
    }
}