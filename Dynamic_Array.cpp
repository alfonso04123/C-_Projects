/*

    Description: Dynamic Arrays
    Usage: 
    Add a command line option -s <integer> 
    to allow the user to provide a seed for the random number generator. 
    This seed value should be given to srand(<int>). 
    If no -s option is given, then seed the random number generator with time: srand(time(0)); 
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include "termcolor.hpp"

using namespace std;

int** landMass(int, int);
void initLandValue(int** array, int, int);
void dropDirtBall(int** landmass, int maxWidth, int maxHeight, int centerX, int centerY, int radius, int power);
bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy);
int findMax(int** landmass, int width, int height);
void normalizeMap(int** landmass, int width, int height, int maxVal);
float frand();
char** finalizeMap(int** landmass, int maxX, int maxY, int waterLine);
void printLand(int** land, int width, int height, ofstream& filename);
void printLand(char** land, int width, int height, ofstream& filename);

int main(int argc, char** argv)
{   
    std::cout << termcolor::colorize;
    
    if(argc != 1 && argc != 3)
    {
        cout << "Not correct command!" << endl; 
        return 1;
    }

    if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        srand(atoi(argv[2]));
        cout << "Seed provided: " << argv[2] << endl;
    } else {
        srand(time(0));
        cout << "No seed provided, using time(0)" << endl;
    }
    
    int width, height, waterLine, radius, power, number;
    int ** land;
    
    cout << "Welcome to Yanzhe Qu's CSE240 Terraformer!!\n";
    cout << "Enter grid width: ";
    cin >> width;
    cout << "Enter grid height: ";
    cin >> height;
    cout << "Enter value for waterline (40-200): ";
    cin >> waterLine;
    cout << "Enter dirtball radius (minimum 2): ";
    cin >> radius;
    cout << "Enter dirtball power rating (minimum = radius): ";
    cin >> power;
    cout << "Enter number of dirtballs to drop: ";
    cin >> number;

    land = landMass(height, width);
    initLandValue(land, width, height);

    ofstream rawFile("raw_landmass.txt"), normFile("normalized_landmass.txt"), finalFile("final_landmass.txt");
    
    for (int i = 0; i < number; i++) 
    {
    dropDirtBall(land, width, height, 0, 0, radius, power);
    }
    printLand(land, width, height, rawFile);
    cout<<endl<<endl;
    
    normalizeMap(land, width, height, findMax(land, width, height));
    printLand(land, width, height, normFile);
    cout<<endl<<endl;

    char** charArray = finalizeMap(land, width, height, waterLine);
    printLand(charArray, width, height, finalFile);
    
    for (int i = 0; i < height; i++) 
    {
        delete[] land[i];
    }
    
    delete[] land;
    
    for (int i = 0; i < height; i++) 
    {
        delete[] charArray[i];
    }
    
    delete[] charArray;

    rawFile.close();
    normFile.close();
    finalFile.close();

    return 0;
}

int** landMass(int height, int width){

    int** initLand = new int*[height];

    for(int i = 0; i < height; i++){
       initLand[i] = new int[width];
    }
    return initLand;
}

void initLandValue(int** landInit, int width, int height){

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            landInit[i][j] = 0;
        }
    }
}

bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy)
{
    if((x < minx) || (x > maxx))
    {
        return false; //if x is out of bound, return false
    }

    if((y < miny) || (y > maxy))
    {
        return false; //if y is out of bound, return false
    }
    
    return true;
}

void dropDirtBall(int** newLand, int width, int height, int centerX, int centerY, int radius, int powerRating)
{       
        
        centerX = frand() * width;
        centerY = frand() * height;

    for(int x = centerX - radius; x <= centerX + radius; x++)
    {
        for(int y = centerY - radius; y <= centerY + radius; y++)
        {
            if(boundsCheck(x, y, 0, 0, width-1, height-1))
            {
               float distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)); //if the 2D array is inside the bound, calculate the distance
               
               if (distance <= radius) {
                int impact_value = powerRating - floor(distance); 
                newLand[y][x] += impact_value;
                }
            }
        }
    }
}

int findMax(int** landScope, int width, int height)
{
    int maxVal = landScope[0][0];
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(landScope[i][j] > maxVal){
                maxVal = landScope[i][j];
            }
        }
    }

    return maxVal;
}

void normalizeMap(int** landFiled, int width, int height, int maxVal)
{    
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float division;
            division = (float) landFiled[i][j] / maxVal;
            landFiled[i][j] = division * 255;
        }
    }
}

float frand()
{
  return ((float)(rand() % RAND_MAX))/(float)RAND_MAX;
}

char** finalizeMap(int** landFinal, int width, int height, int waterLine)
{
    char** arrayChar = new char*[height];
    for(int i = 0; i < height; i++)
    {
        arrayChar[i] = new char [width]; 
    }

    for(int i=0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        { 
            if(landFinal[i][j] < (waterLine / 2))
            {
                arrayChar[i][j] = '#';
            }
            else if(landFinal[i][j] <= waterLine)
            {
                arrayChar[i][j] = '~';
            }
            else if(landFinal[i][j] < (int) (waterLine + (255 - waterLine) * 0.15))
            {
                arrayChar[i][j] = '.';
            }
            else if(landFinal[i][j] < (int) (waterLine + (255 - waterLine) * 0.4))
            {
                arrayChar[i][j] = '-';
            }
            else if(landFinal[i][j] < (int) (waterLine + (255 - waterLine) * 0.8))
            {
                arrayChar[i][j] = '*';
            }
            else
            {
                arrayChar[i][j] = '^';
            }
        }
    }
    return arrayChar;
}

void printLand(int** landPrint, int width, int height, ofstream& filename)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << setw(4) << landPrint[i][j];
            filename << setw(4) << landPrint[i][j];
        }
        cout << endl;
        filename << endl;
    }
    filename.close();
}

void printLand(char** landPrint, int width, int height, ofstream& fileName)
{   
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(landPrint[i][j] == '#')
            cout << termcolor::green << landPrint[i][j];
            else if(landPrint[i][j] == '~')
            cout << termcolor::yellow << landPrint[i][j];
            else if(landPrint[i][j] == '.')
            cout << termcolor::blue << landPrint[i][j];
            else if(landPrint[i][j] == '-')
            cout << termcolor::red << landPrint[i][j];
            else if(landPrint[i][j] == '*')
            cout << termcolor::cyan << landPrint[i][j];
            else if(landPrint[i][j] == '^')
            cout << termcolor::magenta << landPrint[i][j];
            else
            cout << "Something went wrong...";

            fileName << landPrint[i][j];
        }
        cout << endl;
        fileName << endl;
    }
    fileName.close();
}