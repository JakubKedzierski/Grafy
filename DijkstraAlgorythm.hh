#pragma once
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "AdjacencyList.hh"

/*
class graph{
    ListGraph List;
    AdjacencyMatGraph MatGraph;
public:
    ListGraph &GetList(){return List;}
    AdjacencyMatGraph &GetMatGraph(){return MatGraph;}
    graph(int n){ListGraph g(n);List=g;AdjacencyMatGraph m(n);MatGraph=m;}
};
*/

struct elem
{
    int Node;
    int priority;
};

class PriorityQueue{
private:
    elem *queue;
    int n; //ilosc elementow
public:
    elem pop();
    void push(int AddData,int AddPriority);
    PriorityQueue(int MaxN){queue=new elem[MaxN];n=0;}
    ~PriorityQueue(){delete queue;}
};

void DijkstraAlgorythm(int n,int Node, AdjacencyMatGraph graph1);