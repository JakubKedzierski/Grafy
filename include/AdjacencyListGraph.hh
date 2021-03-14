#pragma once
#include "AdjacencyList.hh"
#include "graph.hh"


/**
 * @brief Reprezentacja grafu za pomoca listy sasiedztwa
 *        Klasa ta dziedziczy po klasie Graph, bedacej ogolniejszym
 *        pojeciem grafu, niezaleznie od jego reprezentacji
 * 
 */
class ListGraph:public Graph
{
protected:    
    // Tablica list sasiedztwa. Dla kazdego wierzcholka tablica przechowuje liste
    // jego krawedzi 
    List* TabOfLists;
public:
    // Opis poszczegolnych metod znajduje sie w pliku zrodlowym
    ListGraph(){} 
    ListGraph(int number);
    ~ListGraph();
    bool DetectEdge(int,int);


    /* Metody wirtualne */
    void RemoveEdge(int,int);    
    void AddEdge(int,int,int);
    List incidentEdges(int Node)const;
    void PrintGraph()const;
    int opposite(int ,Edge)const;
    void FillGraph(double density);
    bool ReadFromFile(const char* name);
};


