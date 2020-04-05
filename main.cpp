#include <iostream>
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "DijkstraAlgorythm.hh"


using namespace std;

int main(){
    ListGraph ListGraph1(3);   
    ListGraph1.FillListGraph(0.75);
    ListGraph1.PrintListGraph();
    
    AdjacencyMatGraph mat(3);
    mat.FillGraph(0.75);
    mat.PrintGraph();

}