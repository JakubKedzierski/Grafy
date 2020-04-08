#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Edge
{
public:
    int first,second,weight;
};
/*
class Graph{
protected:    
    int NumberOfNodes;
    int NumberOfEdges;
    double Density;
public:
    const int GetNumberOfNodes()const{return NumberOfNodes;}
    const int GetNumberOfEdges()const{return NumberOfEdges;}
    const double GetDensity()const{return Density;}
    virtual void PrintGraph();
//  virtual void FillGraph();
    virtual ~Graph();
    Graph();
   // Graph()
};
*/