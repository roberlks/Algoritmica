#include <bits/stdc++.h>
#include "../../../Include/City.h"
using namespace std;

//#define TIME
//#define COST
//#define TSP

#ifndef TIME 
    #ifndef COST
        #define TSP
    #endif
#endif

// operator << for vector<City>
template <typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    for (int i=0; i < v.size(); i++) {
        os << v[i] << endl;
    }
    return os;
}

template<typename T>
void remove(vector<T> & v, const T & elem) {
    auto it = find(v.begin(), v.end(), elem); 
    if (it != v.end()) { 
        v.erase(it); 
    }
}

/**
 * @brief Greedy approximated solution to the Travelling Salesman Problem 
 * 
 * @param n number of cities to visit
 * @param home_ind index of the home (origin) city 
 * @param v array of cities to visit
 * @param path current path
*/
void TSP_greedy_v1(int n, int home_ind, const City v[], vector<int> & path){

    // Not visited cities
    vector<int> not_visited(n);

    // Initializes with all cities
    for(int i=0; i < n; i++) {
        not_visited[i] = i;
    }
    // Start with home city
    int current = home_ind;

    while (not_visited.size() > 0) {
        path.push_back(current);
        remove(not_visited,current);

        // Calculate the closest neighbour
        ld min_dist = INF, dist;
        int next;
        for (int city : not_visited) {
            dist = v[current]-v[city];
            if (dist < min_dist) {
                min_dist = dist;
                next = city;
            }
        }

        // Next city
        current = next;
    }
    path.push_back(home_ind);
}

int main(int argc, char** argv) {
    // Faster I/O
    ios::sync_with_stdio(false);

    // Check given paremeters
    if (argc < 2) {
        cout << "Uso: ./greedy <input_file>" << endl;
        return 1;
    }

    // INPUT
    ifstream fin(argv[1],ios::in);

    int n;
    fin >> n;
    City v[n];
    for(int i=0; i<n; ++i)
        fin >> v[i];

    int origin_index = 0; // Origin city index

    // Answer
    vector<int> ans;
    ans.reserve(n);

    // TSP
    clock_t t_before = clock();
    TSP_greedy_v1(n,0,v,ans);
    clock_t t_after = clock();

    // OUTPUT
    #ifdef TSP
    printCycle(ans,v[0],v);
    #endif

    #ifdef COST
    cout << n << " " << cycleDistance(ans,v) << endl;
    #endif

    #ifdef TIME
    cout << n << " " << ((double)(t_after - t_before)/ CLOCKS_PER_SEC) << endl;
    #endif
}