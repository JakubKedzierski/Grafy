#include <iostream>
#include "AdjacencyList.hh"
using namespace std;

graph::graph(int number){
    NumberOfNodes=number;
    List=new AdjacencyList [number];
}
graph::~graph()
{
    delete TabOfNodes;
}

void graph::AddEdge(edge Edge){
    AdjacencyList *elem=new AdjacencyList;
    
    elem->GetData()=nod2;
    elem->GetNext()=TabOfNodes[nod2-1]
    for(int i=0;i<NumberOfNodes;i++){

    }
}