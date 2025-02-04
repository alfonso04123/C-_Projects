// Description: this is where you need to design your own hash functions,
// such as hashInsert, hashDelete, hashSearch and hashDisplay

#include "LinkedList.h"
#include <cmath>

using namespace std;

class Hash
{
    private:
		LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
		int m, numOfElements;      //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      int getNumOfElements();
      bool hashSearch(string hotelName, string arrivalDate, int confirmNum);
      bool hashInsert(string hotelName, string arrivalDate, int confirmNum);
      bool hashDelete(string hotelName, string arrivalDate, int confirmNum);
      double hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
 };

//constructor
Hash::Hash(int size)
{
    hashTable = new LinkedList[size];
    for(int i = 0; i<size; i++)
    {
        hashTable[i] = LinkedList();
    }
    m = size;
    numOfElements = 0;
}

//Destructor
Hash::~Hash()
{
    delete[] hashTable;
}

//Accessor for numOfElements
int Hash::getNumOfElements()
{
    return numOfElements;
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of hotelName, arrivalDate and confirmNum
bool Hash::hashSearch(string hotelName, string arrivalDate, int confirmNum)
{
    string info = hotelName + arrivalDate + to_string(confirmNum);

    if (hashTable[hashFunction(info)].searchBooking(hotelName, arrivalDate, confirmNum))
    {
        cout << "\n" << left
            << setw(18) << hotelName << "on "
            << setw(12) << arrivalDate << "with confirmation Num: "
            << setw(10) << confirmNum << "is found inside the hash table." << endl;
        return true;
    } else{
        cout << "\n" << left
            << setw(18) << hotelName << "on "
            << setw(12) << arrivalDate << "with confirmation Num: "
            << setw(10) << confirmNum << "is NOT found inside the hash table." << endl;
        return false;
    }
}

//hashInsert inserts a booking with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string hotelName, string arrivalDate, int confirmNum)
{
    string info = hotelName + arrivalDate + to_string(confirmNum);

    //if the linked list is empty
    if(hashTable[hashFunction(info)].getHead() == nullptr)
    {
        hashTable[hashFunction(info)].insertBooking(hotelName, arrivalDate, confirmNum);
        numOfElements++;
        return true;
    }else{
        if(hashTable[hashFunction(info)].searchBooking(hotelName, arrivalDate, confirmNum))
        {
            return false;
        }
        hashTable[hashFunction(info)].insertBooking(hotelName, arrivalDate, confirmNum);
        numOfElements++;
        return true;
    }
    return false;
}

//hashDelete deletes a booking with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of hotelName, arrivalDate and confirmNum
bool Hash::hashDelete(string hotelName, string arrivalDate, int confirmNum)
{
    string info = hotelName + arrivalDate + to_string(confirmNum);

    //if the linked list already empty
    if(hashTable[hashFunction(info)].getHead() == nullptr)
    {
        return false;
    }

    //if the booking is found
    if (hashTable[hashFunction(info)].searchBooking(hotelName, arrivalDate, confirmNum))
    {
        hashTable[hashFunction(info)].deleteBooking(hotelName, arrivalDate, confirmNum);
        numOfElements--;

        cout << "\n" << left
        << setw(18) << hotelName   << "on "
        << setw(12) << arrivalDate << "with confirmation Num: "
        << setw(10) << confirmNum  << "is deleted from hash table." << endl;
        return true;
   }else
    {
        cout << "\n"  << left
        << setw(18) << hotelName   << "on "
        << setw(12) << arrivalDate << "with confirmation Num: "
        << setw(10) << confirmNum  << "is NOT deleted from hash table." << endl;
  	}
    return false;
}

//This function computes your real load factor
//it is computed based on the longest linked list size
double Hash::hashLoadFactor()
{
    //if m is 0
    if(m == 0 || numOfElements == 0)
        return 0;

    double load = 0;
    for (int i = 0; i < m; i++) {
        if(hashTable[i].getSize() > load) {
            load = hashTable[i].getSize();
        }
    }
    return load;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
    //if there is no element in hash table
    if(m == 0 ) {
        cout << "There is no element to print" << endl;
        return;
    }

    for(int i = 0; i < m; i++)
    {
        cout << "HashTable[" << i <<"], size = " << hashTable[i].getSize() << endl;
        hashTable[i].displayList();
    }
}

//This is the hash function we used. Can try another hash functions as well
int Hash::hashFunction(string key)
{
    int hash = 0;
    int index;

    for(int i = 0; i<key.length(); i++)
    {
        hash = hash + (int) key[i];
    }
    index = hash % m;

    return index;
 }
