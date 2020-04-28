#pragma once
#include <iostream>
#include <iomanip>
#include "AdjacencyList.hh"
using namespace std;

/**
 * @brief Klasa bazowa - Graf jako pojecie ogolne
 *        W klasie zawarte podstawowe informacje o grafie tj. liczba wierzcholkow
 *        liczba krawedzi, wierzcholek poczatkowy oraz deklaracje metod wirtualnych
 */
class Graph{
protected:    
    int NumberOfNodes;
    int NumberOfEdges;
    int StartingNode; //     na potrzeby odczytania grafu z pliku i wyliczenia drogi
public:
    const int vertices()const{return NumberOfNodes;}
    const int edges()const{return NumberOfEdges;}
    const int GetStartingNode()const{return StartingNode;}
    void NewStartingNode(int Start){StartingNode=Start;}
    
    /* Metody wirtualne*/
    virtual void AddEdge(int,int,int)=0;               // dodanie krawedzi    
    virtual void PrintGraph()const=0;               // drukowanie grafu na stdout
    virtual void FillGraph(double density)=0;       // wypelnianie grafu
    virtual bool ReadFromFile(const char* name)=0;  // wczytanie z pliku
    virtual List incidentEdges(int)const=0;         // dostep do krawedzi wierzcholka
    virtual int opposite(int,Edge)const=0;          // przeciwny wierzcholek do zadanego
    virtual ~Graph(){}
    Graph(){}
    Graph(int N){NumberOfNodes=N;}
};
