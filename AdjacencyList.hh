#include "graph.hh"

class AdjacencyList: public edge
{
private:
    AdjacencyList *next;
    int top; //waga ilosc km np
public:
    AdjacencyList *GetNext(){return next;}
    AdjacencyList(){next=NULL;top=0;}
    int GetTop(){return top;}
};

class graph
{
    int NumberOfNodes;
public:
    int GetNumberOfNodes(){return NumberOfNodes;}
    AdjacencyList *List; // na prywatne

    void AddEdge(int nod1,int nod2);

    graph(int number);
    ~graph();
};

