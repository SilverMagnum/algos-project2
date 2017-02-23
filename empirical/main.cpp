#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>

using namespace std;

typedef vector<char> char_array;

char_array charset() {
    return char_array(
    {'A', 'T', 'G', 'C'
    });
}

void returnDNA();

int main() {
    returnDNA();

    return 0;
}

string random_dna(size_t length, function<char(void)> rand_char) {
    string str(length,0);
    generate_n( str.begin(), length, rand_char );
    return str;
}

void returnDNA() {
    const auto ch_set = charset();

    default_random_engine rng(random_device{}());

    uniform_int_distribution<> dist(0, ch_set.size()-1);

    auto randchar = [ ch_set,&dist,&rng ](){return ch_set[ dist(rng) ];};

    auto length = 500;
    for(int i = 0; i < 10; i++) {
        cout << random_dna(length,randchar) << endl;
    }
}
