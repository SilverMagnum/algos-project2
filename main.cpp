#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//#include "otherfuncs.h"

using namespace std;

int* stringToIntArray(string dna);
string intArrayToString(int* digitDNA);
int align(int* inputOne, int* inputTwo, int inputOneSize, int inputTwoSize, int alpha[5][5], int* outputOne, int* outputTwo);
int min(int a, int b, int c);

int main() {
    int arr[5][5] = {   //	 -  A  T  G  C
                            {0, 1, 2, 1, 3},//-
                            {1, 0, 1, 5, 1},//A
                            {2, 1, 0, 9, 1},//T
                            {1, 5, 9, 0, 1},//G
                            {3, 1, 1, 1, 0}	//C
                    };
    string a1 = "AACAGTTACC", b1 = "TAAGGTCA", a2, b2;
	int *dnaOne, *dnaTwo;
	int *pairOne, *pairTwo;
	int pairSize = (a1.size() + b1.size());
	int weight;

	pairOne = new int[pairSize];
	pairTwo = new int[pairSize];

	for(int i = 0; i < pairSize; i++) {
        pairOne[i] = 9;
        pairTwo[i] = 9;
	}

    //cout << "Data has been initialized." << endl;

	dnaOne = stringToIntArray(a1);
	dnaTwo = stringToIntArray(b1);

    //cout << "Int arrays have been created." << endl;

	weight = align(dnaOne, dnaTwo, a1.size(), b1.size(), arr, pairOne, pairTwo);

    //cout << "Align has run successfully." << endl;

    a2 = intArrayToString(pairOne);
    b2 = intArrayToString(pairTwo);

    cout << "1st String: " << a2 << endl;
    cout << "2nd String: " << b2 << endl;
    cout << "Current weight is: " << weight << endl;

    // Aligned sequences
    //string a2, b2;
    //int penalty = align(a1, b1, arr, a2, b2);
    return 0;
}

int* stringToIntArray(string dna) {
    int stringSize = dna.size();
	int* digitDNA;

	digitDNA = new int[stringSize];

	for(int i = 0; i < stringSize; ++i) {
		if(dna[i] == 'A') {
			digitDNA[i] = 1;
		}

		else if(dna[i] == 'T') {
			digitDNA[i] = 2;
		}

		else if(dna[i] == 'G') {
			digitDNA[i] = 3;
		}

		else if(dna[i] == 'C') {
			digitDNA[i] = 4;
		}
	}

	return digitDNA;
}

string intArrayToString(int* digitDNA) {
    string dna;
    for(int i = 0; digitDNA[i] != 9; i++) {
        if(digitDNA[i] == 0) {
            dna = dna + '-';
        }
        else if(digitDNA[i] == 1) {
            dna = dna + 'A';
        }
        else if(digitDNA[i] == 2) {
            dna = dna + 'T';
        }
        else if(digitDNA[i] == 3) {
            dna = dna + 'G';
        }
        else if(digitDNA[i] == 4) {
            dna = dna + 'C';
        }
    }

    return dna;
}

int align(int* inputOne, int* inputTwo, int inputOneSize, int inputTwoSize, int alpha[5][5], int* outputOne, int* outputTwo) {
    //cout << "We've made it inside the align function!" << endl;
    int n = inputOneSize;
    int m = inputTwoSize;

    vector<vector<int> > contour(n + 1, vector<int>(m + 1));
    //int stringSize = dna.size();
	//int* digitDNA;

	//digitDNA = new int[stringSize];

    //cout << "Contour vector was made successfully." << endl;

    for (int i = 0; i <= m; i++) {
        contour[0][i] = 3 * i;
    }

    for (int i = 0; i <= n; i++) {
        contour[i][0] = 3 * i;
    }

    //cout << "Contour was given some values here..." << endl;

    //cout << "M: " << m << " | N: " << n << endl;
    for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			//cout << "Loop is about to run for the " << (i*j) << "th time" << endl;
			contour[i][j] = min(	contour[i-1][j-1] + alpha[inputOne[i-1]][inputTwo[j-1]],
                                    contour[i-1][j] + alpha[inputOne[i-1]][0],
                                    contour[i][j-1] + alpha[0][inputTwo[j-1]]);
            //cout << "Loop has run " << (i*j) << " times." << endl;
		}
	}

	//cout << "Contour was initialized successfully!" << endl;

    int j = m;
    int i = n;
    int x = 0;
    int y = 0;
    for (; i >= 1 && j >= 1; --i) {
        if (contour[i-1][j-1] + alpha[inputOne[i-1]][inputTwo[j-1]])  {
            outputOne[x] = inputOne[i-1];
            outputTwo[y] = inputTwo[j-1];
            --j; x++; y++;
        }
        else if (contour[i-1][j] + alpha[0][inputTwo[j-1]]) {
            outputOne[x] = inputOne[i-1];
            outputTwo[y] = 0;
            x++; y++;
        }
        else {
            outputOne[x] = 0;
            outputTwo[y] = inputTwo[j-1];
            --j;
        }
    }

    while (i >= 1 && j < 1) {
        outputOne[x] = inputOne[i-1];
        outputTwo[y] = 0;
        --i; x++; y++;
    }
    while (j >= 1 && i < 1) {
        outputOne[x] = 0;
        outputTwo[y] = inputTwo[j-1];
        --j; x++; y++;
    }

    return contour[n][m];
}

int min(int a, int b, int c) {
    //cout << "Min has been run." << endl;
    if (a <= b && a <= c) {
        return a;
    }
    else if (b <= a && b <= c) {
        return b;
    }
    else {
        return c;
    }
}
