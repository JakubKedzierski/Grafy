#include <iostream>
#include "AdjacencyList.hh"
using namespace std;

graph::graph(int number){
    NumberOfNodes=number;
    List=new AdjacencyList* [number];
    PossibleLoop=false;
}
graph::~graph()
{
    delete List;
}

void graph::AddEdge(Edge edge){
    
    if(edge.first==edge.second &&!PossibleLoop){
        cout << "Graf bez petli! Nie mozna dodac krawedzi";
        return;
    }

    AdjacencyList *Node=new AdjacencyList;
    Node->top=edge.second; // dodanie drugiego wierzcholka
    Node->next=List[edge.first-1];       // Dodanie w drugim wskaznika na pierwszy (sasiad pierwszego)    
                                            // dodajemy wierzcholki na poczatek listy 
    List[edge.first-1]=Node;

    /* To samo z drugim wierzcholkiem*/
    Node=new AdjacencyList;
    Node->top=edge.first; 
    Node->next=List[edge.second-1];     
                                            
    List[edge.second-1]=Node;


}

void graph::PrintGraph(){
 AdjacencyList *tmp=new AdjacencyList; // tymczasowa lista zeby nie nadpisywac danych
    cout << endl << "graf" << endl;
    for(int i=0;i<NumberOfNodes;i++){
       cout << endl <<  i+1 << ":";
       tmp=List[i];
        
        if(!tmp){
            cout << "NULL";
        }

       while(tmp){
           cout << tmp->top ;
           tmp=tmp->next;
           if(tmp) 
            cout <<  ", ";
       }
    }
    delete tmp;
    cout << endl;
}