
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

//Add your own code
//----
#include "LinkedList.h"
using namespace std;

void printMenu();

int main()
 {
       // local variables, can be accessed anywhere from the main method
       char input1 = 'Z';
       string inputInfo;
       string hotelName, arrivalDate;
       int confirmNum;
       string line;
       bool success = false;

       //Add your own code
       //----
       string newArrivalDate, newHotelName;

       // instantiate a LinkedList object
       LinkedList* list1 = new LinkedList();

       printMenu();

       do
        {
           cout << "\nWhat action would you like to perform?\n";
           cin.get(input1);
           input1 = toupper(input1);    //change it to upper case
           cin.ignore(20, '\n');   //flush the buffer whenever you enter a char, integer, double
                                   //if you have multiple char, integer, double entered, only flush once

           // matches one of the case statement
           switch (input1)
           {
             case 'A':   //Add the hotel booking info.
               cout << "\nEnter the hotel booking information: ";
               cout << "\nEnter hotel name: ";
               //----
               getline(cin,hotelName);

               cout << "\nEnter arrival date: ";
               //----
               getline(cin,arrivalDate);

               cout << "\nEnter booking confirmation No.: ";
               //----
               cin >> confirmNum;
               cin.ignore(20, '\n'); //flush the buffer
               success = list1->addBooking(hotelName, arrivalDate, confirmNum);


               if (success == true)
                cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << " is added\n";
               else
                cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << " is NOT added\n";
               break;

            case 'C':  //Cancel one HotelBooking
                cout << "\nEnter the booking information which you want to cancel: ";
                cout << "\nEnter hotel name: ";
                //----
                getline(cin,hotelName);

                cout << "\nEnter arrival date: ";
                //----
                getline(cin,arrivalDate);

                cout << "\nEnter confirmation num: ";
                //----
                cin >> confirmNum;
                cin.ignore(20, '\n'); //flush the buffer.
                success = list1->cancelOneBooking(hotelName, arrivalDate, confirmNum);


                if (success == false)
                    cout << "\nNo booking found inside the list, cannot cancel it\n";
                else
                    cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << " is canceled\n";
                break;

             case 'D':   //Display all bookings
               //----
                   list1->displayAllBookings();
               break;

             case 'E':   //Display all bookings with a specific hotel
                cout << "\nWhich hotel you want to display the booking info: \n";
                //----
                //----
                getline(cin,hotelName);
                list1->displayBookingsByHotel(hotelName);
                break;

              case 'F':   //Display all bookings by arrival date
                cout << "\nWhich date you want to display the bookings: \n";
                //----
                //----
                getline(cin,arrivalDate);
                list1->displayBookingsByDate(arrivalDate);
                break;

              case 'G':   //Count total number of bookings
                //----
                //----
                cout << "\nTotal number of bookings is: " << list1->countAllBookings() << "\n";
                break;

              case 'H':   //Count number of bookings by hotel
                cout << "\nWhich hotel you want to count the bookings: \n";
                //----
                getline(cin,hotelName);
                //----
                cout << "\nTotal number of bookings for " << hotelName << " is: " << list1->countBookingByHotel(hotelName) << "\n";
                break;

             case 'I':   //Count number of bookings by date
                cout << "\nWhich date you want to count the bookings: \n";
                //----
                getline(cin,arrivalDate);
                //----
                cout << "\nTotal number of bookings on " << arrivalDate << " is: " << list1->countBookingByDate(arrivalDate) << "\n";
                break;

            case 'O':  //Cancel all bookings by a specific hotel
                cout << "\nWhich hotel you want to cancel all bookings: ";
                //----
                //----
                getline(cin,hotelName);
                success = list1->cancelAllBookingsByHotel(hotelName);

                if (success)
                    cout << "\nAll bookings with " << hotelName << " are canceled\n";
                else
                    cout << "\nBookings with " << hotelName << " does NOT exist. Cancel failed\n";
                break;

            case 'R':  //Cancel all bookings by a specific arrival date
                cout << "\nWhich date you want to cancel all bookings: ";
                //----
                //----
                getline(cin,arrivalDate);
                success = list1->cancelAllBookingsByDate(arrivalDate);

                if (success)
                    cout << "\nAll bookings on " << arrivalDate << " are canceled\n";
                else
                    cout << "\nBookings on " << arrivalDate << " does NOT exist, cancel failed\n";
                break;

            case 'S':  //search a specific booking
                cout << "\nSearch a hotel booking: ";
                cout << "\nEnter hotel name: ";
                //----
                //----
                getline(cin,hotelName);

                cout << "\nEnter arrival date: ";
                //----
                //----
                getline(cin,arrivalDate);

                cout << "\nEnter confirmation num: ";
                //----
                //----
                cin >> confirmNum;
                cin.ignore(20, '\n'); //flush the buffer
                success = list1->searchBooking(hotelName, arrivalDate, confirmNum);

                //----
                //----
                if (success == false)
                    cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << " is NOT found\n";
                else
                    cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << " is found\n";
                break;

            case 'U':  //Delay a booking, i.e. update a booking arrival date
                cout << "\nEnter the booking hotel name: ";
                //---
                getline(cin,hotelName);

                cout << "\nEnter the old arrival date: ";
                //----
                getline(cin,arrivalDate);

                cout << "\nEnter the confirmation num: ";
                //----
                cin >> confirmNum;

                cin.ignore(20, '\n'); //flush the buffer

                cout << "\nEnter the new arrival date: ";
                //----
                getline(cin,newArrivalDate);
                success = list1->delayABooking(hotelName, arrivalDate, confirmNum, newArrivalDate);

                //----
                //----

                if (success == true)
                     cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << ", its date is changed to " << newArrivalDate << "\n";
                else
                     cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with confirmation No.: " << confirmNum << ", its date is NOT changed" << "\n";
                break;

             case 'V':  //Change a hotel
                cout << "\nEnter the original hotel name: ";
                //----
                getline(cin,hotelName);

                cout << "\nEnter arrival date: ";
                //----
                getline(cin,arrivalDate);

                cout << "\nEnter confirmation num: ";
                //----
                cin >> confirmNum;
                cin.ignore(20, '\n'); //flush the buffer

                cout << "\nEnter the new hotel name: ";
                //----
                getline(cin,newHotelName);
                success = list1->changeAHotel(hotelName, arrivalDate, confirmNum, newHotelName);

                //----
                //----
                if (success == true)
                     cout << "\nOriginal booking with " << hotelName << " on " << arrivalDate << " with confirmation No.: " << confirmNum << " is changed to " << newHotelName << "\n";
                else
                     cout << "\nOriginal booking with " << hotelName << " on " << arrivalDate << " with confirmation No.: " << confirmNum << " is NOT changed" << "\n";
                break;

             case 'Q':   //Quit
                    delete list1;
                    break;

             case '?':   //Display Menu
                    printMenu();
                    break;

             default:
               cout << "\nUnknown action\n";
               break;
            }

        } while (input1 != 'Q');
      return 0;
   }

  /** The method displays the menu to a user**/
  void printMenu()
   {
     cout << "Choice\t\tAction\n";
     cout << "------\t\t------\n";
     cout << "A\t\tAdd a Booking\n";
     cout << "C\t\tCancel One Booking\n";
     cout << "D\t\tDisplay All Bookings\n";
     cout << "E\t\tDisplay Bookings by Hotel\n";
     cout << "F\t\tDisplay Bookings by Date\n";
     cout << "G\t\tTotal number of Bookings\n";
     cout << "H\t\tTotal number of Bookings by Hotel\n";
     cout << "I\t\tTotal number of Bookings by Date\n";
     cout << "O\t\tCancel Bookings by Hotel\n";
     cout << "R\t\tCancel Bookings by Date\n";
     cout << "S\t\tSearch one Booking\n";
     cout << "U\t\tDelay a Booking\n";
     cout << "V\t\tChange a Booking Hotel\n";
     cout << "Q\t\tQuit\n";
     cout << "?\t\tDisplay Help\n\n";
  }
