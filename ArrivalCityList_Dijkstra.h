//********************************************************************
// Description: //This is the linked list for all arrival city
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#define DEBUG false

using namespace std;

//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
    string arrCityName;
    double distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
class ArrivalCityList
{
    private:
        struct ArrCity* head;

    public:
        ArrivalCityList();
        ~ArrivalCityList();
        ArrCity* getHead();
        ArrCity* findArrCity(string oneCity);
        bool addArrCity(string oneCity, double distance);
        void printArrCityList();
};

//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL
ArrivalCityList::ArrivalCityList()
{
    head = nullptr;
}

ArrivalCityList::~ArrivalCityList()
{
    ArrCity* free = head;

    while (free != nullptr)
    {
        ArrCity* temp = free;
        free = free->next;
        delete temp;
    }
}

ArrCity* ArrivalCityList::getHead()
{
    return head;
}

// Get Arrival city info and return
ArrCity* ArrivalCityList::findArrCity(string oneCity)
{
    ArrCity* finder = head;

    while(finder != nullptr)
    {
        if(finder->arrCityName.compare( oneCity)==0)
        {
            return finder;
        }
        finder = finder->next;
    }
    return nullptr;
}

// Add all input info into linked list
bool ArrivalCityList::addArrCity(string oneCity, double distance)
{
    ArrCity* current = head;
    ArrCity* previous = nullptr;
    ArrCity* insert = new ArrCity();
    insert->arrCityName = oneCity;
    insert->distance = distance;
    insert->next = nullptr;

    //If linked list is empty, insert directly to head
    if(current == nullptr)
    {
        head = insert;
        return true;
    }

    //If there is an exist node, do not insert
    if(current->arrCityName.compare(oneCity)==0)
    {
        delete insert;
        return false;
    }

    //Insert the node with alphabetical order
    while(current!=nullptr && current->arrCityName < oneCity)
    {
        previous = current;
        current = current->next;
    }
    // Insert at the beginning if previous is still nullptr
    if (previous == nullptr)
    {
        insert->next = head;
        head = insert;
    }
    else // Insert between previous and current
    {
        previous->next = insert;
        insert->next = current;
    }
    return true;
}

// Print out all Arrival city in the linked list
void ArrivalCityList::printArrCityList()
{
    if (!head)
    {
        cout << "Arrival city list is empty" << endl;
        return;
    }

    ArrCity* printTraversal = head;

    while (printTraversal != nullptr)
    {
        cout << left;
        cout << printTraversal->arrCityName
             << setprecision(2) <<"(" <<printTraversal->distance <<")"<< ",";
        printTraversal = printTraversal->next;
    }
    cout << endl;
}
//*******************************************************************
//bool addArrCity(string oneCity, double distance);
//Creates a new ArrCity object and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities
//Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.



//According to above class definition, define all functions accordingly
//----
//----
