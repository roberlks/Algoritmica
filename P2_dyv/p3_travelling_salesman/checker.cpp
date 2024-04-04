#include <bits/stdc++.h>
#include "City.h"
using namespace std;

// Maximum error percentage tolerated
const double EPS = 56;

/**
 * @brief Checks the solution for Travelling Salesman Problem problem.
 * It checks that the solution given is **aproximately** the right one
*/
int main(int argc, char * argv[]){
    if(argc < 4){
        cout << "Error missing arguments" << endl;
        return -1;
    }
    // Read files
    ifstream fin(argv[1]);
    ifstream ans(argv[2]);
    ifstream cor(argv[3]);

    if(!fin){
        cout << argv[0] << endl;
        cout << "Error opening input_file" << endl;
        cout << "ERROR: " << strerror(errno) << endl;
        return -1;
    }
    
    int n;
    fin >> n;
    City cities[n];
    City myCycle[n+1]; 
    int correctCycle[n+1];
    for(int i=0; i<n; ++i){
        fin >> cities[i];
        ans >> myCycle[i];
        //cor >> correctCycle[i];
    }
    ans >> myCycle[n];
    //cor >> correctCycle[n];

    // Check it is in fact a cycle a visits all cities ONLY once
    if(myCycle[0] != cities[0]){
        cout << "WA: doesn't start at the origin city" << endl;
        return -1;
    }
    if(myCycle[n] != cities[0]){
        cout << "WA: doesn't end at the origin city (not a cycle)" << endl;
        return -1;
    }

    bool visited[n];
    memset(visited,false,sizeof(visited));
    for(int i=1; i<n; ++i){
        if(visited[i]){
            cout << "WA: visits a city more than once" << endl;
            return -1;
        }
        visited[i] = true;
    }

    // Check aproximate sum
    ld ans_sum = 0;
    for(int i=0; i<n; ++i)
        //ans_sum += cities[myCycle[i]].dist(cities[myCycle[i+1]]); // Print index
        ans_sum += myCycle[i].dist(myCycle[i+1]);   // Print cities
    ld cor_sum = 0;
    //for(int i=0; i<n; ++i)
    //    cor_sum += cities[correctCycle[i]].dist(cities[correctCycle[i+1]]);;
    cor >> cor_sum;

    // Calculate percentage of error
    ld error_percentage = abs(ans_sum - cor_sum) * 100.0/cor_sum;
    if(error_percentage > EPS){
        cout << "WA: not the minimum distance" << endl;
        cout << "ans: " << ans_sum << endl;
        cout << "correct: " << cor_sum << endl;
        cout << "error: " << error_percentage << "%" << endl;
        return -1;
    }
    fin.close();ans.close();cor.close();
    return 0;
}
