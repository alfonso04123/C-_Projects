
// Description: Build functions to search, add, display, cancel or modify reservation by date or name
//

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// HotelBooking represents a Hotel's booking information
struct HotelBooking
{
    string hotelName;
    string arrivalDate;
    int confirmNum; // booking confirmation No.
    struct HotelBooking *next;
};

// class LinkedList will contains a linked list of HotelBooking objects
class LinkedList
{
private:
    struct HotelBooking *head;

public:
    LinkedList();
    ~LinkedList();
    bool searchBooking(string hotelName, string arrivalDate, int confirmNum);
    bool addBooking(string hotelName, string arrivalDate, int confirmNum);
    bool addBookingHelper( HotelBooking* newBooking);
    void displayAllBookings();
    void displayBookingsByHotel(string hotelName);
    void displayBookingsByDate(string arrivalDate);
    int countAllBookings();
    int countBookingByHotel(string hotelName);
    int countBookingByDate(string arrivalDate);
    bool cancelOneBooking(string hotelName, string arrivalDate, int confirmNum);
    bool cancelAllBookingsByHotel(string hotelName);
    bool cancelAllBookingsByDate(string arrivalDate);
    bool delayABooking(string hotelName, string oldArrivalDate, int confirmNum, string newArrivalDate);
    bool changeAHotel(string oldHotelName, string arrivalDate, int confirmNum, string newHotelName);
};

// Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    // Add your own code
    //----
    head = nullptr;
}

// Destructor
// Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
// It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
// Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    // Add your own code
    //----
    HotelBooking *free = head;
    int count = 0;

    while (free != nullptr)
    {
        HotelBooking *temp = free;
        free = free->next;
        delete temp;
        count++;
    }
    cout << "\nThe number of deleted bookings is: " << count << "\n";
}

//**A function to find if the parameterized HotelBooking object is inside the LinkedList or not.
// Return true if it exists and false otherwise.
bool LinkedList::searchBooking(string hotelName, string arrivalDate, int confirmNum)
{
    // Add your own code
    //----
    HotelBooking *curr = head;

    while (curr != nullptr)
    {
        if ((curr->confirmNum == confirmNum) && (curr->hotelName == hotelName) && (curr->arrivalDate == arrivalDate))
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

//***This is the most important function you need to work on since it build the linked list****
// Creates a new node and inserts it into the list at the right place.
// It also maintains an alphabetical ordering of HotelBookings by hotelName, arrival date
// and confirmation number. i.e. first by hotelName, then by arrival date, last by confirmation
// number. i.e. if two HotelBookings have the same hotelName, then the new HotelBooking should be
// inserted in alphabetical order of their arrival dates. Also it is possible that two or more
// HotelBookings have same hotelName and arrival dates, but their confirmation number must be different
// and they should be inserted into the list by increasing order of the number.
// Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addBooking(string hotelName, string arrivalDate, int confirmNum)
{
    // Add your own code
    //----
    HotelBooking* newBooking = new HotelBooking;
    newBooking->hotelName = hotelName;
    newBooking->arrivalDate = arrivalDate;
    newBooking->confirmNum = confirmNum;
    newBooking->next = nullptr;

    // If the list is empty, add new booking as the first node
    if (!head) {
        head = newBooking;
        return true;
    }

    // Check if there exits duplicate node
    HotelBooking* current = head;
    HotelBooking* previous = nullptr;

    // Traverse the whole linkedlist
    while (current) {
        // Check if the node has already exists
        if (current->hotelName == hotelName &&
            current->arrivalDate == arrivalDate &&
            current->confirmNum == confirmNum) {
            delete newBooking; // delete the new node
            return false; // new booking has already exist
            }

        // Find the correct place
        if (current->hotelName > hotelName ||
            (current->hotelName == hotelName && current->arrivalDate > arrivalDate) ||
            (current->hotelName == hotelName && current->arrivalDate == arrivalDate && current->confirmNum > confirmNum)) {
            break;
            }

        // Search next node
        previous = current;
        current = current->next;
    }

    // Add new booking
    if (!previous) {
        // add at the head
        newBooking->next = head;
        head = newBooking;
    } else {
        // add new booking between head and tail
        previous->next = newBooking;
        newBooking->next = current;
    }

    return true;
}
bool LinkedList::addBookingHelper(HotelBooking* newBooking)
{
    // Add your own code
    //---

    // If the list is empty, add new booking as the first node
    if (!head) {
        head = newBooking;
        return true;
    }

    // Check if there exits duplicate node
    HotelBooking* current = head;
    HotelBooking* previous = nullptr;

    // Traverse the whole linkedlist
    while (current) {

        // Find the correct place
        if (current->hotelName > newBooking->hotelName ||
            (current->hotelName == newBooking->hotelName && current->arrivalDate > newBooking->arrivalDate) ||
            (current->hotelName == newBooking->hotelName && current->arrivalDate == newBooking->arrivalDate && current->confirmNum > newBooking->confirmNum)) {
            break;
            }

        // Search next node
        previous = current;
        current = current->next;
    }

    // Add new booking
    if (!previous) {
        // add at the head
        newBooking->next = head;
        head = newBooking;
    } else {
        // add new booking between head and tail
        previous->next = newBooking;
        newBooking->next = current;
    }

    return true;
}
// Display all HotelBookings in the linked list starting from the head.
void LinkedList::displayAllBookings()
{
    // Add your own code
    //----
    HotelBooking *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        cout << left << setw(18) << temp->hotelName
             << setw(12) << temp->arrivalDate
             << setw(8) << temp->confirmNum << "\n";

        temp = temp->next;
        counter++;
    }
    cout << "\nTotal # of bookings: " << counter << "\n";
}

// Display all bookings with the specified hotelName.
void LinkedList::displayBookingsByHotel(string hotelName)
{
    // Add your own code
    //----
    HotelBooking *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        if (temp->hotelName == hotelName){
            cout << left << setw(18) << temp->hotelName
             << setw(12) << temp->arrivalDate
             << setw(8) << temp->confirmNum << "\n";
            counter++;
        }
        temp = temp->next;
    }
    if (counter == 0)
        cout << "\nNo bookings with the specified hotelName found\n";
    else
        cout << "\nTotal: " << counter << " bookings found with " << hotelName << "\n";
}

// Display all bookings with the specified arrival date
void LinkedList::displayBookingsByDate(string arrivalDate)
{
    // Add your own code
    //----
    HotelBooking *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        if (temp->arrivalDate == arrivalDate){
            cout << left << setw(18) << temp->hotelName
             << setw(12) << temp->arrivalDate
             << setw(8) << temp->confirmNum << "\n";
            counter++;
        }
        temp = temp->next;
    }

    if (counter == 0)
        cout << "\nNo bookings with the specified date found\n";
    else
        cout << "\nTotal: " << counter << " bookings found on " << arrivalDate << "\n";
}

// Returns the total number of bookings in the list
int LinkedList::countAllBookings()
{
    // Add your own code
    //----
    HotelBooking *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        temp = temp->next;
        counter++;
    }
    return counter;
}

// Returns the total number of bookings by the specified hotel
int LinkedList::countBookingByHotel(string hotelName)
{
    // Add your own code
    //----
    HotelBooking *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        if (temp->hotelName == hotelName)
        {
            counter++;
        }
        temp = temp->next;
    }
    return counter;
}

// Returns the total number of bookings in the list by the specified arrival date
int LinkedList::countBookingByDate(string arrivalDate)
{
    // Add your own code
    //----
    HotelBooking *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        if (temp->arrivalDate == arrivalDate)
        {
            counter++;
        }
        temp = temp->next;
    }
    return counter;
}

// Cancel the specified HotelBooking from the list, releases the memory and updates pointers.
// Return true if it is successfully canceled, false otherwise.
bool LinkedList::cancelOneBooking(string hotelName, string arrivalDate, int confirmNum)
{
    // Add your own code
    //----
    HotelBooking *cur = head;
    HotelBooking *prev = nullptr;

    // If the list is empty, return false;
    if(cur == nullptr) {
        return false;
    }

    // First HotelBooking is the one to be canceled
    if ((cur->hotelName == hotelName) && (cur->arrivalDate == arrivalDate) && (cur->confirmNum == confirmNum))
    {
        head = head->next;
        delete cur;
        return true;
    }
    // HotelBooking to be cancled is inside the list
    while (cur != nullptr)
    {
        if ((cur->hotelName == hotelName) && (cur->arrivalDate == arrivalDate) && (cur->confirmNum == confirmNum))
        {
            prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

// Cancel all bookings from a specific hotel, releases the memory and updates pointers.
// Return true if it is successfully canceled, false otherwise. Note: multiple HotelBookings
// might be canceled
bool LinkedList::cancelAllBookingsByHotel(string hotelName)
{
    // Add your own code
    //----
    HotelBooking *cur = head;
    HotelBooking *prev = nullptr;
    bool isDeleted = false;

    while (cur != nullptr)
    {
        if (cur->hotelName == hotelName)
        {
            HotelBooking *tempMulti = cur;
            cur = cur->next;
            delete tempMulti; // Cancel reversation by name

            if (prev == nullptr) {
                head = cur; // If the reservation is the first node
            }else {
                prev->next = cur;
            }
            isDeleted = true;
        }else {
            prev = cur;
            cur = cur->next;
        }
    }
   return isDeleted;
}

// Removes all HotelBookings with the specified date, releases the memory and updates pointers.
// Return true if they are successfully removed, false otherwise. Note: all HotelBookings with
// the same arrival date should be removed from the list.
bool LinkedList::cancelAllBookingsByDate(string arrivalDate)
{
    // Add your own code
    //----
    HotelBooking *cur = head;
    HotelBooking *prev = nullptr;
    bool isDeleted = false;

    while (cur != nullptr)
    {
        if (cur->arrivalDate == arrivalDate)
        {
            HotelBooking *tempMulti = cur;
            cur = cur->next;
            delete tempMulti; // Cancel reservation

            if (prev == nullptr) {
                head = cur; // If the node is the first node
            }else {
                prev->next = cur;
            }
            isDeleted =  true;
        }else {
            prev = cur;
            cur = cur->next;
        }
    }
    return isDeleted;
}

// Modifies the arrival date of the given booking. Return true if it modifies successfully and
// false otherwise.
bool LinkedList::delayABooking(string hotelName, string oldArrivalDate, int confirmNum, string newArrivalDate)
{
    // Add your own code
    //----
    HotelBooking *temp = head;
    HotelBooking *prev= nullptr;

    while (temp != nullptr)
    {
        if ((temp->hotelName == hotelName) && (temp->arrivalDate == oldArrivalDate) && (temp->confirmNum == confirmNum))
        {
            temp->arrivalDate = newArrivalDate; // Change arrivalDate
            if(prev==nullptr) head= temp->next;
            else prev->next=temp->next;

            addBookingHelper(temp); // reorder the list alphabetically
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

// Change a specific booking info. If found it inside the list and change its hotelName successfully, return
// true; otherwise return false. Note: after successfully change its hotelName, the linked list must
// still be in alphabetical order
bool LinkedList::changeAHotel(string oldHotelName, string arrivalDate, int confirmNum, string newHotelName) {
    HotelBooking *temp = head;
    HotelBooking *prev= nullptr;

    while (temp != nullptr)
    {
        if ((temp->hotelName == oldHotelName) && (temp->arrivalDate == arrivalDate) && (temp->confirmNum == confirmNum))
        {
            temp->hotelName = newHotelName; //change hotelname
            if(prev==nullptr) head= temp->next;
            else prev->next=temp->next;

            addBookingHelper(temp); //reorder the list alphabetically

            return true;
        }
        prev = temp; // Keep searching rest node
        temp = temp->next;
    }
    return false;
}
