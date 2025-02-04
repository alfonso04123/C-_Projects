/*
Description: a rotor machine to encrypt and decrypt
Usage:
usage 
./exe -i <file>
./exe -e <file1> <file2> -r <r1> <r2>
./exe -d <file1> <file2> -r <r1> <r2>
./exe -e <file1> <file2> -r <r1> <r2> -i <file>
./exe -d <file1> <file2> -r <r1> <r2> -i <file>
*/

#include "rotorMachine.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    
    int rotor1[28];
    int rotor2[28];

   if(argc != 3 && argc != 7 && argc != 9) {
    std::cerr << "Usage error: Incorrect number of arguments\n";
    return 1;
    }
    else if (argc == 3 && strcmp(argv[1], "-i") == 0) {
    buildIni(argv[2]); 
    
    }
    else if ((argc == 7 || argc == 9) && 
         (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0) && strcmp(argv[4], "-r") == 0) {
    if (argc == 9 && strcmp(argv[7], "-i") == 0) {
        buildIni(argv[8]);  // Initialize if -i is included
    }
    buildRotors(rotor1, rotor2);

    setRotor1(rotor1, atoi(argv[5]));  // Set rotor positions
    setRotor2(rotor2, atoi(argv[6]));

    std::ifstream original(argv[2]);
    std::ofstream result(argv[3]);
    if (!original.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    // Encrypt or decrypt based on the command
    if (strcmp(argv[1], "-e") == 0) {
        encryptFile(original, result, rotor1, rotor2);
    } else {
        decryptFile(original, result, rotor1, rotor2);
    }

    original.close();
    result.close();
    }
    return 0;
}

void buildIni(char *list)
{
     // Open the configuration file for reading
    std::ifstream configFile(list);
    if (!configFile.is_open()) {
        std::cerr << "Error opening configuration file." << std::endl;  //if the file cannot be opened, show error
        return;
    }

    // Open the rotors.ini file for writing encrypted values
    std::ofstream outFile("rotors.ini");
    if (!outFile.is_open()) {
        std::cerr << "Error creating rotors.ini file." << std::endl;
        configFile.close();
        return;
    }

    int value;
    // Read each integer from the config file, encrypt it, and write to rotors.ini
    while (configFile >> value) {
        int encryptedValue = value ^ 42; // Apply XOR with 42
        outFile << encryptedValue << "\n";
    }

    // Close both files
    configFile.close();
    outFile.close();
}

void buildRotors(int rotor1[28], int rotor2[28])
{
    std::ifstream inFile("rotors.ini");
    if (!inFile.is_open()) {
        std::cerr << "Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file." << std::endl; //if the file cannot be opened, show error
        return;
    }

    int value, count = 0;
    while (inFile >> value) {
        if (count < 28) {
            rotor1[count] = value ^ 42;  // Decrypting the value
        } else if (count < 56) {
            rotor2[count - 28] = value ^ 42;  // Decrypting the value
        }
        count++; //count number of value in rotor list
    }

    inFile.close();
}

void rotateRotorRight(int rotor[28])
{
    int last = rotor[27];
    for (int i = 27; i > 0; i--) {
        rotor[i] = rotor[i - 1];
    }
    rotor[0] = last;
}

void rotateRotorLeft(int rotor[28])
{
    int first = rotor[0];
    for (int i = 0; i < 27; i++) {
        rotor[i] = rotor[i + 1];
    }
    rotor[27] = first;
}

void setRotor1(int rotor[28], int rotations)
{
     for (int i = 0; i < rotations; i++) {
        rotateRotorRight(rotor);
    }
}
void setRotor2(int rotor[28], int rotations)
{
    for (int i = 0; i < rotations; i++) {
        rotateRotorLeft(rotor);
    }
}

int charToIndex(char convert)
{
     
    if(convert == ' ') return 26;
    if(convert == '.') return 27;

    convert = toupper(convert); //convert all lowercase char to uppercase
    return int(convert - 65);
   
}

char indexToChar(int value)
{
    if(value == 26) return ' ';
    if(value == 27) return '.';

    return char(value + 65);
}

void encryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28])
{
    char buffer[256];
    while (infile.getline(buffer, 256)) {  // read one line 
        
        for (int i = 0; buffer[i]; i++) {  // get every char in line
            char ch = toupper(buffer[i]);  // change to uppercase
            //Todo toupper might change space and .
            if ((ch < 'A' || ch > 'Z') && ch != ' ' && ch != '.') {
                outfile.put(ch);  // if it is not letter, input them directly
            } else {
                int index = charToIndex(ch);  // change char to index
                int rotor1Value = rotor1[index];
                for(int i = 0; i < 28; i++){
                    if(rotor2[i] == rotor1Value){
                        index = i;
                    }
                }  // get value of rotor1
                char encryptedChar = indexToChar(index);  // use index find the correspond char in rotor2
                outfile.put(encryptedChar);  // input the encrypted char
                rotateRotorRight(rotor1);  // right turn rotor1
                rotateRotorLeft(rotor2);  // left turn rotor2
            }
        }
        outfile.put('\n');  
    }
}
void decryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28])
{
    char buffer[256];
    while (infile.getline(buffer, 256)) {  // read one line 
        
        for (int i = 0; buffer[i]; i++) {  // get every char in line
            char ch = toupper(buffer[i]);  // change to uppercase
            
            if ((ch < 'A' || ch > 'Z') && ch != ' ' && ch != '.') {
                outfile.put(ch);  // if it is not letter, input them directly
            } else {
                int index = charToIndex(ch);  // change char to index
                int rotor1Value = rotor2[index];
                for(int i = 0; i < 28; i++){
                    if(rotor1[i] == rotor1Value){
                        index = i;
                    }
                }  // get value of rotor1
                char encryptedChar = indexToChar(index);  // use index find the correspond char in rotor2
                outfile.put(encryptedChar);  // input the encrypted char
                rotateRotorRight(rotor1);  // right turn rotor1
                rotateRotorLeft(rotor2);  // left turn rotor2
            }
        }
        outfile.put('\n');  
    }
}
