#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Edge
{
public:
    int V1,V2,weight;
};

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
    virtual void PrintGraph()=0;
    virtual void FillGraph(double density)=0;
    virtual bool ReadFromFile(const char* name)=0;
    virtual ~Graph(){}
    Graph(){}
    Graph(int N){NumberOfNodes=N;}
};
