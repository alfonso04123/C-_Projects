// Description: Creates a Heap data structure that contains various HotelBooking objects
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>
#include <array>

using namespace std;

// Each HotelBooking has a unique confirmNum
struct HotelBooking
{
    string hotelName;
    string arrivalDate;
    int confirmNum;
};

// class MaxHeap represents a max heap that contains HotelBooking objects. The underline data structure
// is a one dimensional array of HotelBooking.
class MaxHeap
{
private:
    struct HotelBooking *bookingArr; // an array of HotelBookings
    int capacity, size;
    int leftSide(int i){ return 2 * i + 1;}
    int rightSide(int i){return 2 * i + 2;}

public:
    MaxHeap(int capacity);
    ~MaxHeap();

    HotelBooking *getHotelBookingArr();
    int getSize();
    int getCapacity();
    int isFound(int oneConfirmNum);
    bool heapIncrease(int index, HotelBooking oneNewBooking);
    bool heapInsert(string hotelName, string arrivalDate, int confirmNum);
    void heapify(int index);
    HotelBooking &getHeapMax();
    void extractHeapMax();
    int leftChild(int parentIndex);
    int rightChild(int parentIndex);
    int parent(int childIndex);
    void printHeap();
    void swap(int i, int j);
};

// Constructor to create a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    bookingArr = new HotelBooking[capacity];
}

// Destructor
// Before termination, the destructor is called to free the associated memory occupied by the heap.
// and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
    //----
    delete[] bookingArr;
    cout << "\nThe number of deleted bookings is: " << size << endl;
}

// Insert the relevant HotelBooking object inside the heap at the correct location
bool MaxHeap::heapInsert(string hotelName, string arrivalDate, int confirmNum)
{
    // if the booking already exist, return false
    if (isFound(confirmNum) != -1)
    {
        cout << "\nDuplicated booking. Not added" << endl;
        return false;
    }

    //----
    //----
    if (size == capacity)
    {
        int newCapacity = 2 * capacity;
        HotelBooking *expandBookingArr = new HotelBooking[newCapacity];

        for(int i = 0; i < size; i++){
            expandBookingArr[i] = bookingArr[i];
        }

        delete[] bookingArr;
        bookingArr = expandBookingArr;
        capacity = newCapacity;

        cout << "\nReach the capacity limit, double the capacity now." << endl;
        cout << "\nThe new capacity now is " << newCapacity << endl;
    }

    size++;
    bookingArr[size-1].confirmNum = -4000;

    HotelBooking addBooking = HotelBooking();
    addBooking.confirmNum = confirmNum;
    addBooking.arrivalDate = arrivalDate;
    addBooking.hotelName = hotelName;

    bookingArr[size -1].arrivalDate = arrivalDate;
    bookingArr[size -1].hotelName = hotelName;

    heapIncrease(size-1, addBooking);

    return true;
}

//Print all information
void MaxHeap::printHeap()
{
    //----
    //----
    if (size == 0)
    {
        cout << "\nEmpty heap, no elements" << endl;
    }
    else
    {
        cout << "\nHeap capacity = " << capacity << endl;
        cout << "\nHeap size = " << size << endl <<endl;
    }
    for(int i = 0; i < size; i++) {
        cout << left;
        cout << setw(18) << bookingArr[i].hotelName
             << setw(12) << bookingArr[i].arrivalDate
             << setw(8) << bookingArr[i].confirmNum << endl;
    }
}

// design all other functions according to the function definition and the resulting output testing cases
// getHotelBookingArr
HotelBooking *MaxHeap::getHotelBookingArr()
{
    return bookingArr;
}

// get Size
int MaxHeap::getSize()
{
    return size;
}

// get Capacity
int MaxHeap::getCapacity()
{
    return capacity;
}

// Find the confirmNum in bookingArr
int MaxHeap::isFound(int oneConfirmNum)
{
    for (int i = 0; i < size; i++)
    {
        if (bookingArr[i].confirmNum == oneConfirmNum)
        {
            return i;
        }
    }
    return -1;
}

//Update confirm number of bookingArr, then "float up"
bool MaxHeap::heapIncrease(int index, HotelBooking oneNewBooking)
{
    if(index >= size){return false;}

    if(oneNewBooking.confirmNum < bookingArr[index].confirmNum)
    {
        cout << "Increase confirmation number error: new confirmation number is smaller than the current number" << endl;
        return false;
    }

    bookingArr[index].confirmNum = oneNewBooking.confirmNum;

    while (index > 0 && bookingArr[parent(index)].confirmNum < bookingArr[index].confirmNum){
        swap(parent(index), index);
        index = parent(index);
    }

    return true;
}

//Use heapify to get the correct order
void MaxHeap::heapify(int index)
{
    int l = leftSide(index);
    int r = rightSide(index);
    int largest = index;
    if (l < size && bookingArr[l].confirmNum > bookingArr[index].confirmNum)
    {
        largest = l;
    }

    if (r < size && bookingArr[r].confirmNum > bookingArr[largest].confirmNum)
    {
        largest = r;
    }
    if (largest != index)
    {
        swap(index, largest);
        heapify(largest);
    }
}

//Get access of the root of the heap
HotelBooking& MaxHeap::getHeapMax()
{
    return bookingArr[0];
}

//Extracts the root of the heap
void MaxHeap::extractHeapMax()
{
    if (size == 0) {
        cout << "\nHeap is empty, no elements to extract." << endl;
        return;
    }

    bookingArr[0] = bookingArr[size - 1];
    size--;
    heapify(0);
}

//Get leftChild index
int MaxHeap::leftChild(int parentIndex)
{
    return 2 * parentIndex;
}

//Get rightChild index
int MaxHeap::rightChild(int parentIndex)
{
    return 2 * parentIndex + 1;
}

//Get parent index
int MaxHeap::parent(int childIndex)
{
    return (childIndex - 1) / 2;
}

//Swap function for heapify
void MaxHeap::swap(int i, int j)
{
    HotelBooking temp = bookingArr[i];
    bookingArr[i] = bookingArr[j];
    bookingArr[j] = temp;
}