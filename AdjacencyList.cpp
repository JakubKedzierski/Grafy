#include <iostream>
#include "AdjacencyList.hh"
using namespace std;

List::List(){
    head=NULL;
}


List::~List(){ 
    adjacencyListElem *tmp;
        while(head){
            tmp=head;
            head=head->next;
            delete tmp;
            
        }

}

void List::insertFront(Edge edge){
    adjacencyListElem *Node=new adjacencyListElem;
    Node->edge=edge;
    Node->next=head;
    head = Node; 
}

void::List::Print(){
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