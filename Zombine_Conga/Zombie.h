#ifndef ZOMBIE_QU_H
#define ZOMBIE_QU_H

#include <iostream>
#include <string>

class Zombie {
private:
    char type;

public:
    // Default constructor
    Zombie() : type(' ') {}

    // Parameterized constructor
    Zombie(char t) : type(t) {}

    // Getter for type
    char getType(); 
    
    // Equality operator
    bool operator==(Zombie other) {
        return type == other.type;
    }

    // Friend function for ostream
    friend std::ostream& operator<<(std::ostream& os, Zombie& z);
};

#endif
