#pragma once
#include "AdjacencyList.hh"
#include "graph.hh"

class ListGraph:public Graph
{
protected:    
    List* TabOfLists; //tablica z listami powiazan , iterujemy od 1.
public:
 
    ListGraph();
    ListGraph(int number);
    ListGraph(const ListGraph &graph);
    ~ListGraph();
    void AddEdge(int,int,int);
    bool DetectEdge(int,int);

    /* Metody wirtualne */
    List incidentEdges(int Node)const;
    void PrintGraph()const;
    void FillGraph(double density);
    bool ReadFromFile(const char* name);
};


