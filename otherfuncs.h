#ifndef OTHERFUNCS_H
#define OTHERFUNCS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int matrix_size = 5;

int align(const string &a, const string &b, int alpha_gap, int alpha[matrix_size][matrix_size], string &a_aligned, string &b_aligned,
          int weights[matrix_size][matrix_size]);

void printVector(const vector<vector<int> > &A);

int min(int a, int b, int c);

int gapWeight(int weights[matrix_size][matrix_size], char c1, char c2);

#endif // OTHERFUNCS_H
