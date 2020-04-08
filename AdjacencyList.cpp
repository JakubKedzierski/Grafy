#include <iostream>
#include <cstdlib>
#include "AdjacencyList.hh"
#include "graph.hh"
#include <ctime>
#include <unistd.h>
using namespace std;
ListGraph::ListGraph(){}

ListGraph::ListGraph(int number){
    NumberOfNodes=number;
    TabOfLists=new AdjacencyList* [number+1];
    PossibleLoop=false;
}
ListGraph::~ListGraph()
{
    //delete List;
}


ListGraph::ListGraph(const ListGraph &graph){
    NumberOfNodes=graph.NumberOfNodes;
    NumberOfEdges=graph.NumberOfEdges;
    PossibleLoop=false;    
    TabOfLists=new AdjacencyList* [NumberOfNodes+1];
    TabOfLists=graph.TabOfLists;
}


void ListGraph::AddEdge(Edge edge){

    if(edge.first==edge.second &&!PossibleLoop){
        cout << "Graf bez petli! Nie mozna dodac krawedzi";
        return;
    }

    AdjacencyList *Node=new AdjacencyList;
    Node->Vnode=edge.second; // dodanie drugiego wierzcholka
    Node->weightTo=edge.weight;
    Node->next=TabOfLists[edge.first];       // Dodanie w drugim wskaznika na pierwszy (sasiad pierwszego)    
                                            // dodajemy wierzcholki na poczatek listy 
    TabOfLists[edge.first]=Node;

    /* To samo z drugim wierzcholkiem*/
    Node=new AdjacencyList;
    Node->Vnode=edge.first;
    Node->weightTo=edge.weight; 
    Node->next=TabOfLists[edge.second];     
                                            
    TabOfLists[edge.second]=Node;


}

void ListGraph::PrintListGraph(){
 AdjacencyList *tmp=new AdjacencyList; // tymczasowa lista zeby nie nadpisywac danych
    
    cout << endl << "Graf reprezentowany na liscie sasiedztwa" << endl;
    cout << "[wierzcholek: wierzcholek sasiadujacy -> waga polaczenia, nastepny sasiad ...]" << endl;
    for(int i=1;i<NumberOfNodes+1;i++){
       cout << endl <<  i << ":";
       tmp=TabOfLists[i];
        
        if(!tmp){
            cout << "NULL";
        }

       while(tmp){
           cout << " " <<tmp->Vnode << "->" << tmp->weightTo;
           tmp=tmp->next;
           if(tmp) 
            cout <<  ", ";
       }
    }
    delete tmp;
    cout << endl;
}

bool ListGraph::DetectEdge(Edge edge){
    AdjacencyList *tmp=new AdjacencyList; // tymczasowa lista zeby nie nadpisywac danych
    
    tmp=TabOfLists[edge.first];

       while(tmp){
           if(tmp->Vnode==edge.second){
               return true;
           }
           tmp=tmp->next;
       }
    return false;
}

void ListGraph::FillListGraph(double density){
    int counter=0; 
    NumberOfEdges=NumberOfNodes*(NumberOfNodes-1)*density/2;
    srand( time( NULL ) );
    Edge edge1;
    int *first =new int[NumberOfNodes+1],*second=new int[NumberOfNodes+1];
    int ToRand=NumberOfNodes;
    
    for(int i=1;i<NumberOfNodes+1;i++){
        first[i]=i;
        second[i]=i;
    }

 // Dla pelnych grafow  
    if((int)density){ // dla pelnego grafu
        for(int i=1;i<NumberOfNodes;i++){
            for(int j=i+1;j<NumberOfNodes+1;j++){
                edge1.weight=rand() %1000;
                edge1.first=i;
                edge1.second=j;
                AddEdge(edge1);
            }
        }
        return;
    }


// niewydajna
    for(int i=0;i<NumberOfEdges;i++){
        edge1.weight=rand() %1000+1;
        edge1.first=first[rand()%ToRand+1];
        edge1.second=second[rand()%ToRand+1];
        
        if((edge1.second==edge1.first) && (!PossibleLoop)){
            if(edge1.second<NumberOfNodes){
                edge1.second++;
            }else{
                edge1.second--;
            }
        }

        counter=0;
        while(DetectEdge(edge1)){
            
            counter++;
            edge1.second=second[rand()%ToRand+1];
         
            if((edge1.second==edge1.first) && (!PossibleLoop)){
                if(edge1.second<NumberOfNodes){
                    edge1.second++;
                }else{
                    edge1.second--;
                }
            }
            if(counter==NumberOfNodes-1){
                break;
            }
        }

        if(!(counter==NumberOfNodes-1)){
            AddEdge(edge1);
        }else{
            i--;
            first[edge1.first]=first[ToRand];
            second[edge1.first]=second[ToRand];
            ToRand--;
            
            if(!ToRand)
            return;
        }
        

    }

    
//for(int i=0;i<NumOfEdges;i++){
  //  cout << edges[i].first << "  " << edges[i].second << "  " << edges[i].weight << endl;
//}
}
