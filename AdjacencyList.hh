#pragma once

/**
 * @brief Krawedz grafu reprezentowana jako dwa wierzcholki oraz wage
 * polaczenia
 * 
 */
class Edge
{
public:
    int V1,V2,weight;
};

/**
 * @brief Struktura bedaca elementem przechowywanym przez liste
 *        Na potrzeby programu przechowywana dana jest krawedz pomiedzy dwoma
 *        wierzcholkami 
 * 
 */
struct adjacencyListElem
{
    adjacencyListElem *next;
    Edge edge;
};


/**
 * @brief Lista jednokierunkowa, w mojej implementacji sluzy jako lista
 *        sasiedztwa, czy lista krawedzi danego wierzcholka
 * 
 */
class List{
public:
    adjacencyListElem *head;    
    void insertFront(Edge);  
    void Print();           
    List();
    ~List();
};