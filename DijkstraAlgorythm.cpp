#include "DijkstraAlgorythm.hh"
#include <fstream>

//u1 Trzeba zaznaczyc ze ta kolejka priorytetowa zostalaa dostosowana do moich potrzeb


void PriorityQueue::IncreaseSize(int n){
    elem *NewQueue=new elem[2*n];          // zwiekszamy pamiec aby nie przekroczyc gornego limitu ( od razu 2 krotnie aby nie tracic czasu na 
                                           // przepisywanie danych )
    for(int i=0;i<MaxSize;i++){
        NewQueue[i]=queue[i];        
    }
    delete[] queue;
    MaxSize=2*n;
    queue=NewQueue;  
}

void PriorityQueue::push(int Node,int AddPriority){
    int son=n++,father;

    if(n>=MaxSize){
        IncreaseSize(n);
    }

    father=(son-1)/2;
    while(son>0 && queue[father].priority>AddPriority){  // naprawa kopca - najmniejszy element na szczycie kopca
        queue[son]=queue[father]; // ojciec na pozycji syna
        son=father; 
        father=(son-1)/2;   // nowe miejsce ojca 
    }

    queue[son].Node=Node;
    queue[son].priority=AddPriority;
    
}

elem PriorityQueue::pop(){
    int i,j;
    elem ReturnElem,HelpElem;

    if(!n){
        elem exception;exception.Node=0; // gdy wyrzucamy exception kolejka jest pusta
        return exception;
    }
    ReturnElem=queue[0];
    n--;
    HelpElem=queue[n];
    i=0; // korzen
    j=1;  // lewy syn
    while(j<n){ // robimy tzw "downheap"

        if((j+1<n) && (queue[j+1].priority<queue[j].priority) ){  // szukamy synow o mniejszym priorytecie (odleglosci)
            j++;
        }
        if(HelpElem.priority<=queue[j].priority){  // sprawdzenie warunku kopca
            break;
        }

        queue[i]=queue[j]; // kopiujemy mniejszego syna do ojca
        i=j;               // pozycja mniejszego syna
        j=2*j+1;            // lewy syn 
    } 

    queue[i]=HelpElem;


    return ReturnElem;
}

void PriorityQueue::PrintQueue(){
    cout << endl <<  "Kolejka priorytetowa: " << endl;
    for(int i=0;i<n;i++){
        cout << "W: " << queue[i].Node << " waga: " << queue[i].priority <<  endl;
    }
}

void PrintPath(ostream& os,int source,int* ParentTab){

    if(ParentTab[source]==-1) return  ;

    PrintPath(os,ParentTab[source],ParentTab);    

    os << "-> " << source+1  ;
}

/**
 * @brief 
 * 
 * @param NodePlus1 
 * @param graph 
 * @param ParentTab - tablica z poprzednikami, dzieki niej mozliwe jest odtworzenie sciezki do wierzcholka koncowego
 * @return int* 
 */
int* DijkstraAlgorythm(int NodePlus1,ListGraph *graph,int *ParentTab){

    int Node=NodePlus1-1;                          // wybrany wierzcholek (jako ze numeracja w tablicy od 0 a numeracja wierzcholkow od 1)                     
    PriorityQueue queue(2*graph->GetNumberOfNodes()); // tworzymy kolejke priorytetowa przechowujaca max elem =liczba wierzcholkow
    elem nearest;                              // zmienna pomocnicza dla 'wyjetego' z kolejki elementu               
    int *LengthTab= new int[graph->GetNumberOfNodes()];  // tablica przechowujaca odleglosci do pozostalych wierzcholkow

    for(int i=0;i<graph->GetNumberOfNodes();i++){      // Przypisanie naszej flagi (brak polaczenia z wierzcholkiem)
        LengthTab[i]=100000;
    }
    LengthTab[Node]=0;                            // dla wybranego wierzcholka odleglosc do samego siebie to 0
    ParentTab[Node]=-1;

    adjacencyListElem *tmp=new adjacencyListElem; // tymczasowa lista zeby nie nadpisywac danych
    List list=graph->incidentEdges(NodePlus1);
    tmp=list.Head();


    queue.push(NodePlus1,0);               // na potrzeby algorytmu dodaje wierzcholek wybrany
          
    while(tmp){
        queue.push(tmp->edge.V2,tmp->edge.weight);
        tmp=tmp->next;
    }

    while(!queue.IsEmpty()){
        nearest=queue.pop(); 
        List list1=graph->incidentEdges(nearest.Node);
        tmp=list1.head;     

        while(tmp){                            // dla wszystkich sasiadow wyjetego z kolejki wierzcholka
            if( (LengthTab[nearest.Node-1]+tmp->edge.weight) < LengthTab[tmp->edge.V2-1] ){           
                LengthTab[tmp->edge.V2-1]=LengthTab[nearest.Node-1]+tmp->edge.weight;
                queue.push((tmp->edge.V2),LengthTab[tmp->edge.V2-1]);
                ParentTab[tmp->edge.V2-1]=nearest.Node-1;
            }
            tmp=tmp->next;                    // przesuwamy sie po sasiadach
        }

    }

    return LengthTab;

}

int* DijkstraAlgorythm(int NodePlus1,AdjacencyMatGraph *graph,int *ParentTab){
    int Node=NodePlus1-1;                          // wybrany wierzcholek (jako ze numeracja w tablicy od 0 a numeracja wierzcholkow od 1)                     
    PriorityQueue queue(2*graph->GetNumberOfNodes()); // tworzymy kolejke priorytetowa przechowujaca max elem =liczba wierzcholkow
    elem nearest;                              // zmienna pomocnicza dla 'wyjetego' z kolejki elementu               
    int *LengthTab= new int[graph->GetNumberOfNodes()];  // tablica przechowujaca odleglosci do pozostalych wierzcholkow
    
    for(int i=0;i<graph->GetNumberOfNodes();i++){      // Przypisanie naszej flagi (brak polaczenia z wierzcholkiem)
        LengthTab[i]=100000;
    }
    LengthTab[Node]=0;
    ParentTab[Node]=-1;    

    adjacencyListElem *tmp=new adjacencyListElem;
    List list=graph->incidentEdges(Node);
    tmp=list.Head();

    queue.push(NodePlus1,0);          // na potrzeby algorytmu (odleglosc do samego siebie)
 

    while(tmp){
        queue.push(tmp->edge.V2,tmp->edge.weight);
        tmp=tmp->next;
    }
    while(!queue.IsEmpty()){
        nearest=queue.pop();
        
        List list=graph->incidentEdges(nearest.Node-1);
        tmp=list.head;
        
        while(tmp){                            // dla wszystkich sasiadow wyjetego z kolejki wierzcholka
            if( (LengthTab[nearest.Node-1]+tmp->edge.weight) < LengthTab[tmp->edge.V2-1] ){           
                LengthTab[tmp->edge.V2-1]=LengthTab[nearest.Node-1]+tmp->edge.weight;
                queue.push((tmp->edge.V2),LengthTab[tmp->edge.V2-1]);
                ParentTab[tmp->edge.V2-1]=nearest.Node-1;
            }
            tmp=tmp->next;                    // przesuwamy sie po sasiadach
        }
        
    }

    return LengthTab;
}

bool WriteDijkstraOut(Graph* graph,const char* name){
    int *ParentTab=new int[graph->GetNumberOfNodes()];
    ofstream file(name);
    if(!file.good()) return false;

    int *DistanceTab=new int[graph->GetNumberOfNodes()];    

    if(ListGraph* graph1 = dynamic_cast<ListGraph*>(graph)){
        DistanceTab=DijkstraAlgorythm(graph1->GetStartingNode(),graph1,ParentTab);
    }

    if(AdjacencyMatGraph* graph2 = dynamic_cast<AdjacencyMatGraph*>(graph)){
        DistanceTab=DijkstraAlgorythm(graph2->GetStartingNode(),graph2,ParentTab);
    }


    file <<  "Odleglosci od wierzcholka startowego nr " << graph->GetStartingNode() << endl;
    file << "Format danych: [Wierzcholek Koncowy] : [koszt drogi] | [kolejne wierzcholki liczac od wierzcholka startowego]" << endl;
    for(int i=0;i<graph->GetNumberOfNodes();i++){
        if(DistanceTab[i]!=100000){
            file << setw(2) << i+1 <<": "<< setw(4) <<  DistanceTab[i] <<" | " << graph->GetStartingNode();
            PrintPath(file,i,ParentTab);
            file << endl;
        }else{
            file << setw(2) << i+1 <<": "<< setw(4) << "NULL - brak polaczenia"  << endl;
        }
    }

    file.close();
    return true;
}