#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "otherfuncs.h"

using namespace std;

int main() {
    ifstream infile;
    infile.open("imp2cost.txt");
    if(!infile) {
        cout << "The file imp2cost.txt does not exist." << endl;
    }

    int arr[5][5] = {
        {0, 1, 2, 1, 3},
        {1, 0, 1, 5, 1},
        {2, 1, 0, 9, 1},
        {1, 5, 9, 0, 1},
        {3, 1, 1, 1, 0}
    };

    // The input strings that need to be aligned
    string a1 = "AACAGTTACC";
    string b1 = "TAAGGTCA";

    // Penalty for any matrix_size matched with a gap
    int gap_penalty = 1;

    /*
     * alpha[i][j] = penalty for matching the ith matrix_size with the
     *               jth matrix_size.
     * Here: Penalty for matching an char with anoter one is 2
     *       Penalty for matching an char with itself is 0
     */
    int alpha[matrix_size][matrix_size];
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            if (i == j) {
                alpha[i][j] = 0;
            }
            else {
                alpha[i][j] = 2;
            }
        }
    }

    // Aligned sequences
    string a2, b2;
    int penalty = align(a1, b1, gap_penalty, alpha, a2, b2, arr);

    cout << "Initial Sequence a: " << a1 << endl;
    cout << "Initial Sequence b: " << b1 << endl;
    cout << "Total Alignment Cost: " << penalty << endl;
    cout << "Aligned sequences a & b: " << endl;
    cout << a2 << endl;
    cout << b2 << endl;

    return 0;
}
