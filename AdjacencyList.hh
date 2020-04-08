#pragma once
#include "ListGraph.hh"
#include "graph.hh"

class AdjacencyList: public Edge
{
public:
    AdjacencyList *next;
    int Vnode,weightTo; //wierzcholek

    AdjacencyList(){next=NULL;Vnode=0;}
};

class ListGraph//:public Graph
{
protected:    
    int NumberOfNodes;
    int NumberOfEdges;
    bool PossibleLoop;
    AdjacencyList **TabOfLists; //tablica z listami powiazan , iterujemy od 1.
public:
    int GetNumberOfNodes(){return NumberOfNodes;}
    AdjacencyList* GetListOfAdjacency(int Node){return TabOfLists[Node];}
    void AddEdge(Edge edge);
    void PrintGraph();
    void FillListGraph(double density);
    bool DetectEdge(Edge edge);
    const int GetNumEdg(){return NumberOfEdges;}

    ListGraph(const ListGraph &graph);
    ListGraph();
    ListGraph(int number);
    ~ListGraph();
};


