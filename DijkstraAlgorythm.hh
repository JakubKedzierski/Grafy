#pragma once
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "AdjacencyList.hh"

enum choose{
    adjacencylist,
    adjacencymatrix
};

class graph{
public:
    choose choice;
    int NumberOfNodes;
    ListGraph List;
    AdjacencyMatGraph MatGraph;
    graph(int n){ListGraph g(n);List=g;AdjacencyMatGraph m(n);MatGraph=m;choice=adjacencymatrix;
                NumberOfNodes=n;}
};


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
    void push(int Node,int AddPriority);
    PriorityQueue(int MaxN){queue=new elem[MaxN];n=0;}
    ~PriorityQueue(){delete queue;}
    bool IsEmpty(){return n?false:true;}
    void PrintQueue();
};

int* DijkstraAlgorythm(int Node, graph graph1);