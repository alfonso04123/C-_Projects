//********************************************************************
// ASU CSE310 Assignment #7 Fall 2024
// Name of Author: Yanzhe Qu
// ASU ID: 1230914986
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
#include "MinPriorityQueue.h"



using namespace std;

class Graph
{
   private:
   int numOfNode;                 //number of vertices in the graph
   MinPriorityQueue* cityHeap;    //adjacency list of the graph, it is a min-heap
                                  //of departure city objects
   public:
   Graph(int numOfNode, MinPriorityQueue* cityHeap);
   ~Graph();
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(DepCity* u, DepCity v);
   int findOneCity(string aCityName);
   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);
   void printPath(string sourceCityName, DepCity* aCity);

   //add any auxiliary functions here in case you need them
   //----
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

//*******************************************************************
//Destructor
Graph::~Graph()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

//*******************************************************************
//void printGraph();
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.
void Graph::printGraph()
{
    if(numOfNode == 0)
    {
        cout << "\nThis is an empty graph" << endl;
    }else {
        for (int i = 0; i < numOfNode; i++) {
            cityHeap[i].printHeap();
        }
    }
}

// Every time we have a source city as departure city, we initialize the heap
void Graph::initialize_single_source(string sourceCityName)
{
    cityHeap->setSize(numOfNode);

    if (findOneCity(sourceCityName) == -1)
    {
        return;
    }

    DepCity temp=cityHeap->getDepCityArr()[findOneCity(sourceCityName)];
    temp.d=0;
    cityHeap->decreaseKey(findOneCity(sourceCityName),temp);

}

// To get the correct distance of each heap with departure city info with arrival city info
void Graph::relax(DepCity* u, DepCity v)
{
    if(v.d > u->d + u->arrCityList->findArrCity(v.depCityName)->distance)
    {
    if (DEBUG)   cout<<"relaxing"<<v.depCityName<<" to "<<u->depCityName<<endl;
        DepCity finderNew;
        finderNew.depCityName = v.depCityName;
        finderNew.d = u->d + u->arrCityList->findArrCity(v.depCityName)->distance;
        finderNew.pi = u;
        cityHeap->decreaseKey(findOneCity(v.depCityName),finderNew);
    }
}
int Graph::findOneCity(string aCityName)
{
    return cityHeap->isFound(aCityName);
}

// Apply dijkstra algorithm to calculate the correct edges
void Graph::dijkstra(string sourceCityName)
{
    initialize_single_source(sourceCityName);

    DepCity* exploredList = new DepCity[numOfNode];
    int exp_size = 0;

    while (cityHeap->getSize() != 0)
    {
        DepCity u = cityHeap->getHeapMin();
        cityHeap->extractHeapMin();
        exploredList[exp_size] = u;
        exp_size++;

        if (DEBUG) cout<<"the city "<<u.depCityName<<" is being extracted"<<endl;
        ArrCity* tempCurrent = u.arrCityList->getHead();

        while (tempCurrent != NULL && tempCurrent != nullptr)
        {
            DepCity v;
            bool vHasValue = false;
            string cityName = tempCurrent->arrCityName;
            for (int i = 0; i <cityHeap->getSize(); i++)
            {
                if (cityName.compare( cityHeap->getDepCityArr()[i].depCityName)==0)
                {
                    v = cityHeap->getDepCityArr()[i];
                    vHasValue = true;
                    break;
                }
            }

            if (vHasValue)//!isExplored && vHasValue)
            relax(&cityHeap->getDepCityArr()[cityHeap->getSize()], v);

            tempCurrent = tempCurrent->next;
        }
    }
    delete [] exploredList;
}

// Print out all edges calculate by dijkstra algorithm
void Graph::printDijkstraPath(string sourceCityName) {
    initialize_single_source(sourceCityName);
    if (findOneCity(sourceCityName) == -1)
    {
        if (cityHeap->getSize()==0)
        {
            cout << "\nThis is an empty graph" << endl;
        }

        cout << sourceCityName << " does NOT exist" << endl;
        return;
    }
    cout << "\n\nPrint the Dijkstra algorithm running result" << endl;
    cout << "\nSource City: " << sourceCityName << endl;
    cout << endl;

    if (cityHeap->isFound(sourceCityName) != -1)
    {
        dijkstra(sourceCityName);
        cout << left;
            cout << setw(14) << "Arrival City"
                 << setw(15) << "Shortest Dist."
                 << setw(15) << "Shortest Path" << endl;
            for(int i = numOfNode-1; i >-1; i--)
            {
                cout << setw(15) << cityHeap->getDepCityArr()[i].depCityName;

                if (cityHeap->getDepCityArr()[i].d >= 20000.0)
                {
                    cout << setw(15) << "None exist";
                }
                else
                {
                    cout << setw(15) << cityHeap->getDepCityArr()[i].d;
                }

                if (cityHeap->getDepCityArr()[i].d >= 20000.0)
                    { cout<< setw(15) <<"None exist";}
                else {
                    printPath(sourceCityName, &cityHeap->getDepCityArr()[i]);
                }
                cout << endl;
            }
        }
    }

void Graph::printPath(string sourceCityName, DepCity* aCity)
{
    if (aCity == nullptr) return;
    if (aCity->pi == nullptr)
    {
        cout << aCity->depCityName;
        return;
    }
    printPath(sourceCityName, aCity->pi);
    cout << "->" << aCity->depCityName;
}

//According to above class definition, define all functions accordingly
//----
//----
