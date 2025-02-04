//************************************************************************

// Description: this is the main program that reads input from keyboard,
// it then uses disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
//**************************************************************************

//include necessary header file
#include "Map.h"

using namespace std;

void getArrSiteInfo(string oneArrSiteInfo, string& arrSiteName, double& distance);
int findSite(Site* travel, int numOfSites, string& siteName);

int main()
{
    //Maximum possible sites and route number
    const int MAX_SITE_NUM = 50, MAX_ROUTE_NUM = 100;
    int numOfSites = 0, numOfRoutes = 0;  //counter used to track actual number of sites and routes


   //create an array of Site which store all Sites (vertex of the graph)
   Site* travel = new Site[MAX_SITE_NUM];
   //create an array of Route which store all Routes (edges of the graph)
   Route* plan = new Route[MAX_ROUTE_NUM];

   //declare all necessary local variables here
   //

   string oneLine;

   getline(cin, oneLine);

   while(oneLine.compare("End") != 0)
   {
      //get one line from the input, extract the first token
      //create a Site object if it does not exist in site array,
      //insert it inside the site array. This will be first point of the 'aNewRoute'
      string delimiter = ",";
      int pos = oneLine.find(delimiter);
      string place = oneLine.substr(0,pos);

       //only add when there isnt one already
       if (findSite(travel, numOfSites, place) == -1)
       {
           travel[numOfSites].siteName = place;
           numOfSites++;
       }

       oneLine.erase(0, pos+delimiter.length());

       string arrival;
       double distance;

       while(oneLine.find(delimiter) != std::string::npos)
       {
           pos=oneLine.find(delimiter);
           arrival = oneLine.substr(0,pos);
           if (arrival.compare("") == 0)
           {
               break;
           }
           getArrSiteInfo(oneLine, arrival, distance);
           if (findSite(travel, numOfSites, arrival) == -1) {
               travel[numOfSites].siteName = arrival;
               numOfSites++;
           }
           plan[numOfRoutes] = Route(&travel[findSite(travel, numOfSites, place)], &travel[findSite(travel, numOfSites, arrival)], distance);
           numOfRoutes++;
           oneLine.erase(0, pos+delimiter.length());
           pos=oneLine.find(delimiter);
       }

      //extract the arrival site info. check whether it exists in
      //site array or not, if not, create a new Site object, add it inside.
      //This site will be the second point of the 'aNewRoute'


      //by using the two sites we got above, create a new route, add
      //it inside route array


      // Check if arrival site exists in travel array


      //get next line
      getline(cin, oneLine);

   } //repeat until the 'End'

   //Create a Map object by using site array and route array
   Map myMap(numOfSites, numOfRoutes, travel, plan);

   cout << "Total historical sites you will visit: " << numOfSites << endl;

   //Run Kruskal MST algorithm on above map
   myMap.MST_Kruskal();
}

//****************************************************************
//By giving a string, for example 'Pantheon(300.5)', this function
//extract the arrival site name 'Pantheon' and distance '300.5' meters
//Note: the delimiter is left and right parenthesis
//****************************************************************
void getArrSiteInfo(string oneArrSiteInfo, string& arrSiteName, double& distance)
{
    string delimiterLeft = "(";
    string delimiterRight = ")";
    int pos=oneArrSiteInfo.find(delimiterLeft);
    arrSiteName = oneArrSiteInfo.substr(0,pos);
    oneArrSiteInfo.erase(0, pos+delimiterLeft.length());

    pos=oneArrSiteInfo.find(delimiterRight);
    distance = stod(oneArrSiteInfo.substr(0,pos));
    oneArrSiteInfo.erase(0, pos+delimiterRight.length());
}

int findSite(Site* travel, int numOfSites, string& siteName) {
    for (int i = 0; i < numOfSites; i++) {
        //If find the vertex, return its index
        if (travel[i].siteName == siteName) {
            return i;
        }
    }
    //If not, return -1
    return -1;
}
