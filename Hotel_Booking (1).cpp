// Description: this is the main program that reads input from keyboard,
// it then executes various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the info. of a HotelBooking object
void getBookingInfo(string oneLine, string& hotelName, string& arrivalDate, int& confirmNum);

int main()
{
    string hotelName, arrivalDate ;
    int confirmNum;
    string command, oneLine;
    string delimiter = ",";

   int pos = 0;

   //Create a RedBlackTree object here, use it throughout the program
   RedBlackTree *hotelObject = new RedBlackTree();



   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      command = oneLine.substr(0, pos);
      oneLine.erase(0, pos + delimiter.length());

      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;
         //call the relevant function on the red black tree
         delete hotelObject;
         break;
      }
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;
         hotelObject->treePreorder();
      }
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;
         hotelObject->treeInorder();
      }
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;
         hotelObject->treePostorder();
      }
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;
         hotelObject->treeMinimum();
      }
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;
         hotelObject->treeMaximum();
      }
      else if(command.compare("tree_predecessor")==0)
      {
         //call the relevant function to get the HotelBooking info. first
         getBookingInfo(oneLine,hotelName, arrivalDate, confirmNum);
         cout << "\nCommand: tree_predecessor" << endl;
         //call the relevant function on the red black tree
         hotelObject->treePredecessor(hotelName, arrivalDate, confirmNum);
      }
      else if(command.compare("tree_successor")==0)
      {
         //call the relevant function to get the HotelBooking info. first
         getBookingInfo(oneLine,hotelName, arrivalDate, confirmNum);
         cout << "\nCommand: tree_successor" << endl;
         //call the relevant function on the red black tree
         hotelObject->treeSuccessor(hotelName, arrivalDate, confirmNum);
      }
      else if(command.compare("tree_search")==0)
      {
         //call the relevant function to get the HotelBooking info. first
         getBookingInfo(oneLine,hotelName, arrivalDate, confirmNum);
         cout << "\nCommand: tree_search" << endl;
         //call the relevant function on the red black tree
         hotelObject->treeSearch(hotelName, arrivalDate,confirmNum);
      }
      else if(command.compare("tree_insert")==0)
      {
         //call the relevant function to get the HotelBooking info. first
         getBookingInfo(oneLine,hotelName, arrivalDate, confirmNum);
         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(18)  << hotelName
              << setw(12) << arrivalDate
              << setw(8) << confirmNum   << endl;
        //call the relevant function on the red black tree
        hotelObject->treeInsert(hotelName, arrivalDate, confirmNum);
      }
   } while(true);  //continue until 'quit'
   return 0;
}

//************************************************************************************
//This function from one line, extracts the hotelName, arrivalDate and confirmNum of a HotelBooking
void getBookingInfo(string oneLine, string& hotelName, string& arrivalDate, int& confirmNum)
{
   //Design your own code here
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
