#include "DijkstraAlgorythm.hh"
#include <fstream>

/**
 * @file W tym pliku znajduja sie rozwiniecia metod kolejki priorytetowej,
 *        algorytm Dijkstry oraz funkcja zapisujaca algorytm do pliku.
 */



/**
 * @brief Zwiekszenie rozmiaru kolejki w przypadku przekroczenia gornej granicy pojemnosci kolejki.
 *        W programie (przy algorytmie) metoda nie stosowana. (Potrzebna byla podczas debuggowania)
 * 
 */
void PriorityQueue::IncreaseSize(){
    Edge *NewQueue=new Edge[2*n];          // zwiekszamy pamiec aby nie przekroczyc gornego limitu ( od razu 2-krotnie aby nie tracic czasu na 
                                          // przepisywanie danych )
    for(int i=0;i<MaxSize;i++){
        NewQueue[i]=queue[i];        
    }
    delete[] queue;
    MaxSize=2*n;
    queue=NewQueue;  
}

/**
 * @brief Dodawanie elementu do kolejki priorytetowej. Element o najmniejszym kluczu (najmniejsza waga krawedzi zawsze ma miejsce korzenia)
 * 
 * @param edge - element (krawedz)
 */
void PriorityQueue::push(Edge edge){
    int son=n++; /* syn zajmuje ostatnia mozliwa pozycje w kolejce (na kopcu) */
    int father=(son-1)/2; // miejsce ojca (poziom wyzej od syna)

    if(n>=MaxSize){
        IncreaseSize();
    }

    while(son>0 && queue[father].weight>edge.weight){   // naprawa kopca - najmniejszy element na szczycie kopca
        queue[son]=queue[father];                        // ojciec na pozycji syna
        son=father; 
        father=(son-1)/2;                                // nowe miejsce ojca 
    }

    queue[son]=edge;
    
}

/**
 * @brief Usuwanie elementu z kolejki. Usuwany element ma najmniejszy klucz sposrod wszystkich
 *        elementow w kolejce. Po usunieciu dokonujemy naprawy kopca.
 * 
 * @return Edge - zwracana krawedz
 */
Edge PriorityQueue::pop(){
    int i,j; // zmienne do iterowania - ojciec i syn
    Edge ReturnElem,tmp;

    if(!n){
        Edge exception;exception.weight=0; // gdy wyrzucamy exception kolejka jest pusta
        cerr << "Kolejka jest juz pusta !" << endl;
        return exception;
    }

    ReturnElem=queue[0]; // zwracamy korzen
    n--;                 // zmniejszenie liczby elementow kolejki
    tmp=queue[n];
    i=0; // korzen
    j=1;  // lewy syn
    while(j<n){ // robimy tzw "downheap"

        if((j+1<n) && (queue[j+1].weight<queue[j].weight) ){  // szukamy synow o mniejszym priorytecie (odleglosci)
            j++;
        }
        if(tmp.weight<=queue[j].weight){  // sprawdzenie warunku kopca
            break;
        }

        queue[i]=queue[j]; // kopiujemy mniejszego syna do ojca
        i=j;               // pozycja mniejszego syna
        j=2*j+1;            // lewy syn 
    } 

    queue[i]=tmp;


    return ReturnElem;
}

/**
 * @brief Zamiana klucza wskazanego przez uzytkownika elementu
 * 
 * @param Node - wierzcholek (drugi w krawedzi) dla ktorego mamy dokonac zmiany klucza
 * @param weight - waga krawedzi
 */
void PriorityQueue::replaceKey(int Node,int weight){   

     int k=0;      // zmienna do przechowania miejsca znalezionego elementu
     for(int i=0;i<n;i++){
         if(queue[i].V2==Node){
            queue[i].weight=weight;             
            k=i; 
            break;
         }
     }
     int father=(k-1)/2; // miejsce ojca
     while(k>0&&queue[father].weight>queue[k].weight){  // przywrocenie wlasnosci kopca
         swap(queue[k],queue[father]);
         k=father;
         father=(k-1)/2;
     }

}

/**
 * @brief Drukowanie kolejnych elementow kolejki
 * 
 */
void PriorityQueue::PrintQueue(){
    cout << endl <<  "Kolejka priorytetowa: " << endl;
    for(int i=0;i<n;i++){
        cout << "W: " << queue[i].V2 << " waga: " << queue[i].weight <<  endl;
    }
}

/**
 * @brief Funkcja drukujaca na okreslony strumien dlugosc drogi do poszczegolnych
 * wierzcholow grafu
 * 
 * @param os - strumien wyjsciowy
 * @param source - wierzcholek poprzedzajacy
 * @param ParentTab - tablica wierzcholkow poprzedzajacych
 */
void PrintPath(ostream& os,int source,int* ParentTab){

    if(ParentTab[source]==-1) return  ; // dotarcie do wierzcholka poczatkowego

    PrintPath(os,ParentTab[source],ParentTab);    

    os << "-> " << source+1  ;
}

/**
 * @brief Algorytm Dijkstry - znalezienie najkrotszej sciezki w grafie od zadanego wierzcholka do wszystkich
 *        pozostalych
 * 
 * @param NodePlus1 - zadany wierzcholek dla ktorego szukamy najkrotszych sciezek
 * @param graph - graf do szukania sciezek, reprezentacja grafu jest dowolna
 * @param ParentTab - tablica do przechowania "rodzicow" (poprzednikow w sciezce)
 * @return int* - zwracana tablica najkrotszych sciezek do kazdego wierzcholka
 */
int* DijkstraAlgorythm(int NodePlus1,Graph *graph,int *ParentTab){

    int Node=NodePlus1-1;                          // wybrany wierzcholek (jako ze numeracja w tablicy od 0 a numeracja wierzcholkow od 1)                     
    PriorityQueue queue(graph->vertices());     // tworzymy kolejke priorytetowa przechowujaca max elem =liczba wierzcholkow
    Edge tmpEdge;                              // zmienna pomocnicza dla 'wyjetego' z kolejki elementu               
    int *LengthTab= new int[graph->vertices()];  // tablica przechowujaca odleglosci do  wierzcholkow
    
    Edge e0;e0.V1=NodePlus1;                   // zainicjalizowanie krawedzi przechowywanych przez kolejke 
                                            //(wierzcholek V1 bedzie taki sam i jest to wierzcholek zadany)

    for(int i=0;i<graph->vertices();i++){     
    
        /* Wypelnienie tablicy odleglosci */   
        if(i!=Node){
            LengthTab[i]=100000;
        }else{
            LengthTab[i]=0;   
        }

        /* ... oraz umieszczenie na kolejce priorytetowej */    
        e0.V2=i+1;e0.weight=LengthTab[i];
        queue.push(e0);
    }

    ParentTab[Node]=-1; // przypisanie flagi w tablicy "rodzicow" na miejscu wierzcholka poczatkowego
    adjacencyListElem *listIterator; // tymczasowa element do przechowywania glowy listy krawedzi i iterowania sie po kolejnych krawedziach
    int opp; // znacznik na wierzcholek przeciwny

    while(!queue.IsEmpty()){ 
        tmpEdge=queue.pop(); // usuwamy najmniejszy element

        List list1=graph->incidentEdges(tmpEdge.V2-1);  // pobieramy krawedzie danego wierzcholka
        listIterator=list1.head;     

        while(listIterator){                            // dla wszystkich sasiadow wyjetego z kolejki wierzcholka
            opp=graph->opposite(listIterator->edge.V1,listIterator->edge)-1;
            
            if( (LengthTab[tmpEdge.V2-1]+listIterator->edge.weight) < LengthTab[opp] ){           
                LengthTab[opp]=LengthTab[tmpEdge.V2-1]+listIterator->edge.weight;          // relaksacja krawedzi
                queue.replaceKey(opp+1,LengthTab[opp]);   // zmiana odleglosci do konkretnego wierzcholka w kolejce
                ParentTab[opp]=tmpEdge.V2-1; // zapisanie wierzcholka do tablicy rodzicow (na potrzeby odtworzenia sciezki)
            }

            listIterator=listIterator->next;                    // przesuwamy sie po sasiadach
        }
    
    }

    return LengthTab;
}

/**
 * @brief Zapis wyniku dzialania algorytmu do pliku
 * 
 * @param graph - graf na ktorym bedziemy stosowac algorytm
 * @param name - nazwa pliku do zapisu
 * @return true - zapis z powodzeniem
 * @return false - nieudany zapis
 */
bool WriteDijkstraOut(Graph* graph,const char* name){
    int *ParentTab=new int[graph->vertices()]; // tablica "rodzicow" w sciezce
    ofstream file(name);
    if(!file.good()) return false;

    int *DistanceTab=new int[graph->vertices()];    // tablica odleglosci

    DistanceTab=DijkstraAlgorythm(graph->GetStartingNode(),graph,ParentTab);

    file <<  "Odleglosci od wierzcholka startowego nr " << graph->GetStartingNode() << endl;
    file << "Format danych: [Wierzcholek Koncowy] : [koszt drogi] | [kolejne wierzcholki liczac od wierzcholka startowego]" << endl;
    for(int i=0;i<graph->vertices();i++){
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