#pragma once
#include "ListGraph.hh"
#include "graph.hh"

class AdjacencyList: public Edge
{
public:
    AdjacencyList *next;
    int top,weightTo; //wierzcholek

    AdjacencyList(){next=NULL;top=0;}

};

class ListGraph
{
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

    ListGraph(int number);
    ~ListGraph();
};


