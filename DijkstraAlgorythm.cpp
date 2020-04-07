#include "DijkstraAlgorythm.hh"

//u1 Trzeba zaznaczyc ze ta kolejka priorytetowa zostalaa dostosowana do moich potrzeb

//u2 W moim przypadku w algorytmie jest jedno zbdne porownanie (switch) mozna byloby 2 algorytmy jeden dla
// matrixa drugi dla listy ale czas wychodzil ten sam, operacja porownanie nie zajmuje az tyle czasu

void PriorityQueue::push(int Node,int AddPriority){
    int son=n++,father;

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

int* DijkstraAlgorythm(int Node1,graph graphh){
    
    int Node=Node1-1;                          // wybrany wierzcholek (jako ze numeracja w tablicy od 0 a numeracja wierzcholkow od 1)                     
    PriorityQueue queue(graphh.NumberOfNodes); // tworzymy kolejke priorytetowa przechowujaca max elem =liczba wierzcholkow
    elem nearest;                              // zmienna pomocnicza dla 'wyjetego' z kolejki elementu               
    int *LengthTab= new int[graphh.NumberOfNodes];  // tablica przechowujaca odleglosci do pozostalych wierzcholkow

    for(int i=0;i<graphh.NumberOfNodes;i++){      // Przypisanie naszej flagi (brak polaczenia z wierzcholkiem)
        LengthTab[i]=maxweight+1;
    }
    LengthTab[Node]=0;                            // dla wybranego wierzcholka odleglosc do samego siebie to 0
    

    switch(graphh.choice){
        case adjacencylist:{
            AdjacencyList *tmp=new AdjacencyList; // tymczasowa lista zeby nie nadpisywac danych
            tmp=graphh.List.List[Node1];
            queue.push(Node1,0);
            
            while(tmp){
                queue.push(tmp->Vnode,tmp->weightTo);
                tmp=tmp->next;
            }


            while(!queue.IsEmpty()){
                queue.PrintQueue();
                nearest=queue.pop();      
                tmp=graphh.List.List[nearest.Node]; // listagraph musi dodawac 0 priority dla samego siebie wierzcholka
                // tu skonczylem prace i tu sa bledy mozna pomyslec o 0 
                while(tmp){   
                    cout <<  "tab " << LengthTab[tmp->Vnode] << endl;
                    if( (LengthTab[nearest.Node]+tmp->weightTo) < LengthTab[tmp->Vnode] ){           
                            LengthTab[tmp->Vnode]=LengthTab[nearest.Node]+tmp->weightTo;
                    }
                    tmp=tmp->next;
                }

            }

            break;
        }

        case adjacencymatrix: {
            for(int i=0;i<graphh.NumberOfNodes;i++){
                queue.push(i,graphh.MatGraph(Node,i)); // na kolejke dodaja sie tez wierzcholki ktore nie istnieja - bardzo niepotrzebne
            }

            while(!queue.IsEmpty()){
                nearest=queue.pop();
        
                for(int i=0;i<graphh.NumberOfNodes;i++){    
                    if( (LengthTab[nearest.Node]+graphh.MatGraph(nearest.Node,i)) < LengthTab[i] ){           
                        LengthTab[i]=LengthTab[nearest.Node]+graphh.MatGraph(nearest.Node,i);
                    }
                }

            }
            break;
        }

    }

    return LengthTab;
}