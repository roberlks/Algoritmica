#include <iostream>
#include <set>
using namespace std;

typedef long double ld;

// Maximum size of the array
const int MAXN = 12;
const int MINN = 7;
// Side of the map
const int R = 1;

/**
 * @brief Returns a random float x € [a,b)
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
    int n = rnd(MINN,MAXN+1);
    // OUTPUT
    cout << n << endl;
    set<pair<ld,ld>> s;
    for(int i=0; s.size() < n; ++i){
        pair<ld,ld> elem(rnd(-R,R),rnd(-R,R));
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