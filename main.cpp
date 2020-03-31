#include <iostream>
#include "AdjacencyList.hh"

using namespace std;

int main(){
    graph graph1(10);
    Edge edge;
    edge.first=1;edge.second=3;edge.weight=2;
    graph1.AddEdge(edge);
       graph1.PrintGraph();
    edge.first=1;edge.second=4;edge.weight=2;
    graph1.AddEdge(edge);
    graph1.PrintGraph();


}