// Description: This is the Min Heap contain all Departure city info. Also including all arrival city
//              as linked list
//********************************************************************

//include necessary header file here
#include "ArrivalCityList.h"

using namespace std;

//Each node of the graph which is a departure City
struct DepCity
{
    string depCityName;
    double d;
    struct DepCity* pi;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains DepCity objects.
//The key of each DepCity is its d value.
class MinPriorityQueue
{
    private:
        struct DepCity* depCityArr;	        //a DepCity array
        int capacity, size;

	public:
        MinPriorityQueue(int capacity);
        ~MinPriorityQueue();

        DepCity* getDepCityArr();
        int getSize();
        void setSize(int size);
        int getCapacity();
        int isFound(string oneDepCityName);
        bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);
        bool insert(DepCity oneDepCity);
        void heapify(int index);
        DepCity getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();
        void swap(int i, int j);
};

// Constructor
MinPriorityQueue::MinPriorityQueue(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    depCityArr = new DepCity[capacity];
}

// Destructor
MinPriorityQueue::~MinPriorityQueue()
{
    delete[] depCityArr;
}
//*********************************************************
// Print all info in Min-Heap, including all departure city info and all its arrival city info
// in linked list
void MinPriorityQueue::printHeap()
{
    if(size == 0)
    {
        cout << "\nEmpty heap, no elements" << endl;
    }else
    {
        cout << "\nHeap size = " << getSize() << "\n" << endl;
    }

    cout << left;
    cout << setw(15) << "Dep. City "
         << setw(12) << "d Value"
         << setw(15) << "PI"
         << "Arrival City List" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << setw(15) << depCityArr[i].depCityName;
        cout << setw(12) <<fixed<<setprecision(2) <<depCityArr[i].d;
        if( depCityArr[i].pi == nullptr) {
            cout << setw(15)  << "No Parent";
        }else {
            cout << setw(15) <<  depCityArr[i].pi->depCityName;
        }
        depCityArr[i].arrCityList->printArrCityList();
    }
}

// Get Departure city info as a heap with linked list
DepCity* MinPriorityQueue::getDepCityArr()
{
    return depCityArr;
}

// Get size of each element of heap
int MinPriorityQueue::getSize()
{
    return size;
}

void MinPriorityQueue::setSize(int size) {
    this->size = size;
}

// Get capacity of each element of heap with linked list
int MinPriorityQueue::getCapacity()
{
    return capacity;
}

// Find the city name in depCityArr
int MinPriorityQueue::isFound(string oneDepCityName)
{
    for(int i = 0; i< size; i++)
    {
        if(depCityArr[i].depCityName==oneDepCityName)
        {
            return i;
        }
    }
    return -1;
}

// Organize heap with a decrease order to form a min-heap
bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue)
{
    if(index >= size){return false;}

    if(oneDepCityWithNewDValue.d > depCityArr[index].d)
    {
        cout << "\nDecrease distance error: new distance is bigger than the current distance" << endl;
        return false;
    }
    if (depCityArr[index].depCityName.compare(oneDepCityWithNewDValue.depCityName) != 0)
        throw runtime_error("Error in MinPriorityQueue::decreaseKey");

    depCityArr[index].d = oneDepCityWithNewDValue.d;
    depCityArr[index].pi = oneDepCityWithNewDValue.pi;

    while (index > 0 && (depCityArr[parent(index)].d > depCityArr[index].d))
    {
        swap(parent(index), index);
        index = parent(index);
    }
    return true;
}

// Insert departure city info as heap element with all arrival city info in linked list
bool MinPriorityQueue::insert(DepCity oneDepCity)
{
    if(isFound(oneDepCity.depCityName) != -1)
    {
        cout << "\nDuplicated. Do not insert" << endl;
        return false;
    }

    if(size == capacity)
    {
        int newCapacity = 2 * capacity;
        DepCity *doubleDepciy = new DepCity[newCapacity];

        for(int i = 0; i < size; i++)
        {
            doubleDepciy[i] = depCityArr[i];
        }

        delete[] depCityArr;
        depCityArr = doubleDepciy;
        capacity = newCapacity;
    }

    size++;
    depCityArr[size-1].d = 30000.0;

    DepCity insertNode = DepCity();
    insertNode = oneDepCity;

    depCityArr[size-1] = insertNode;

    decreaseKey(size-1, insertNode);

    return true;
}

//Use heapify to get the correct order
void MinPriorityQueue::heapify(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);
    int smallest = index;

    if(l < size && ((depCityArr[l].d < depCityArr[smallest].d) ||
        (depCityArr[l].d == depCityArr[smallest].d &&depCityArr[l].depCityName=="M")))
    {
        smallest = l;
    }
    if(r < size && depCityArr[r].d < depCityArr[smallest].d)
    {
        smallest = r;
    }
    if(smallest != index)
    {
        swap(index, smallest);
        heapify(smallest);
    }
}

DepCity  MinPriorityQueue::getHeapMin()
{
    return depCityArr[0];
}

// Extract the first element of min-heap
void MinPriorityQueue::extractHeapMin()
{
    if(size == 0)
    {
        cout << "\nHeap is empty, no element to extract." << endl;
        return;
    }

    swap(0, size-1);
    size--;
    heapify(0);
}

int MinPriorityQueue::leftChild(int parentIndex)
{
    return 2 * parentIndex+1;
}

int MinPriorityQueue::rightChild(int parentIndex)
{
    return 2 * parentIndex +2;
}

int MinPriorityQueue::parent(int childIndex)
{
    return (childIndex + 1) / 2-1;
}
void MinPriorityQueue::swap(int i, int j)
{
    DepCity temp = depCityArr[i];
    depCityArr[i] = depCityArr[j];
    depCityArr[j] = temp;
}

//
//************************************************************
//when you create the dummy node, initialize its d value to be
//30000.0 which represents infinite


//According to above class definition, define all other functions accordingly

