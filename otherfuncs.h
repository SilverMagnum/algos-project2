#ifndef OTHERFUNCS_H
#define OTHERFUNCS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int alphabets = 5;

int align(const string &a, const string &b, int alpha_gap, int alpha[alphabets][alphabets], string &a_aligned, string &b_aligned);

void printVector(const vector<vector<int> > &A);

int min(int a, int b, int c);

#endif // OTHERFUNCS_H
