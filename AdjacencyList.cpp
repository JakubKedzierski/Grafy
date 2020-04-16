#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include "AdjacencyList.hh"
#include "graph.hh"

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


void ListGraph::AddEdge(int first,int second,int weight){

    if(first==second &&!PossibleLoop){
        cout << "Graf bez petli! Nie mozna dodac krawedzi";
        return;
    }

    AdjacencyList *Node=new AdjacencyList;
    Node->Vnode=second; // dodanie drugiego wierzcholka
    Node->weightTo=weight;
    Node->next=TabOfLists[first];       // Dodanie w drugim wskaznika na pierwszy (sasiad pierwszego)    
                                            // dodajemy wierzcholki na poczatek listy 
    TabOfLists[first]=Node;

    /* To samo z drugim wierzcholkiem*/
    Node=new AdjacencyList;
    Node->Vnode=first;
    Node->weightTo=weight; 
    Node->next=TabOfLists[second];     
                                            
    TabOfLists[second]=Node;
    NumberOfEdges++;
}

void ListGraph::PrintGraph(){
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


void ListGraph::FillGraph(double density){
    // Moj algorytm wypelniania listy dziala na tej samej zasadzie co wypelnianie macierzy sasiedztwa
    // W pliku AdjacencyMatGraph.cpp znajduje sie dokladniejszy opis tego algorytmu
    double nv=NumberOfNodes,ne=nv*(nv-1)*density/2;

    srand( time( NULL ) );
    int EndOfMatrix=NumberOfNodes,Jump=2;  
    int RandNum=2,AllEdges=(NumberOfNodes*(NumberOfNodes-1))/2; // AllEdges - wszystkie krawedzie (nie liczymy podwojnie jednej krawedzi)
    int *AllEdgesTab=new int [AllEdges];

    srand( time( NULL ) );

    for(int i=0;i<AllEdges;i++){
        AllEdgesTab[i]=RandNum;
        RandNum++;
        if(RandNum>EndOfMatrix){
            EndOfMatrix+=NumberOfNodes;
            RandNum+=Jump;
            Jump++;
        }
    }

    int Num=ne,row=0,col=0,iterator=0;
    double choice;
 
    while(Num){
        iterator++;                   // licznik przejscia petli -> do zmniejszania liczby dostepnych krawedzi  
        RandNum=rand() %Num;          // wybieramy krawedz ze zbioru 
        choice=AllEdgesTab[RandNum];
        AllEdgesTab[RandNum]=AllEdgesTab[AllEdges-iterator];      // Wyrzucamy wylosowana krawedz poza tablice
        --Num;                                    // i zmniejszamy liczbe dostepnnych krawedzi do losowania                              
        row=ceil(choice/NumberOfNodes)-1;
        col=choice-row*NumberOfNodes-1;
        AddEdge(row+1,col+1,(rand()%1000+1));
    }
    
}


bool ListGraph::ReadFromFile(const char* name){
    
    ifstream file;
    file.open(name,ifstream::in);
    
    if(!file.good()) return false;

    int BuffNumb[3];
    string buffer;
    file >> BuffNumb[0] >> BuffNumb[1] >> StartingNode;
    StartingNode++; //numeracja od 0
    
    if(!file.good()) return false;  // zabezpieczenie
    
    NumberOfNodes=BuffNumb[1];
    getline(file,buffer);
    
    TabOfLists=new AdjacencyList* [NumberOfNodes+1];

    while(file.good()){
        file >> BuffNumb[0] >> BuffNumb[1] >> BuffNumb[2];
        AddEdge(BuffNumb[0]+1,BuffNumb[1]+1,BuffNumb[2]);    // +1 poniewaz w wymaganiach jest numeracja od 0 a moja implementacja
                                                        // zaklada numeracje od 1  
        getline(file,buffer);
    }

    file.close();
    return true;
}