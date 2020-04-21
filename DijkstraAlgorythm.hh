#pragma once
#include "AdjacencyMatGraph.hh"
#include "AdjacencyListGraph.hh"

struct elem
{
    int Node;
    int priority;
};

class PriorityQueue{
private:
    elem *queue;
    int n; //ilosc elementow
    int MaxSize;
public:
    elem pop();
    void push(int Node,int AddPriority);
    PriorityQueue(int MaxN){queue=new elem[MaxN];n=0;MaxSize=MaxN;} 
    ~PriorityQueue(){delete queue;}
    bool IsEmpty(){return n?false:true;}
    void PrintQueue();
    void IncreaseSize(int n);
};

int* DijkstraAlgorythm(int Node,ListGraph *graph,int *ParenTab);
int* DijkstraAlgorythm(int Node,AdjacencyMatGraph *graph,int *ParenTab);
void PrintPath(ostream& os,int source,int* ParentTab);
bool WriteDijkstraOut(Graph*,const char*);