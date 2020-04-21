#pragma once

class Edge
{
public:
    int V1,V2,weight;
};

struct adjacencyListElem
{
    adjacencyListElem *next;
    Edge edge;
};


class List{
public:
    adjacencyListElem *head;    
    void insertFront(Edge);
    adjacencyListElem* Head(){return head;}
    void Print();
    List();
    ~List();
};