#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include "linkedlist_Qu.hpp"
#include "zombie_Qu.h"
#include <cassert>
#include <limits>

using namespace std;

int string_to_int(const std::string &str) {
    std::istringstream iss(str);
    int num;
    iss >> num;
    if (iss.fail()) {
        throw std::invalid_argument("Invalid number: " + str);
    }
    return num;
}

// Unit test functions
void testAddToFront() {
    LinkedList<Zombie> list;
    list.AddToFront(Zombie('R'));
    assert(list.RetrieveFront().getType() == 'R');
    list.AddToFront(Zombie('Y'));
    assert(list.RetrieveFront().getType() == 'Y');
}

void testAddToEnd() {
    LinkedList<Zombie> list;
    list.AddToEnd(Zombie('G'));
    assert(list.RetrieveEnd().getType() == 'G');
    list.AddToEnd(Zombie('B'));
    assert(list.RetrieveEnd().getType() == 'B');
}

void testAddAtIndex() {
    LinkedList<Zombie> list;
    list.AddToEnd(Zombie('C'));
    list.AddToEnd(Zombie('M'));
    list.AddAtIndex(Zombie('Y'), 1);
    assert(list.Retrieve(1).getType() == 'Y');
    try {
        list.AddAtIndex(Zombie('R'), 5); // Should throw exception
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    try {
        list.Retrieve(5); 
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    list.AddAtIndex(Zombie('B'), 0); 
    assert(list.Retrieve(0).getType() == 'B');
    
    list.AddAtIndex(Zombie('G'), list.Length()); 
    assert(list.Retrieve(list.Length() - 1).getType() == 'G');
}

void testRemoveFromFront() {
    LinkedList<Zombie> list;
    list.AddToEnd(Zombie('C'));
    list.AddToEnd(Zombie('M'));
    assert(list.RemoveFromFront().getType() == 'C');
    assert(list.RemoveFromFront().getType() == 'M');
}

void testRemoveFromEnd() {
    LinkedList<Zombie> list;
    list.AddToEnd(Zombie('C'));
    list.AddToEnd(Zombie('M'));
    assert(list.RemoveFromEnd().getType() == 'M');
    assert(list.RemoveFromEnd().getType() == 'C');
}

// Actions
void engine_action(LinkedList<Zombie>* list, Zombie randomZomb) {
    if (!list) {
        std::cerr << "Error: List is null!" << std::endl;
        return;
    }
    list->AddToFront(randomZomb);
}

void caboose_action(LinkedList<Zombie>* list, Zombie randomZomb) {
    if (!list) {
        std::cerr << "Error: List is null!" << std::endl;
        return;
    }
    list->AddToEnd(randomZomb);
}

void jump_in_action(LinkedList<Zombie>* list, Zombie randomZomb, int position) {
    if (!list) {
        std::cerr << "Error: List is null!" << std::endl;
        return;
    }
    try {
        list->AddAtIndex(randomZomb, position);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void everyone_out_action(LinkedList<Zombie>* list, Zombie randomZomb) {
    list->RemoveAllOf(randomZomb);
}

void you_out_action(LinkedList<Zombie>* list, Zombie randomZomb) {
    list->RemoveTheFirst(randomZomb);
}

void brains_action(LinkedList<Zombie>* list, Zombie randomZomb) {
    if (!list) {
        std::cerr << "Error: List is null!" << std::endl;
        return;
    }
    list->AddToFront(randomZomb);
    list->AddToEnd(randomZomb);
    list->AddAtIndex(randomZomb, (list->Length()) / 2);
}

void rainbow_action(LinkedList<Zombie>* list, Zombie randomZomb) {
    engine_action(list, randomZomb);
    caboose_action(list, Zombie('R'));
    caboose_action(list, Zombie('Y'));
    caboose_action(list, Zombie('G'));
    caboose_action(list, Zombie('B'));
    caboose_action(list, Zombie('C'));
    caboose_action(list, Zombie('M'));
}

void friends_action(LinkedList<Zombie>* list, Zombie randomZomb) {
    if (!list) {
        std::cerr << "Error: List is null!" << std::endl;
        return;
    }
    Node<Zombie>* firstOfType = list->Find(randomZomb);
    if (firstOfType) {
        if (rand() % 2 == 0) list->AddBefore(firstOfType, randomZomb);
        else list->AddAfter(firstOfType, randomZomb);
    } else {
        caboose_action(list, randomZomb);
    }
}

int main(int argc, char* argv[]) {
   
    // Existing main function logic
    int seed = time(0);
    if (argc == 3 && std::string(argv[1]) == "-s") {
        seed = std::stoi(argv[2]);
    }
    srand(seed);

    LinkedList<Zombie> congaLine;
    int zombieType = rand() % 6;
    char zombieColors[] = {'R', 'Y', 'G', 'B', 'C', 'M'};
    Zombie randomZomb(zombieColors[zombieType]);

    rainbow_action(&congaLine, Zombie(randomZomb));
    for (int i = 0; i < 3; i++) {
        zombieType = rand() % 6;
        randomZomb = Zombie(zombieColors[zombieType]);
        brains_action(&congaLine, Zombie(randomZomb));
    }

    int rounds;
    std::cout << "Enter number of rounds: ";
    while (!(std::cin >> rounds)) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        std::cout << "Invalid input. Please enter an integer: ";
    }

    for (int round = 0; round < rounds; round++) {
        if (round % 5 == 0) {
            try {
                congaLine.RemoveFromFront();
                congaLine.RemoveFromEnd();
            } catch (...) {
                std::cerr << "Error: Unable to remove from an empty list!" << std::endl;
            }
        }

        int action = rand() % 8;
        zombieType = rand() % 6;
      
        randomZomb = Zombie(zombieColors[zombieType]);

        std::cout << "Round: " << round << std::endl;
        congaLine.PrintList();
        std::cout << "New Zombie: " << randomZomb << " -- Action: ";
        try {
            switch (action) {
                case 0:
                    std::cout << "[Engine!]" << std::endl;
                    engine_action(&congaLine, randomZomb);
                    break;
                case 1:
                    std::cout << "[Caboose!]" << std::endl;
                    caboose_action(&congaLine, randomZomb);
                    break;
                case 2:
                    std::cout << "[Jump In!]" << std::endl;
                    jump_in_action(&congaLine, randomZomb, rand() % (congaLine.Length()+1));
                    break;
                case 3:
                    std::cout << "[Everyone Out!]" << std::endl;
                    everyone_out_action(&congaLine, randomZomb);
                    break;
                case 4:
                    std::cout << "[You Out!]" << std::endl;
                    you_out_action(&congaLine, randomZomb);
                    break;
                case 5:
                    std::cout << "[Brains!]" << std::endl;
                    brains_action(&congaLine, randomZomb);
                    break;
                case 6:
                    std::cout << "[Rainbow!]" << std::endl;
                    rainbow_action(&congaLine, randomZomb);
                    break;
                case 7:
                    std::cout << "[New Friends!]" << std::endl;
                    friends_action(&congaLine, randomZomb);
                    break;
            }
        } catch (const std::exception &e) {
            std::cerr << "Action failed: " << e.what() << std::endl;
        }

        std::cout << "The conga line is now: ";
        congaLine.PrintList();
        std::cout << std::endl;
    }

    return 0;
}
