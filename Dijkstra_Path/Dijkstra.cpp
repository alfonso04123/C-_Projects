
//include necessary header file here
#include "Graph.h"

using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);     //**optional

int main()
{
   int count;       //number of nodes
   string oneLine, sourceCityName;
   string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times or not

   //cout << "Enter number of cities: ";
   cin >> count;
   cin.ignore(20, '\n');

   //For each line, we will create an ArrivalCityList(which is a linked list) for a specific departure city.
   //It represents all its reachable arrival cities with distance info.
   //Here we use an array of DepCity to store them
   DepCity* depCityArr = new DepCity[count];

   //Initialize depCityArr. Set each node's d value to be very large 20000.0
   //initialize each arrival city list
   for(int i = 0; i < count; i++)
   {
      //depCityArr[i].depCityName = oneLine;
      depCityArr[i].d = 20000.0 + i;      //**this is to make sure each node has different d value
      depCityArr[i].pi = nullptr;
      depCityArr[i].arrCityList = new ArrivalCityList();
      getline(cin, oneLine);
      getCityInfo(oneLine, depCityArr[i].depCityName, depCityArr[i].arrCityList);
   }

   //get input line by line and create the depCityArr
   ////create a Graph object
   /////----
   MinPriorityQueue* cityList = new MinPriorityQueue(count);
   for (int i = 0; i < count; i++)
   {
     cityList->getDepCityArr()[i]= depCityArr[i];
   }
   cityList->setSize(count);

   Graph *path = new Graph(count, cityList);

   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
   cityList->printHeap();

   // Get the source city name from the user and run the Dijkstra algorithm once before looping
   cout << endl;
   cout << "Enter source city name: ";
   cout << endl;
   cin >> sourceCityName;

   path->printDijkstraPath(sourceCityName);

   // Using a sentinel value controlled loop to repeat the process based on user input
   do {
      cout << "\nFind shortest path for another departure city(yes or no): " << endl;
      cout << endl;
      cin >> answer;
      if (answer == "yes") {
         cout << "Enter source city name: " << endl;
         cin >> sourceCityName;
         for (int i = 0; i < count; i++)
         {
            cityList->getDepCityArr()[i]= depCityArr[i];
         }
         path->printDijkstraPath(sourceCityName);
      }
   } while (answer == "yes");
   cout << "Program terminate" << endl;

   return 0;
}

//************************************************************************
//Given one line in input file, this function extract tokens and get departure city
//name and its arrival cities info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   depCityName = token;
   oneLine.erase(0, pos+delimiter.length());

   string oneArrCityInfo, arrCityName;
   double distance;

   while (oneLine.find(delimiter) != std::string::npos) {
      pos=oneLine.find(delimiter);
      oneArrCityInfo = oneLine.substr(0,pos);
      if (oneArrCityInfo.compare("") == 0)
      {
         break;
      }
      getArrCityInfo(oneArrCityInfo, arrCityName, distance);
      arrCityList->addArrCity(arrCityName,distance);
      oneLine.erase(0, pos+delimiter.length());
   }
}

//****************************************************************************
//Given one arrival city info. format of, such as Z(60.2), this function
//extract arrival city name 'Z' and distance 60.2 from it.
//this function is optional. Feel free to extract tokens using your own way
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance)
{
   string delimiterLeft = "(";
   string delimiterRight = ")";
   int pos=oneArrCityInfo.find(delimiterLeft);
   arrCityName = oneArrCityInfo.substr(0,pos);
   oneArrCityInfo.erase(0, pos+delimiterLeft.length());

   pos=oneArrCityInfo.find(delimiterRight);
   distance = stod(oneArrCityInfo.substr(0,pos));
   oneArrCityInfo.erase(0, pos+delimiterRight.length());
}
