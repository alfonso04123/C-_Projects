//********************************************************************
// Description: This file contain all setup for vertexes and edges
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Site represents one vertex of the map
struct Site
{
    string siteName;
    int rank;
    struct Site* parent;

   //C++ doesn't provide a default constructor, need it here.
   Site()
   {
       siteName = "";
       rank = 0;
       parent = nullptr;
   }

   //overloaded constructor
   Site(string name)
   {
      this->siteName = name;
      rank = 0;
      parent = nullptr;
   }
};

//Route represents one edge of the map which connects two historical sites of Rome
class Route
{
    private:
       struct Site* site1;
       struct Site* site2;
       double distance;

	public:
	   Route();
       Route(Site* site1, Site* site2, double distance);
       Site* getSite1();
       Site* getSite2();
       double getDistance();
       void printRoute();
};


Route::Route()
{
    site1 = nullptr;
    site2 = nullptr;
    distance = 0.0;
}

Route::Route(Site *site1, Site *site2, double distance)
{
    this->site1 = site1;
    this->site2 = site2;
    this->distance = distance;
}

Site *Route::getSite1()
{
    //Get first vertex
    return site1;
}

Site *Route::getSite2()
{
    //Get Another vertex
    return site2;
}

double Route::getDistance()
{
    return distance;
}

void Route::printRoute()
{
    cout << left;
    cout << setw(33) << site1->siteName
         << setw(8) << "<--->"
         << setw(33) << site2->siteName
         << setw(3) << " = "
         << setw(8) << right << fixed << setprecision(1) << getDistance()
         << endl;
}
