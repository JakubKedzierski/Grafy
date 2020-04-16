#pragma once
#include "ListGraph.hh"
#include "graph.hh"

struct AdjacencyList
{
    AdjacencyList *next;
    int Vnode,weightTo; //wierzcholek
    AdjacencyList(){next=NULL;Vnode=0;}
};

class ListGraph:public Graph
{
protected:    
    AdjacencyList **TabOfLists; //tablica z listami powiazan , iterujemy od 1.
public:
 
    ListGraph();
    ListGraph(int number);
    ListGraph(const ListGraph &graph);
    ~ListGraph();
    AdjacencyList* GetListOfAdjacency(int Node){return TabOfLists[Node];}
    void AddEdge(int,int,int);
    bool DetectEdge(Edge edge);

    /* Metody wirtualne */
    void PrintGraph();
    void FillGraph(double density);
    bool ReadFromFile(const char* name);
};


