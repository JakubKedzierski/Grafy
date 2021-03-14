#include <iostream>
#include "AdjacencyList.hh"
using namespace std;

/**
 * @brief Kostruktor listy, ustawienie znacznika poczatkowego na NULL
 * 
 */
List::List(){
    head=NULL;
}

/**
 * @brief Destruktor listy, usuwamy po kolei kazdy element zawarty w liscie.
 *        W wyniku przeprowadzonych testow odkryto ze destruktor wykonywal sie w relatywnie dlugim
 *        czasie, co moglo spowolnic dzialanie algorytmu.
 * 
 */
List::~List(){ 
    adjacencyListElem *tmp;
        while(head){   // dopoki istnieja elementy w liscie
            tmp=head;
            head=head->next;  // przesuwamy sie po kolejnych elementach
            delete tmp;
        }
}

/**
 * @brief Funkcja wstawiajaca element na poczatek listy
 * 
 * @param edge - wstawiany element (krawedz)
 */
void List::insertFront(Edge edge){
    adjacencyListElem *Node=new adjacencyListElem; // stworzenie nowego elementu
    Node->edge=edge;
    Node->next=head;        // przypisanie poczatku listy jako element nastepujacy
    head = Node;            // zmiana wskaznika poczatkowego listy
}

/**
 * @brief Funkcja wypisujaca liste na standardowy strumien wyjsciowy
 * 
 */
void List::Print(){
    adjacencyListElem *tmp;
    tmp=head;
    if(!tmp){
        cout << "Brak listy incydencji" << endl;
        return; 
    }
    cout << "Lista incydencji V" << tmp->edge.V1 << ":" ;

    while(tmp){
        cout << "->" << tmp->edge.V2 << " w:" << tmp->edge.weight << ","; 
        tmp=tmp->next;
    }
    cout << endl;
}

/**
 * @brief Usuniecie wybranego elementu
 * 
 * @param V2 - wierzcholek przeciwny w krawedzi (elemecie) ktorego usuwamy
 */
void List::removeElem(int V2){

    adjacencyListElem *tmp,*tmp1;
    if(head->edge.V2==V2){
        tmp=head;
        head=head->next;
        delete tmp;
        tmp=NULL;
        return;
    }
       
    tmp=head;   
    while(tmp->next->edge.V2!=V2){
        tmp=tmp->next;
    }

    tmp1=tmp->next;
    tmp->next=tmp1->next;
    delete tmp1;
    tmp1=NULL;
}