//********************************************************************
// Description: This is the header file that defines an undirected graph
//              with an array of sites and routes
//********************************************************************

//include necessary header file here
#include "Route.h"

using namespace std;

class Map
{
   private:
      int numOfSites, numOfRoutes;
      Site* setOfSites;   //an array of Site. Note: NOT allowed to change it to Site**
      Route* setOfRoutes; //an array of Route. Note: NOT allowed to change it to Route**

   public:
      Map(int numOfSites, int numOfRoutes, Site* siteArray, Route* routeArray);
      ~Map();
      void make_set(Site* oneSite);
      Site* find_set(Site* oneSite);
      void link(Site* aSite, Site* bSite);
      void Union(Site* aSite, Site* bSite);
      void sortRoutes();
      void MST_Kruskal();
      void heapify(Route* routeArray, int n, int index);
      void heapSort(Route* oneRoute);
      void swap(Route* routeArray,int i, int j);

};


//finish each function according to above definition
Map::Map(int numOfSites, int numOfRoutes, Site* siteArray, Route* routeArray)
{
    this->numOfSites = numOfSites;
    this->numOfRoutes = numOfRoutes;
    this->setOfSites = new Site[50];
    this->setOfRoutes = new Route[100];

    for(int i=0; i<numOfSites; i++)
    {
        this->setOfSites[i] = siteArray[i];
    }

    for(int j=0; j<numOfRoutes; j++)
    {
        this->setOfRoutes[j] = routeArray[j];
    }
}

Map::~Map()
{
    delete[] setOfSites;
    delete[] setOfRoutes;
}

void Map::make_set(Site* oneSite)
{
    //For each vertex, make them to a set.
    if (oneSite==nullptr)
    {
        return;
    }
    oneSite->parent = oneSite;
    oneSite->rank = 0;
}

Site *Map::find_set(Site* oneSite)
{
    //Find the representative
    if (oneSite->parent == nullptr)
    {
        oneSite->parent = oneSite;
    }

    if (oneSite != oneSite->parent)
    {
        oneSite->parent = find_set(oneSite->parent);
    }

    return oneSite->parent;
}

void Map::link(Site* aSite, Site* bSite)
{
    //Link 2 representative together
    if(aSite->rank > bSite->rank)
    {
        bSite->parent = aSite;
    }else if(aSite->rank < bSite->rank)
    {
        aSite->parent = bSite;
    }else
    {
        bSite->rank++;
        aSite->parent = bSite;
    }
}

void Map::Union(Site* aSite, Site* bSite)
{
    Site* rootA = find_set(aSite);
    Site* rootB = find_set(bSite);
    link(rootA, rootB);
}

void Map::sortRoutes()
{
    heapSort(setOfRoutes);
}

//*******************************************************************
//This function performs the Kruskal algorithm on the graph
void Map::MST_Kruskal()
{
   cout << "\nMST Kruskal Algorithm Result\n" << endl;
   double totalDistance = 0.0;
   int edgesUsed = 0;

   for (int i = 0; i < numOfSites; i++)
   {
       make_set(&setOfSites[i]);
   }

   sortRoutes();

   for (int i = 0; i < numOfRoutes && edgesUsed < numOfSites - 1; i++)
   {
       Site* u = setOfRoutes[i].getSite1();
       Site* v = setOfRoutes[i].getSite2();

       if (find_set(u) != find_set(v)) {
           Union(u, v);
           setOfRoutes[i].printRoute();
           totalDistance += setOfRoutes[i].getDistance();
           edgesUsed++;
       }
   }

   cout << "=====================================================================================" << endl;
   cout << "Total Distance: " << totalDistance << " meters" << endl;
}

void Map::heapify(Route* routeArray, int n, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int largest = index;

    if (left < n && routeArray[left].getDistance() > routeArray[largest].getDistance())
        largest = left;

    if (right < n && routeArray[right].getDistance() > routeArray[largest].getDistance())
        largest = right;

    if(largest != index)
    {
        swap(routeArray, index, largest);
        heapify(routeArray, n, largest);
    }
}

void Map::heapSort(Route* routeArray)
{
    int n = numOfRoutes;

    for(int i = n /2 -1; i >=0; i--)
    {
        heapify(routeArray, n, i);
    }

    for(int j = n - 1; j > 0; j--)
    {
        swap(routeArray, 0, j);
        heapify(routeArray, j, 0);
    }
}

void Map::swap(Route* routeArray, int i, int j)
{
    Route temp = routeArray[i];
    routeArray[i] = routeArray[j];
    routeArray[j] = temp;
}
