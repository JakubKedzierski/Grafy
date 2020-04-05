#pragma once
#include "graph.hh"
const int maxweight =1000;

class AdjacencyMatGraph
{
protected:    
    int NumberOfNodes;
    int NumberOfEdges;
    bool PossibleLoop;
    int **matrix;
public:
    int **GetMatrix(){return matrix;}
    void AddEdge(Edge edge);

    AdjacencyMatGraph();
    AdjacencyMatGraph(int NumOfNodes);
    ~AdjacencyMatGraph();
    AdjacencyMatGraph(const AdjacencyMatGraph &graph);    
    void FillGraph(double density);
    void PrintGraph();
};


