#pragma once
#include "ListGraph.hh"
#include "graph.hh"

class AdjacencyList: public Edge
{
public:
    AdjacencyList *next;
    int Vnode,weightTo; //wierzcholek

    AdjacencyList(){next=NULL;Vnode=0;}
   /* AdjacencyList(const AdjacencyList &List){next=new AdjacencyList;next=List.next;Vnode=List.Vnode;weightTo=List.weightTo;}*/
};

class ListGraph
{
protected:    
    int NumberOfNodes;
    int NumberOfEdges;
    bool PossibleLoop;
public:
    int &GetNumberOfNodes(){return NumberOfNodes;}
    AdjacencyList **List; //tablica z listami powiazan

    void AddEdge(Edge edge);
    void PrintListGraph();
    void FillListGraph(double density);
    bool DetectEdge(Edge edge);
    const int GetNumEdg(){return NumberOfEdges;}

    ListGraph(const ListGraph &graph);
    ListGraph();
    ListGraph(int number);
    ~ListGraph();
};


