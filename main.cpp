#include <iostream>
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"


using namespace std;

int main(){
    ListGraph ListGraph1(10);
    
    ListGraph1.FillListGraph(1);
  // ListGraph1.PrintListGraph();
    
    AdjacencyMatGraph mat(20);
    mat.FillGraph(0.5);
    mat.PrintGraph();


}