#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include "AdjacencyListGraph.hh"
using namespace std;

/**
 * @brief Konstruktor grafu na liscie sasiedztwa
 *        Tworzymy tablice list sasiedztwa dla kazdego wierzcholka
 *        Numeracja list od 1.
 * 
 * @param number - liczba wierzcholkow w nowo powstalym grafie
 */
ListGraph::ListGraph(int number){
    NumberOfNodes=number;
    TabOfLists=new List[number+1];
    StartingNode=1;
}

/**
 * @brief Destruktor listy. Usuwamy tablice list, a tym samym
 *        wywolujemy destruktory poszczegolnych list
 * 
 */
ListGraph::~ListGraph()
{
    delete[] TabOfLists;
}

/**
 * @brief Dodanie nowej krawedzi dla grafu reprezentowanego na liscie sasiedztwa 
 * 
 * @param first - pierwszy wierzcholek w krawedzi
 * @param second - drugi wierzcholek w krawedzi
 * @param weight - waga nowo utworzonej krawedzi
 */
void ListGraph::AddEdge(int first,int second,int weight){

    if(first==second){
        cerr << "Graf bez petli! Nie mozna dodac krawedzi";
        return;
    }

    /* Tworzenie krawedzi*/
    Edge edge;
    edge.V1=first;
    edge.V2=second; 
    edge.weight=weight;

    /* Dodanie utworzonej krawedzi do listy sasiedztwa dla okreslonego 
                                    wierzcholka (miejsca w tablicy list)*/
    TabOfLists[first].insertFront(edge);


    /* To samo dla drugiego wierzcholka w krawedzi*/
    edge.V1=second;
    edge.V2=first;
    edge.weight=weight; 
    TabOfLists[second].insertFront(edge);     
                                      
    /* Zwiekszenie licznika liczby krawedzi w grafi*/                                  
    NumberOfEdges++;
}

/**
 * @brief Wypisanie grafu reprezentowanego na liscie sasiedztwa
 *        na standardowy strumien wyjsciowy
 * 
 */
void ListGraph::PrintGraph()const{

    cout << endl << "Graf reprezentowany na liscie sasiedztwa" << endl;
    cout << "[-> wierzcholek: wierzcholek sasiadujacy] [w:waga polaczenia], nastepny sasiad ...]" << endl;
    for(int i=1;i<NumberOfNodes+1;i++){
        TabOfLists[i].Print();                     // wywolujemy metode Print dla kazdej listy sasiedztwa
    }
}

/**
 * @brief Funkcja sprawdzajaca istnienie krawedzi. 
 * 
 * @param V1 - pierwszy wierzcholek w krawedzi
 * @param V2 - drugi wierzcholek w krawedzi
 * @return true  - krawedz istnieje w grafie
 * @return false  - krawedz nie istnieje w grafie
 */
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
 * @brief Metoda wypelniajaca graf losowymi krawedziami z losowymi wagami z zakrsu [1-1000]
 *        W przypadku wypelniania grafu na liscie zastosowano algorytm wzorcowany na macierzy 
 *        sasiedztwa. Na poczatku losujemy krawedzie myslac o nich jako elementach tablicy dwuwymiarowej
 *        (np tab[2][3]=flag -istnieje krawedz miedzy 2 i 3 wierzcholkiem). Algorytm nie jest doskonaly, ale wystarczajacy
 *        do potrzeb przeprowadzanych testow.
 *          
 * @param density - zadawana gestosc grafu - na jej podstawie wylicza sie liczbe krawedzi a pozniej losuje 
 *        krawedzie i dodaje do grafu
 */
void ListGraph::FillGraph(double density){
    int flag=10; // flaga ustawiana dla wylosowanych krawedzi do stworzenia

    /* Tworzymy macierz dwuwymiarowa*/
    int **matrix=new int*[NumberOfNodes];
    for(int i=0;i<NumberOfNodes;i++){
        matrix[i]=new int[NumberOfNodes];
    }
   
    for(int i=0;i<NumberOfNodes;i++){
        for(int j=0;j<NumberOfNodes;j++){
            matrix[i][j]=0;
        }
    }
    
   /* nv - liczba wierzcholkow, ne - liczba krawedzi*/
    double nv=NumberOfNodes,ne=nv*(nv-1)*density/2;  // nie liczymy krawedzi podwojnie 
                                                //tj krawedz miedzy wierzcholkami 2-1 i 1-2 to jedna krawedz
    
    srand( time( NULL ) );
    /* ztrzutowanie liczby krawedzi na liczbe calkowita, row-wiersz macierzy 
        col - kolumna macierzy (mozna myslec o wierszach i kolumnach jako wierzcholkach) */
    int loops=ne,row=0,col=0;

    int i=0,j=0; // na potrzeby iterowania i sprawdzania warunku
    
    if(density==1){   // dla pelnego grafu sytuacja jest prosta, tworzymy wszystkie krawedzi
        for(i=0;i<NumberOfNodes;i++){
            for(j=0;j<NumberOfNodes;j++){
                if(j!=i){
                    if(matrix[i][j]==0){
                        matrix[i][j]=flag;
                        matrix[j][i]=flag;
                    }
                }
            }
        }
    }else{ 
        /* W przypadku grafu niepelnego losujemy krawedzie do okreslonej liczby. W przypadku
            powtarzajacych sie krawedzi ponawiamy losowanie, nie zmniejszajac liczby krawedzi pozostalych do wylosowania*/
        while(loops){
            row=rand()%NumberOfNodes+1;
            col=rand()%NumberOfNodes+1;
            if(row!=col){
                if(matrix[row-1][col-1]==0){
                    matrix[row-1][col-1]=flag;
                    matrix[col-1][row-1]=flag;
                    loops--;
                }
            }
        } 
    }

    /* Zczytujemy ustawione flagi w macierzy i tworzymy krawedzie*/
    for(int i=0;i<NumberOfNodes;i++){
        for(int j=i+1;j<NumberOfNodes;j++){   // aby nie powtarzac dodawania krawedzi juz istniejacych iterator kolumn ustawiamy jako wiersz +1
            if(matrix[i][j]==flag){
                AddEdge(i+1,j+1,rand()%1000+1);
            }
        }

    }

    for(int i=0;i<NumberOfNodes;i++){
        delete[] matrix[i];
    }

    delete[] matrix;
}

/**
 * @brief Wczytanie grafu z pliku
 * 
 * @param name - nazwa w pliku w ktorym znajduje sie zapisany graf w okreslonym porzadku ( jak w zalozeniach projektu )
 * @return true - pomyslne wczytanie
 * @return false  - blad przy wczytywaniu
 */
bool ListGraph::ReadFromFile(const char* name){
    
    ifstream file;      
    file.open(name,ifstream::in);
    
    if(!file.good()) return false;

    int BuffNumb[3];    // bufer do wczytania pierwszej lini (czyli liczby krawedzi wierzcholkow oraz wierzcholka startowego)
    string buffer; // bufer na wczytywanie lini tekstu i przesuwanie wskaznika pliku
    file >> BuffNumb[0] >> BuffNumb[1] >> StartingNode;
    
    StartingNode++; //numeracja od 0 
    
    if(!file.good()) return false;  // zabezpieczenie
    
    NumberOfNodes=BuffNumb[1];
    getline(file,buffer);         // przesuniecie wskaznika pliku do nastepnej lini
    
    TabOfLists=new List[NumberOfNodes+1]; // zaalokowanie pamieci potrzebnej do przechowywania list sasiedztwa

    while(file.good()){
        file >> BuffNumb[0] >> BuffNumb[1] >> BuffNumb[2];
        AddEdge(BuffNumb[0]+1,BuffNumb[1]+1,BuffNumb[2]);    // dodawanie krawedzi
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
List ListGraph::incidentEdges(int Node)const{
    List incidents;

    adjacencyListElem *tmp=TabOfLists[Node+1].head;
    while(tmp){
        incidents.insertFront(tmp->edge);               
        tmp=tmp->next;
    }

    return incidents;
}

/**
 * @brief Zwraca wierzcholek przeciwny krawedzi do zadanego
 * 
 * @param Node - wierzcholek zadany
 * @param edge - krawedz
 * @return int - zwracamy wierzcholek przeciwny
 */
int ListGraph::opposite(int Node,Edge edge)const{
    if(Node==edge.V1){
        return edge.V2;
    }else{
        return edge.V1;
    }
}