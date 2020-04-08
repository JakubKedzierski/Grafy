#pragma once
#include "AdjacencyList.hh"
#include "AdjacencyMatGraph.hh"
#include "AdjacencyList.hh"

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

int* DijkstraAlgorythm(int Node,ListGraph *graph);
int* DijkstraAlgorythm(int Node,AdjacencyMatGraph *graph);