#pragma once
#include "AdjacencyMatGraph.hh"
#include "AdjacencyListGraph.hh"

/**
 * @brief Kolejka priorytetowa zaimplementowana na kopcu (kopiec na tablicy). 
 * Kolejke zaimplementowano na potrzeby uzycia w algorytmie Dijkstry, dlatego jej korzeniem
 * jest element o najmniejszym kluczu (wadze krawedzi). 
 */
class PriorityQueue{
private:
    Edge *queue;     // kolejka ktorej elementami sa krawedzie (za klucz uznajemy wage krawedzi)
    int n;          //ilosc elementow w kolejce
    int MaxSize; // maksymalny rozmiar kolejki 
public:
    Edge pop(); // zwraca najmniejszy element kolejki
    void push(Edge);
    void replaceKey(int,int);
    PriorityQueue(int MaxN){queue=new Edge[MaxN];n=0;MaxSize=MaxN;} 
    ~PriorityQueue(){delete queue;}
    bool IsEmpty(){return n?false:true;}
    void PrintQueue();
    void IncreaseSize();      
};

// Naglowki funkcji przeliczajacych najkrotsza sciezke w grafie
int* DijkstraAlgorythm(int Node,Graph *graph,int *ParentTab);
void PrintPath(ostream& os,int source,int* ParentTab);
bool WriteDijkstraOut(Graph*,const char*);