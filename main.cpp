#include <iostream>
#include <functional>
#include <random>

#include "otherfuncs.h"

using namespace std;

typedef vector<char> char_array;

char_array charset() {
    return char_array(
    {'A', 'T', 'G', 'C'
    });
}

string returnDNA();

int main() {
    int cost[5][5] = {{0}};
    getCostTable(cost); //Opens cost matrix file and stores values into a 2d int array

    //Opening the dna input file and createing the output file. Includes checks for file existence
    ifstream indna;
    ofstream outdna;
    indna.open("imp2input.txt");
    outdna.open("imp2output.txt");
    if(!indna.is_open()) {
        cout << "File imp2input.txt does not exist" << endl;
    }
    if(!outdna.is_open()) {
        cout << "Unable to create file imp2output.txt" << endl;
    }

    string line;
    while(getline(indna, line)) {
        //Initialize variables
        string a1 = line.substr(0, line.find(','));
        string b1 = line.substr(line.find(',') + 1, line.length());
        string a2, b2;
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

        dnaOne = stringToIntArray(a1);
        dnaTwo = stringToIntArray(b1);

        weight = align(dnaOne, dnaTwo, a1.size(), b1.size(), cost, pairOne, pairTwo);

        a2 = intArrayToString(pairOne);
        b2 = intArrayToString(pairTwo);

        outdna << a2 << ',' << b2 << ':' << weight << endl;
    }
    cout << "The \"imp2output.txt\" file has been created in the current directory." << endl;
    indna.close();
    outdna.close();

    return 0;
}

string random_dna(size_t length, function<char(void)> rand_char) {
    string str(length,0);
    generate_n( str.begin(), length, rand_char );
    return str;
}

string returnDNA() {
    const auto ch_set = charset();

    default_random_engine rng(random_device{}());

    uniform_int_distribution<> dist(0, ch_set.size()-1);

    auto randchar = [ ch_set,&dist,&rng ](){return ch_set[ dist(rng) ];};

    auto length = 500;
    string s = random_dna(length, randchar);

    return s;
}
