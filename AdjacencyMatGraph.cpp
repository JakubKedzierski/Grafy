#include <iostream>
#include <fstream>
#include <cstdlib>
#include "AdjacencyMatGraph.hh"
#include <ctime>
#include <cmath>
using namespace std;

AdjacencyMatGraph::AdjacencyMatGraph(const AdjacencyMatGraph &graph){    
 
    NumberOfNodes=graph.NumberOfNodes;
    matrix=new Edge **[NumberOfNodes];
    for(int i=0;i<NumberOfNodes;i++){
        matrix[i]=new Edge*[NumberOfNodes];   
    } 
        for(int i=0;i<NumberOfNodes;i++){
            for(int j=0;j<NumberOfNodes;j++){
                if(matrix[i][j])
                    matrix[i][j]=new Edge;
            }
        }     
   (*this)=graph;

}


AdjacencyMatGraph::AdjacencyMatGraph(int NumOfNodes){
    NumberOfNodes=NumOfNodes;
    NumberOfEdges=0;
    StartingNode=1;
    PossibleLoop=false;
    matrix=new Edge **[NumberOfNodes];
    for(int i=0;i<NumberOfNodes;i++){
        matrix[i]=new Edge*[NumberOfNodes];
    }
    for(int i=0;i<NumberOfNodes;i++){
            for(int j=0;j<NumberOfNodes;j++){
                matrix[i][j]=NULL;
        }
    }
}

AdjacencyMatGraph::~AdjacencyMatGraph(){
    for(int i=0;i<NumberOfNodes;i++){
        for(int j=0;j<NumberOfNodes;j++){
            if(matrix[i][j])
                delete[] matrix[i][j];
        }
    }

    for(int i=0;i<NumberOfNodes;i++){
        delete[] matrix[i];
    }

    delete[] matrix;
}

void AdjacencyMatGraph::AddEdge(int first,int second, int weight){
    if(first!=second){
        matrix[first-1][second-1]=new Edge;
        matrix[first-1][second-1]->V1=first;
        matrix[first-1][second-1]->V2=second;
        matrix[first-1][second-1]->weight=weight;
        matrix[second-1][first-1]=new Edge;
        matrix[second-1][first-1]->weight=weight;
        matrix[second-1][first-1]->V1=second;
        matrix[second-1][first-1]->V2=first;
        NumberOfEdges++;
    }
}

void AdjacencyMatGraph::PrintGraph(){
cout << endl << "Macierz sasiedztwa:" << endl;   
    for (int i=0;i<NumberOfNodes+1;i++){
        cout <<setw(4) << i<< "|" ;
    }
    cout << endl;
        for(int i=0;i<NumberOfNodes;i++){
            cout << setw(4) << i+1 << "|";   
            for(int j=0;j<NumberOfNodes;j++){
                    if(!matrix[i][j]){
                        cout << " NULL";
                    }else{
                        cout << setw(5) << (*matrix[i][j]).weight;
                    }
            }
            cout << endl;
        }
}

/**
 * @brief Przy wypelnianu grafu zastosowalem metode losowania ze zbioru, po to aby nie powtarzaly sie
 * wyniki losowania oraz aby uniknac petli w grafie 
 * 
 * Algorytm polega na losowaniu krawedzi -> wylosowana krawedz zostaje wyrzucona z puli dostepnych 
 * krawedzi
 * 
 * Dostepne krawedzi to pola w macierzy sasiedztwa. Mozna dostrzec, ze ta macierz jest symetryczna i 
 * wystarczy wybierac krawedz w gornej czesci
 * 
 * 
 * @param density 
 */
void AdjacencyMatGraph::FillGraph(double density){
    double nv=NumberOfNodes,ne=nv*(nv-1)*density/2;
    srand( time( NULL ) );

    if(density==1){
        for(int i=0;i<NumberOfNodes;i++){
            for(int j=0;j<NumberOfNodes;j++){
                if(i!=j){
                    if(!matrix[i][j]){
                        AddEdge(i+1,j+1,(rand()%1000+1));
                    }
                }
            }
        }
        return;
    }

    int loops=ne,row=0,col=0;
    while(loops){
        row=rand()%NumberOfNodes+1;
        col=rand()%NumberOfNodes+1;
        if(row!=col){
            if(!matrix[row-1][col-1]){
                AddEdge(row,col,rand()%1000+1);
                loops--;
            }
        }
    } 

}

bool AdjacencyMatGraph::ReadFromFile(const char* name){

    ifstream file;
    file.open(name,ifstream::in);
    if(!file.good()) return false;

    int BuffNumb[3];
    string buffer;
    file >> BuffNumb[0] >> BuffNumb[1] >> StartingNode;
    StartingNode++;
    if(!file.good()) return false;  // zabezpieczenie
        
    NumberOfNodes=BuffNumb[1];
    getline(file,buffer);
    
    matrix= matrix=new Edge **[NumberOfNodes];       // alokacja miejsca na wczytany graf
    for(int i=0;i<NumberOfNodes;i++){
        matrix[i]=new Edge*[NumberOfNodes];
    }

    while(file.good()){                                          // zakladam ze dane w pliku tekstowym sa poprawne (nie skupiam
                                                                // sie na obsludze bledow)
        file >> BuffNumb[0] >> BuffNumb[1] >> BuffNumb[2];
        AddEdge(BuffNumb[0]+1,BuffNumb[1]+1,BuffNumb[2]);  // +1 poniewaz w wymaganiach jest numeracja od 0 a moja implementacja
                                                             // zaklada numeracje od 1 
        getline(file,buffer);
    }

    file.close();
    return true;
}

