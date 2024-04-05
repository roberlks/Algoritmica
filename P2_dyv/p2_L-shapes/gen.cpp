#include <iostream>
using namespace std;

// Max k of n = 2^k
const int MAXK = 8;
const int MINK = 2;

/**
 * @brief Returns a random int x € [a,b)
*/
int rnd(int a, int b){
    return a + rand() % (b - a + 1);
}

/**
 * @brief Generator for problem L-shape
 * @param argv[0] -> the seed for the random numbers
*/
int main(int argc, char * argv[]){
    int seed = atoi(argv[1]);
    srand(seed);
    int k = rnd(1,MAXK+1);
    // n must be a power of 2 (size of the square)
    int n = 1 << k;
    // (r,c) -> position of the square tile (NOT zero base)
    int r = rnd(0,n-1);
    int c = rnd(0,n-1);
    // OUTPUT
    cout << n << endl;
    cout << r << " " << c << endl;
    return 0;
}