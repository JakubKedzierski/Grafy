#include <iostream>
#include <chrono>
#include "AdjacencyListGraph.hh"
#include "AdjacencyMatGraph.hh"
#include "DijkstraAlgorythm.hh"

using namespace std;
using namespace std::chrono;

class Stats{
public:

    double average,min,max;
    Stats(){average=0;min=0;max=0;}

};

double test(Graph *graph){
    int *ParentTab=new int[graph->vertices()];
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    DijkstraAlgorythm(rand()%graph->vertices()+1,graph,ParentTab);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    return time_span.count()*1000;
}


int main(){

    Graph *graph1=new ListGraph();
    
    if(!graph1->ReadFromFile("graf.txt"))    
    cerr << endl << "Operacja zakonczyla sie niepowodzeniem. Najprawdopodobniej zla nazwa pliku." << endl;
    
    graph1->AddEdge(1,2,20);
    graph1->PrintGraph();
    WriteDijkstraOut(graph1,"zapis1.txt");
    
    delete graph1;
    graph1=NULL;
    graph1=new ListGraph(6);
    graph1->FillGraph(1);
    graph1->PrintGraph();    

    delete graph1;
    graph1=NULL;
    graph1=new AdjacencyMatGraph(10);
    graph1->FillGraph(0.5);
    graph1->PrintGraph();
    graph1->NewStartingNode(4);
    WriteDijkstraOut(graph1,"zapis.txt");

    delete graph1;
    graph1=NULL;
    graph1=new ListGraph(1000);
    graph1->FillGraph(1);
    cout << "Czas dzialania algorytmu [ms] " << test(graph1) << endl;

}


// zamiast pushowania -> replaceKey, , ListGraph jest do przerobienia, 

