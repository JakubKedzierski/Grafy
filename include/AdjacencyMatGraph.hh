#pragma once
#include "graph.hh"
#include "AdjacencyList.hh"

/**
 * @brief Graf reprezentowany na macierzy sasiedztwa. Macierz sasiedztwa przedstawiona jako
 *        dwuwymiarowa tablica wskaznikow na krawedzie. Gdy pole macierzy jest puste (NULL) - brak krawedzi.
 *        Gdy pole zawiera krawedz to w obiekcie krawedzi sa dokladniejsze informacje np. o wadze krawdzi, czy 
 *        wierzcholkach jakie dana krawedz laczy.
 */
class AdjacencyMatGraph:public Graph
{
protected:    
    Edge ***matrix; 
public:

    AdjacencyMatGraph(){}
    AdjacencyMatGraph(int NumOfNodes);
    ~AdjacencyMatGraph();
    
    /* Metody wirtualne */
    void RemoveEdge(int,int);    
    void AddEdge(int,int,int);    
    List incidentEdges(int Node)const; 
    void FillGraph(double density);
    void PrintGraph()const;
    bool ReadFromFile(const char* name);
    int opposite(int,Edge)const;
};


