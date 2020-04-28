#include <iostream>
#include <fstream>
#include <cstdlib>
#include "AdjacencyMatGraph.hh"
#include <ctime>
#include <cmath>
using namespace std;

/**
 * @brief Konstruktor grafu reprezentowanego na macierzy sasiedztwa. Podczas konstrukcji obiektu
 *        alokujemy pamiec potrzebna na przechowanie dwuwymiarowej tablicy wskaznikow na krawedzie.
 * 
 * @param NumOfNodes - liczba wierzcholkow w grafie
 */
AdjacencyMatGraph::AdjacencyMatGraph(int NumOfNodes){
    NumberOfNodes=NumOfNodes;
    NumberOfEdges=0;
    StartingNode=1;
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

/**
 * @brief Destruktor grafu. Podczas usuwania obiektu pamietamy o zwolnieniu pamieci
 *        potrzebnej do przechowywania macierzy wskaznikow na krawedz
 */
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

/**
 * @brief Dodanie krawedzi do grafu.  
 * 
 * @param first - pierwszy wierzcholek krawedzi
 * @param second - drugi wierzcholek krawedzi
 * @param weight - waga krawedzi
 */
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

/**
 * @brief Wypisanie grafu reprezentowanego na macierzy sasiedztwa na standardowy
 *        strumien wyjsciowy
 * 
 */
void AdjacencyMatGraph::PrintGraph()const{
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
 * @brief Wypelnienie grafu losowymi krawedziami zgodnie z zadana gestoscia. Opis algorytmu podobnie jak dla grafu
 *        na liscie sasiedztwa
 * 
 * Na poczatku podjelem probe zaimplementowania algorytmu losowania ze zbioru, po to aby nie powtarzaly sie
 * wyniki losowania i aby uniknac tracenia czasu na losowanie. Moj algorytm nie zapewnial jednak calkowitej 
 * losowosci (wystepowalo duze prawdopodobienstwo wylosowania krawedzi pomiedzy poczatkowymi wierszami i kolumnami
 *  np krawedzi 1-2 1-4 1-5 2-3 w grafie z 10 wierzcholkami). Powrocilem wiec do algorytmu, ktory dluzej sie wykonuje,
 *  ale zapewnia wieksza losowosc i jest prostszy w zrozumieniu.
 * 
 * @param density 
 */
void AdjacencyMatGraph::FillGraph(double density){
    double nv=NumberOfNodes,ne=nv*(nv-1)*density/2; // ne - liczba krawedzi nv - liczba wierzcholkow
    srand( time( NULL ) );

    if(density==1){ // pelny graf
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
    while(loops){                           // podobnie jak w grafie reprezentowanym na liscie losujemy dopoki nie wylosujemy
                                            // wystarczajacej liczby krawedzi do zapewnienia odpowiedniej gestosci
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

/**
 * @brief Wczytanie grafu z pliku. 
 * 
 * @param name - nazwa w pliku w ktorym znajduje sie zapisany graf w okreslonym porzadku ( jak w zalozeniach projektu )
 * @return true - pomyslne wczytanie
 * @return false  - blad przy wczytywaniu
 */
bool AdjacencyMatGraph::ReadFromFile(const char* name){

    /* Algorytm prawie taki sam jak dla listy sasiedztwa */

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
    
    matrix=new Edge **[NumberOfNodes];       // alokacja miejsca na wczytany graf
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

/**
 * @brief Metoda zwracajaca krawedzie danego wierzcholka
 * 
 * @param Node - wierzcholek dla ktorego mamy zwrocic krawedzie
 * @return List - lista krawedzi danego wierzcholka
 */
List AdjacencyMatGraph::incidentEdges(int Node)const{
    List list;
   
    for(int i=0;i<NumberOfNodes;i++){
        if(matrix[Node][i]){          // gdy krawedz istnieje
            list.insertFront(*matrix[Node][i]);
        }
    }
    
    return list;
}

/**
 * @brief Zwraca wierzcholek przeciwny krawedzi do zadanego
 * 
 * @param Node - wierzcholek zadany
 * @param edge - krawedz
 * @return int - zwracamy wierzcholek przeciwny
 */
int AdjacencyMatGraph::opposite(int Node,Edge edge)const{
    if(Node==edge.V1){
        return edge.V2;
    }else{
        return edge.V1;
    }
}

/**
 * @brief Usuniecie krawedzi
 * 
 * @param V1 - pierwszy wierzcholek w krawedzi
 * @param V2 - drugi wierzcholek w krawedzi
 */
void AdjacencyMatGraph::RemoveEdge(int V1,int V2){
    if(matrix[V1][V2]){
        delete matrix[V1][V2];
        matrix[V1][V2]=NULL;
        delete matrix[V2][V1];
        matrix[V2][V1]=NULL;
    }
    NumberOfEdges--;
}