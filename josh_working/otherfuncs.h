#ifndef OTHERFUNCS_H
#define OTHERFUNCS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t alphabets = 26;

/*
 * Returns the Needleman-Wunsch score for the best alignment of a and b
 * and stores the aligned sequences in a_aligned and b_aligned
 */
int align(const string &a, const string &b, int alpha_gap,
        int alpha[alphabets][alphabets], string &a_aligned,
        string &b_aligned);

void printVector(const vector<vector<int> > &A);

int min(int a, int b, int c);

#endif // OTHERFUNCS_H
