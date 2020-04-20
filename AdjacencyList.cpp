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
    for(int i=0;i<number+1;i++){
        TabOfLists[i]=NULL;
    }
    PossibleLoop=false;
}
ListGraph::~ListGraph()
{
    AdjacencyList *tmp,*tmp2;
    
    for(int i=1;i<NumberOfNodes+1;i++){
        tmp=TabOfLists[i];
        while(tmp){
            tmp2=tmp;
            tmp=tmp->next;
            delete tmp2;
        }
    }

    delete[] TabOfLists;
    
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

bool ListGraph::DetectEdge(int V1,int V2){
    AdjacencyList *tmp=new AdjacencyList; // tymczasowa lista zeby nie nadpisywac danych
    
    tmp=TabOfLists[V1];

       while(tmp){
           if(tmp->Vnode==V2){
               return true;
           }
           tmp=tmp->next;
       }
    return false;
}

/**
 * @brief myeslenie jak w macierzy
 * 
 * @param density 
 */
void ListGraph::FillGraph(double density){
    int **matrix=new int*[NumberOfNodes];
    for(int i=0;i<NumberOfNodes;i++){
        matrix[i]=new int[NumberOfNodes];
    }
   
    for(int i=0;i<NumberOfNodes;i++){
        for(int j=0;j<NumberOfNodes;j++){
            matrix[i][j]=0;
        }
    }
    

    double nv=NumberOfNodes,ne=nv*(nv-1)*density/2;
    srand( time( NULL ) );
    int loops=ne,row=0,col=0;

    int i=0,j=0;
    if(density==1){
        for(i=0;i<NumberOfNodes;i++){
            for(j=0;j<NumberOfNodes;j++){
                if(j!=i){
                    if(matrix[i][j]==0){
                        matrix[i][j]=15;
                        matrix[j][i]=15;
                    }
                }
            }
        }
    }else{
        while(loops){
            row=rand()%NumberOfNodes+1;
            col=rand()%NumberOfNodes+1;
            if(row!=col){
                if(matrix[row-1][col-1]==0){
                    matrix[row-1][col-1]=15;
                    matrix[col-1][row-1]=15;
                    loops--;
                }
            }
        } 
    }

    for(int i=0;i<NumberOfNodes;i++){
        for(int j=i+1;j<NumberOfNodes;j++){
            if(matrix[i][j]==15){
                AddEdge(i+1,j+1,rand()%1000+1);
            }
        }

    }

    for(int i=0;i<NumberOfNodes;i++){
        delete[] matrix[i];
    }

    delete[] matrix;
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