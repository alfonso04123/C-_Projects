// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.

#include <sstream>
#include "Hash.h"

using namespace std;

//This function used to get all info. of a HotelBooking object
void getBookingInfo(string oneLine, string& hotelName, string& arrivalDate, int& confirmNum);

int main()
{
    int size = 0;

    //a counter used to count # of valid HotelBooking entered
    //Note: duplicated bookings will NOT be counted inside
    int counter = 0 ;

	string hotelName, arrivalDate;
	int confirmNum;

    //declare any other necessary variables here
    //----

   // cout << "Enter the size of the hash table: ";     //used to test on local PC
	cin >> size;
    cin.ignore(20, '\n');

    //Instantiate the hash table with the relevant number of slots
    Hash reservation(size);
    string info = hotelName + arrivalDate + to_string(confirmNum);

    do {
         //use this do..while loop to repeatedly get one line booking info. and extract tokens
         //create one HotelBooking object and insert it inside the hashTable until 'InsertionEnd'
        // cout << "Enter the booking information you want to insert: " << endl;
         getline(cin, info);

         if(info != "InsertionEnd") {
             getBookingInfo(info, hotelName, arrivalDate, confirmNum);
             reservation.hashInsert(hotelName, arrivalDate, confirmNum);
             counter = reservation.getNumOfElements();
         }else{
             break;
         }
   } while(true);

	cout << "\nHash table size is: " << size;
	cout << "\nTotal HotelBooking objects entered is: " << counter <<endl;


    //This do..while loop used to get the commands until 'End'
    do {
        //get one line command
        getline(cin, info);

        if (info.find_first_of(',') == string::npos)
        {
            //check whether it is 'End', 'hashDisplay' or 'hashLoadFactor'
            //proceed accordingly
            if(info == "End")
            {
              break;
            }else if(info == "hashDisplay")
            {
                reservation.hashDisplay();
            }else if(info == "hashLoadFactor")
            {
                cout << "The ideal load factor is: "  << (double) (reservation.getNumOfElements()) / size << endl;
                cout << "My hash table real load factor is: "  << (double) (reservation.hashLoadFactor()) << endl;
                cout << "My hash table performance ratio is: " << (double) (reservation.hashLoadFactor())/ ((double) (reservation.getNumOfElements()) / size) <<endl;
            }
        }
        else
        {
            //extract the first token
            string delimiter = ",";
            int pos=info.find(delimiter);
            string token = info.substr(0,pos);
            string firstOne = token;
            info.erase(0, pos+delimiter.length());

            //check whether it is 'hashSearch' or 'hashDelete'
            //proceed accordingly
            if(firstOne == "hashSearch")
            {
                reservation.hashSearch(hotelName, arrivalDate, confirmNum);
            }else if(firstOne == "hashDelete")
            {
                reservation.hashDelete(hotelName, arrivalDate, confirmNum);
            }
        }
    } while(true);

	return 0;
}

//***************************************************************************
//From one line, this function extracts the tokens and get one HotelBooking info.
//This function is completed and given here as a study guide for extracting tokens
void getBookingInfo(string oneLine, string& hotelName, string& arrivalDate, int& confirmNum)
{
    string delimiter = ",";
	int pos=oneLine.find(delimiter);
	string token = oneLine.substr(0,pos);
	hotelName = token;
	oneLine.erase(0, pos+delimiter.length());

	pos=oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	arrivalDate = token;
	oneLine.erase(0, pos+delimiter.length());

	pos=oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	confirmNum = stoi(token);
	oneLine.erase(0, pos+delimiter.length());
}
