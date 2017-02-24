#ifndef OTHERFUNCS_H
#define OTHERFUNCS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const size_t alphabets = 26;

int align(int* inputOne, int* inputTwo, int inputOneSize, int inputTwoSize, int alpha[5][5], int* outputOne, int* outputTwo);

void printVector(const vector<vector<int> > &A);

int min(int a, int b, int c);

void removeDelim(string &str, char delim);

void getCostTable(int cost[5][5]);

int* stringToIntArray(string dna);

string intArrayToString(int* digitDNA);

#endif // OTHERFUNCS_H
