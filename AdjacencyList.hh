#include "graph.hh"

class AdjacencyList: public Edge
{
public:
    AdjacencyList *next;
    int top; //wierzcholek

    AdjacencyList(){next=NULL;top=0;}

};

class graph
{
    int NumberOfNodes;

public:
    bool PossibleLoop;
    int GetNumberOfNodes(){return NumberOfNodes;}
    AdjacencyList **List; //tablica z listami powiazan

    void AddEdge(Edge edge);
    void PrintGraph();


    graph(int number);
    ~graph();
};

