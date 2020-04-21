#pragma once
#include <iostream>
#include <iomanip>
#include "AdjacencyList.hh"
using namespace std;

class Graph{
protected:    
    int NumberOfNodes;
    int NumberOfEdges;
    bool PossibleLoop;
    int StartingNode; //     na potrzeby odczytania grafu z pliku i wyliczenia drogi
public:
    const int GetNumberOfNodes()const{return NumberOfNodes;}
    const int GetNumberOfEdges()const{return NumberOfEdges;}
    const int GetStartingNode()const{return StartingNode;}
    void NewStartingNode(int Start){StartingNode=Start;}
    virtual void PrintGraph()const=0;
    virtual void FillGraph(double density)=0;
    virtual bool ReadFromFile(const char* name)=0;
    virtual List incidentEdges(int)const=0;
    virtual ~Graph(){}
    Graph(){}
    Graph(int N){NumberOfNodes=N;}
};
