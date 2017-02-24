#include "otherfuncs.h"

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
    int n = inputOneSize;
    int m = inputTwoSize;

    vector<vector<int> > contour(n + 1, vector<int>(m + 1));

    contour[0][0] = 0;

    for (int i = 1; i <= m; i++) {
        contour[0][i] = contour[0][i-1] + alpha[0][inputTwo[i-1]];
    }

    for (int i = 1; i <= n; i++) {
        contour[i][0] = contour[i-1][0] + alpha[inputOne[i-1]][0];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            contour[i][j] = min(contour[i-1][j-1] + alpha[inputOne[i-1]][inputTwo[j-1]],
                    contour[i-1][j] + alpha[inputOne[i-1]][0],
                    contour[i][j-1] + alpha[0][inputTwo[j-1]]);
        }
    }
	
    int j = m;
    int i = n;
    int x = 0;
    int y = 0;
    int weightRecalc = 0;
    for (; i >= 1 && j >= 1; --i) {
        if (contour[i][j] == (contour[i-1][j-1] + alpha[inputOne[i-1]][inputTwo[j-1]])) {
            outputOne[x] = inputOne[i-1];
            outputTwo[y] = inputTwo[j-1];
            --j; x++; y++;
        }
        else if (contour[i][j] == (contour[i-1][j] + alpha[inputOne[i-1]][0])) {
            outputOne[x] = inputOne[i-1];
            outputTwo[y] = 0;
            x++; y++;
        }
        else if (contour[i][j] == (contour[i][j-1] + alpha[0][inputTwo[j-1]])) {
            outputOne[x] = 0;
            outputTwo[y] = inputTwo[j-1];
            --j; x++; y++; i++;
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

void printVector(const vector<vector<int> > &A) {
    for (auto i : A) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void removeDelim(string &str, char delim) {
    str.erase(remove(str.begin(), str.end(), delim), str.end());
}

void getCostTable(int cost[5][5]) {
    ifstream costfile;
    costfile.open("imp2cost.txt");

    if(!costfile.is_open()) {
        cout << "File imp2cost.txt does not exist" << endl;
    }

    string line;
    int line_count = 0;
    char delim = ',';
    while(getline(costfile, line)) {
        if(line_count >= 1 && line_count <=5) {
            removeDelim(line, delim);
            for(int i = 0; i <= 5; i++) {
                if(line.at(i) != '-' && line.at(i) != 'A' && line.at(i) != 'C' &&
                        line.at(i) != 'G' && line.at(i) != 'T') {
                    char c = line.at(i);
                    int j = c - 48;
                    cost[line_count - 1][i - 1] = j;
                }
            }
        }
        line_count++;
    }
    costfile.close();
}
