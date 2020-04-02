#pragma once
#include "graph.hh"
const int maxweight =1000;

class AdjacencyMatGraph
{
    int NumberOfNodes;
    int NumberOfEdges;
    bool PossibleLoop;
    int **matrix;
public:
    int **GetMatrix(){return matrix;}
    void AddEdge(Edge edge);

    AdjacencyMatGraph(int NumOfNodes);
    ~AdjacencyMatGraph();
    void FillGraph(double density);
    void PrintGraph();
};


