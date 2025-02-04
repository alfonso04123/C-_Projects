// Description: A simple linked list that implements a list of HotelBooking objects. A user can
//              perform searching, insertion or deletion on the linked list.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct HotelBooking
{
    string hotelName;
    string arrivalDate;
    int confirmNum;
    struct HotelBooking* next;

    HotelBooking(const string &hotelName, const string &arrivalDate, int confirmNum, HotelBooking *next) : hotelName(
            hotelName), arrivalDate(arrivalDate), confirmNum(confirmNum), next(next) {}
    HotelBooking();

};

HotelBooking::HotelBooking() {}

class LinkedList
{
	private:
		struct HotelBooking* head;
		int size;   //number of bookings inside the linked list
    public:
       	LinkedList();
       	~LinkedList();
       	HotelBooking* getHead();
       	int getSize();
       	bool searchBooking(string hotelName, string arrivalDate, int confirmNum);
       	bool insertBooking(string hotelName, string arrivalDate, int confirmNum);
       	bool deleteBooking(string hotelName, string arrivalDate, int confirmNum);
       	void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    //----
    head = nullptr;
    size = 0;
}

//Destructor
LinkedList::~LinkedList()
{
    HotelBooking* free = head;

    while(free != nullptr)
    {
        HotelBooking* temp = free;
        free = free->next;
        delete temp;
    }
}

HotelBooking* LinkedList::getHead()
{
    return head;
}

//Return number of HotelBookings inside the Linked list
int LinkedList::getSize()
{
    return size;
}

//This function does a linear search on the linked list with the given info.
//it returns true if the corresponding HotelBooking is found, otherwise it returns false.
bool LinkedList::searchBooking(string hotelName, string arrivalDate, int confirmNum)
{
    HotelBooking* find = head;

    while(find != nullptr)
    {
        if((find->hotelName == hotelName) && (find->arrivalDate == arrivalDate) && (find->confirmNum ==confirmNum))
        {
            return true;
        }
        find = find->next;
    }
    return false;
}

//Insert the parameter HotelBooking at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertBooking(string hotelName, string arrivalDate, int confirmNum)
{
    HotelBooking* current = head;
    HotelBooking* insert = new HotelBooking(hotelName, arrivalDate, confirmNum, nullptr);

    //if the linked list is empty
    if(current == nullptr)
    {
        head = insert;
        size++;
        return true;
    }

    //if the HotelBooking already exist, return false
    if (searchBooking(hotelName, arrivalDate, confirmNum))
    {
        cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << " - Duplicated. NOT added" << endl;
        return false;
    }

    //if the list is not empty
    insert->next = head;
    head = insert;
    size++;
    return true;
 }

//Delete the HotelBooking with the given info. from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteBooking(string hotelName, string arrivalDate, int confirmNum)
{
    HotelBooking* search = head;
    HotelBooking* prev = nullptr;

    //if the list is empty
    if(search == nullptr)
    {
        return false;
    }

    //if booking not in the list
    if(!searchBooking(hotelName, arrivalDate, confirmNum))
    {
        return false;
    }

    //if booking is the first one
    if((search->hotelName == hotelName) && (search->arrivalDate == arrivalDate) && (search->confirmNum == confirmNum))
    {
        head = head->next;
        delete search;
        size--;
    }

    //if booking is inside the list
    while(search != nullptr)
    {
        if((search->hotelName == hotelName) && (search->arrivalDate == arrivalDate) && (search->confirmNum == confirmNum))
        {
            if(prev == nullptr){
                head = search->next;
            }else{
                prev->next = search->next;
            }
            delete search;
            size--;
            return true;
        }
        prev = search;
        search = search->next;
    }
    return false;
 }

//This function displays the content of the linked list.
void LinkedList::displayList()
{
    HotelBooking* temp = head;
    while(temp != nullptr)
    {
        cout << left << setw(18) << temp->hotelName
             << setw(12) << temp->arrivalDate
             << setw(8) << temp->confirmNum << "\n";
        temp = temp->next;
    }
}
