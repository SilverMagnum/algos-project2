#include <iostream>

#include "otherfuncs.h"

using namespace std;

int main() {
    int cost[5][5];
    getCostTable(cost);

    // The input strings that need to be aligned
    string a1 = "AACAGTTACC";
    string b1 = "TAAGGTCA";

    // Penalty for any alphabet matched with a gap
    int gap_penalty = 1;

//    int alpha[4][4] = {
//            {0, 1, 5, 1},
//            {1, 0, 9, 1},
//            {5, 9, 0, 1},
//            {1, 1, 1, 0}
//        };

    /*
     * alpha[i][j] = penalty for matching the ith alphabet with the
     *               jth alphabet.
     * Here: Penalty for matching an alphabet with anoter one is 1
     *       Penalty for matching an alphabet with itself is 0
     */
    int alpha[alphabets][alphabets] = {{0}};
    for (size_t i = 0; i < alphabets; ++i) {
        for (size_t j = 0; j < alphabets; ++j) {
            if (i == j) alpha[i][j] = 0;
            else alpha[i][j] = 2;

        }
    }

    string a2, b2;
    int penalty = align(a1, b1, gap_penalty, alpha, a2, b2);

    cout << "a: " << a1 << endl;
    cout << "b: " << b1 << endl;
    cout << "Needleman-Wunsch Score: " << penalty << endl;
    cout << "Aligned sequences: " << endl;
    cout << a2 << endl;
    cout << b2 << endl;

    return 0;
}
