#pragma once
#include "ListGraph.hh"
#include "graph.hh"

struct AdjacencyList
{
    AdjacencyList *next;
    int Vnode,weightTo; //wierzcholek

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
    bool DetectEdge(int,int);

    /* Metody wirtualne */
    void PrintGraph();
    void FillGraph(double density);
    bool ReadFromFile(const char* name);
};


