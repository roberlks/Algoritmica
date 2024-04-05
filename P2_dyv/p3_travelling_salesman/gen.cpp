#include <iostream>
#include <set>
using namespace std;

typedef long double ld;

// Maximum size of the array
const int MAXN = 12;
// Side of the map
const int N = 1000;

/**
 * @brief Returns a random int x € [a,b)
*/
ld rnd(ld a, ld b){
    ld f = (ld)rand() / RAND_MAX;
    return a + f*(b-a);
}

/**
 * @brief Generator for Travelling Salesman Problem
 * @param argv[0] -> the seed for the random numbers
*/
int main(int argc, char * argv[]){
    int seed = atoi(argv[1]);
    srand(seed);
    int n = rnd(1,MAXN+1);
    // OUTPUT
    cout << n << endl;
    set<pair<ld,ld>> s;
    for(int i=0; s.size() < n; ++i){
        pair<ld,ld> elem(rnd(-N,N),rnd(-N,N));
        if(!s.count(elem)) {
            s.insert(elem);
            // Generate random positive and negative numbers
            //cout << (rand() - RAND_MAX/2) << " " << (rand() - RAND_MAX/2) << endl;
            cout << "(" << elem.first << ", " << elem.second << ")" << endl;
        }
    }
    cout << endl;
    return 0;
}