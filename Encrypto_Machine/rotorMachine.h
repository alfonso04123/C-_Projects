#pragma once
#ifndef ROTORMACHINE_H
#define ROTORMACHINE_H

#include <fstream>

void buildIni(char *);
void buildRotors(int [28], int[28]);

void rotateRotorRight(int[28]);
void rotateRotorLeft(int[28]);

void setRotor1(int[28], int);
void setRotor2(int[28], int);

int charToIndex(char);
char indexToChar(int);

void encryptFile(std::ifstream &, std::ofstream &, int[28], int[28]);
void decryptFile(std::ifstream &, std::ofstream &, int[28], int[28]);

#endif
