#include <iostream>
#include <cstdlib>
#include "AdjacencyMatGraph.hh"
#include <ctime>
using namespace std;

AdjacencyMatGraph::AdjacencyMatGraph(int NumOfNodes){
    NumberOfNodes=NumOfNodes;
    NumberOfEdges=0;
    PossibleLoop=false;
    matrix=new int *[NumberOfNodes];
    for(int i=0;i<NumberOfNodes;i++){
        matrix[i]=new int[NumberOfNodes];
    }
    for(int i=0;i<NumberOfNodes;i++){
        for(int j=0;j<NumberOfNodes;j++){
            matrix[i][j]=maxweight; // maxweight ustawione jako flaga swiadczace ze dane pole jest puste 
        }                           // zgodnie z konwencja ze gdy mozliwe sa petle w grafie waga polaczenia = 0
    }                               // a brak polaczenia to nieskonczonosc (w przypadku tej implementacji -> maxweight)
}

AdjacencyMatGraph::~AdjacencyMatGraph(){
    for(int i=0;i<NumberOfNodes;i++){
        delete matrix[i];
    }
    delete matrix;
}

void AdjacencyMatGraph::AddEdge(Edge edge){
    if(edge.first!=edge.second){
        matrix[edge.first][edge.second]=edge.weight;
    }else{
        matrix[edge.first][edge.second]=0;
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
                    cout << setw(5) << matrix[i][j];
            }
            cout << endl;
        }
}


void AdjacencyMatGraph::FillGraph(double density){
    NumberOfEdges=NumberOfNodes*(NumberOfNodes-1)*density/2;
    srand( time( NULL ) );

    if(density==1){
        for(int i=0;i<NumberOfNodes;i++){
            for(int j=0;j<NumberOfNodes;j++){
                if(i!=j){
                    matrix[i][j]=rand() %maxweight+1;
                }
            }
                
        }
        return ;
    }

// Trzeba naprawic wypelnianie dla innych przypadkow
    double point=0,col,nex; 
    for(int i=0;i<NumberOfEdges;i++){
        point=rand()%(NumberOfNodes*(NumberOfNodes-1));
        nex=point/NumberOfNodes;
        col=int((point/NumberOfNodes))%NumberOfNodes;
        matrix[(int)(nex)][(int)(col)]=rand() %maxweight+1;
    }


}