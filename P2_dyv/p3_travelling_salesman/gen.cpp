#include <iostream>
using namespace std;

// Maximum size of the array
const int MAXN = 10;

/**
 * @brief Returns a random int x € [a,b)
*/
int rnd(int a, int b){
    return a + rand() % (b - a + 1);
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
    for(int i=0; i<n; ++i){
        // Generate random positive and negative numbers
        //cout << (rand() - RAND_MAX/2) << " " << (rand() - RAND_MAX/2) << endl;
        cout << "(" << rnd(-3,3) << ", " << rnd(-3,3) << ")" << endl;
    }
    cout << endl;
    return 0;
}