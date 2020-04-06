#include <iostream>
#include <cstdlib>
#include "AdjacencyMatGraph.hh"
#include <ctime>
#include <cmath>
using namespace std;
AdjacencyMatGraph::AdjacencyMatGraph(){}


AdjacencyMatGraph::AdjacencyMatGraph(const AdjacencyMatGraph &graph){    
    NumberOfNodes=graph.NumberOfNodes;
    matrix=new int *[NumberOfNodes];
    for(int i=0;i<NumberOfNodes;i++){
        matrix[i]=new int[NumberOfNodes];
        matrix[i]=graph.matrix[i];
    } 
    
}


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
            matrix[i][j]=maxweight+1; // maxweight+1 ustawione jako flaga swiadczace ze dane pole jest puste 
        }                           // zgodnie z konwencja ze gdy mozliwe sa petle w grafie waga polaczenia = 0
    }                               // a brak polaczenia to nieskonczonosc (w przypadku tej implementacji -> maxweight+1)

    for(int i=0;i<NumberOfNodes;i++){           // do samego siebie -> odgleglosc =0
        for(int j=0;j<NumberOfNodes;j++){
            if(i==j){matrix[i][i]=0;}
        }
    }
}

AdjacencyMatGraph::~AdjacencyMatGraph(){
    delete matrix;
}




void AdjacencyMatGraph::AddEdge(Edge edge){
    if(edge.first!=edge.second){
        matrix[edge.first-1][edge.second-1]=edge.weight;
        matrix[edge.second-1][edge.first-1]=edge.weight;
    }else{
        matrix[edge.first-1][edge.second-1]=0;
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

/**
 * @brief Przy wypelnianu grafu zastosowalem metode losowania ze zbioru, po to aby nie powtarzaly sie
 * wyniki losowania oraz aby uniknac petli w grafie 
 * 
 * @param density 
 */
void AdjacencyMatGraph::FillGraph(double density){
    double nv=NumberOfNodes,ne=nv*(nv-1)*density;
    NumberOfEdges=ne;
    srand( time( NULL ) );


    if(density==1){  // w przypadku pelnego grafu przyspieszamy wypelnianie grafu
        for(int i=0;i<NumberOfNodes;i++){  // tu jest niefajnie
            for(int j=0;j<NumberOfNodes;j++){
                if(i!=j){
                    matrix[i][j]=rand() %maxweight+1;
                    matrix[j][i]=matrix[i][j];
                }
            }
                
        }
        return ;
    }
    
    int RandNum=0,Edgenum=(NumberOfNodes*NumberOfNodes-NumberOfNodes),div=1; // edgenum wlasciwa max liczba kraawedzi po odjeciu bez loop
    int *RandTab=new int [Edgenum];

   
    for(int i=0;i<Edgenum;i++){
        ++RandNum;
        if(RandNum==div){
            RandNum++;
            div+=NumberOfNodes+1;
        }
        RandTab[i]=RandNum;
    }

    int Num=NumberOfEdges,row,col,p=0;
    double choice;
 
    while(Num){
        p++;
        RandNum=rand() %Num;
        choice=RandTab[RandNum];
        RandTab[RandNum]=RandTab[Edgenum-p];
        --Num;
        row=ceil(choice/NumberOfNodes)-1;
        col=choice-row*NumberOfNodes-1;
        matrix[row][col]=rand()%maxweight+1;
        matrix[col][row]=matrix[row][col];

    }



// Przeniesc to myslenie do listy tam tez powinno smigac
}