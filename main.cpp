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
    int *ParentTab=new int[graph->GetNumberOfNodes()];
    high_resolution_clock::time_point t1 = high_resolution_clock::now();


    if(ListGraph* graph1 = dynamic_cast<ListGraph*>(graph)){
        DijkstraAlgorythm(rand()%graph->GetNumberOfNodes()+1,graph1,ParentTab);
    }

    if(AdjacencyMatGraph* graph2 = dynamic_cast<AdjacencyMatGraph*>(graph)){
        DijkstraAlgorythm(rand()%graph->GetNumberOfNodes()+1,graph2,ParentTab);
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    return time_span.count()*1000;
}


int main(){

    Graph *graph1=new ListGraph();
    if(!graph1->ReadFromFile("graf.txt"))    
    cerr << endl << "Operacja zakonczyla sie niepowodzeniem. Najprawdopodobniej zla nazwa pliku." << endl;
    
    graph1->PrintGraph();
    WriteDijkstraOut(graph1,"zapis.txt");

 /*
   Graph *graph1=new ListGraph(5);
 graph1->FillGraph(1);
 graph1->PrintGraph();
WriteDijkstraOut(graph1,"nowy.txt");
*/
/*
    double time[5][4][100];
    Stats stats[5][4];
    int size[5]={10,50,100,500,1000};
    double dens[4]={0.25,0.5,0.75,1};
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            for(int k=0;k<100;k++){    
                
                    Graph *graph1=new ListGraph(size[i]);
                    graph1->FillGraph(dens[j]);
                    time[i][j][k]=test(graph1) ;
                    delete graph1;
                
            }
        }
    }


    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            stats[i][j].max=time[i][j][0];
            stats[i][j].min=time[i][j][0];
            for(int k=0;k<100;k++){
                stats[i][j].average=stats[i][j].average+time[i][j][k];
                if(stats[i][j].min>time[i][j][k]){
                    stats[i][j].min=time[i][j][k];
                }
                if(stats[i][j].max<time[i][j][k]){
                    stats[i][j].max=time[i][j][k];
                }
            }
        }
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            stats[i][j].average=stats[i][j].average/100;
            cout << setw(3) << size[i] << setw(6) << dens[j] << "  :";
            cout << stats[i][j].min << " " << stats[i][j].average  << " " << stats[i][j].max << endl;
        }
    }

*/

    //if(!graph1->ReadFromFile("graf.txt"))    
    //cerr << endl << "Operacja zakonczyla sie niepowodzeniem. Najprawdopodobniej zla nazwa pliku." << endl;
    
    //graph1->PrintGraph();
    //WriteDijkstraOut(graph1,"zapis.txt");

}


// zamiast pushowania -> replaceKey, , ListGraph jest do przerobienia, 

