#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include "AdjacencyListGraph.hh"


using namespace std;
ListGraph::ListGraph(){}

ListGraph::ListGraph(int number){
    NumberOfNodes=number;
    TabOfLists=new List[number+1];
    PossibleLoop=false;
    StartingNode=1;
}

ListGraph::~ListGraph()
{
    delete[] TabOfLists;
}


ListGraph::ListGraph(const ListGraph &graph){
    NumberOfNodes=graph.NumberOfNodes;
    NumberOfEdges=graph.NumberOfEdges;
    PossibleLoop=false;    
    TabOfLists=new List[NumberOfNodes+1];
    TabOfLists=graph.TabOfLists;
}


void ListGraph::AddEdge(int first,int second,int weight){

    if(first==second &&!PossibleLoop){
        cout << "Graf bez petli! Nie mozna dodac krawedzi";
        return;
    }

    Edge edge;
    edge.V1=first;
    edge.V2=second; // dodanie drugiego wierzcholka
    edge.weight=weight;
                                           // Dodanie w drugim wskaznika na pierwszy (sasiad pierwszego)    
                                            // dodajemy wierzcholki na poczatek listy 
    TabOfLists[first].insertFront(edge);

    /* To samo z drugim wierzcholkiem*/

    edge.V1=second;
    edge.V2=first;
    edge.weight=weight; 
    TabOfLists[second].insertFront(edge);     
                                      
    NumberOfEdges++;
}

void ListGraph::PrintGraph()const{

    cout << endl << "Graf reprezentowany na liscie sasiedztwa" << endl;
    cout << "[-> wierzcholek: wierzcholek sasiadujacy] [w:waga polaczenia], nastepny sasiad ...]" << endl;
    for(int i=1;i<NumberOfNodes+1;i++){
        TabOfLists[i].Print();
    }

}

bool ListGraph::DetectEdge(int V1,int V2){
    List tmp; // tymczasowa lista zeby nie nadpisywac danych  
    tmp=TabOfLists[V1];
    adjacencyListElem *tmp1=tmp.head;

       while(tmp1){
           if(tmp1->edge.V2==V2){
               return true;
           }
           tmp1=tmp1->next;
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
    
    TabOfLists=new List[NumberOfNodes+1];

    while(file.good()){
        file >> BuffNumb[0] >> BuffNumb[1] >> BuffNumb[2];
        AddEdge(BuffNumb[0]+1,BuffNumb[1]+1,BuffNumb[2]);    // +1 poniewaz w wymaganiach jest numeracja od 0 a moja implementacja
                                                        // zaklada numeracje od 1  
        getline(file,buffer);
    }

    file.close();
    return true;
}

List ListGraph::incidentEdges(int Node)const{
    List incidents;

    adjacencyListElem *tmp=TabOfLists[Node].head;
    while(tmp){
        incidents.insertFront(tmp->edge);
        tmp=tmp->next;
    }

    return incidents;
}