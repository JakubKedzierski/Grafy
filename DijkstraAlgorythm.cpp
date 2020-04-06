#include "DijkstraAlgorythm.hh"

// Trzeba zaznaczyc ze ta kolejka priorytetowa zostalaa dostosowana do moich potrzeb


void PriorityQueue::push(int Node,int AddPriority){
    int son=n++,father;

    father=(son-1)/2;
    while(son>0 && queue[father].priority>AddPriority){  // naprawa kopca - najmniejszy element na szycie kopca
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
// tu zakonczylem prace

    return ReturnElem;
}

int* DijkstraAlgorythm(int Node1,AdjacencyMatGraph graph1){
    int Node=Node1-1;
    PriorityQueue queue(graph1.GetNumberOfNodes());
    elem nearest;
    int *LengthTab= new int[graph1.GetNumberOfNodes()];
    
    for(int i=0;i<graph1.GetNumberOfNodes();i++){
        LengthTab[i]=maxweight+1;
    }
    LengthTab[Node]=0;

    for(int i=0;i<graph1.GetNumberOfNodes();i++){
            queue.push(i,graph1(Node,i));
    }
    

    while(!queue.IsEmpty()){
        nearest=queue.pop();
        
        for(int i=0;i<graph1.GetNumberOfNodes();i++){    
            if( (LengthTab[nearest.Node]+graph1(nearest.Node,i)) < LengthTab[i] ){           
                 LengthTab[i]=LengthTab[nearest.Node]+graph1(nearest.Node,i);
            }
        }

    }   

    return LengthTab;
}