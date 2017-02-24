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
    getCostTable(cost);

    // The input strings that need to be aligned
    string a1 = "AACAGTTACC";
    string b1 = "TAAGGTCA";

    // Penalty for any alphabet matched with a gap
    int gap_penalty = 1;

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
    cout << "Alignment Cost: " << penalty << endl;
    cout << "Aligned sequences: " << endl;
    cout << a2 << endl;
    cout << b2 << endl;

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
