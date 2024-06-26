#include <bits/stdc++.h>
#include "City.h"
using namespace std;

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
void TSP_greedy_v1(int n, int home_ind, const City v[], vector<City> & path){

    vector<int> not_visited(n);

    for(int i=0; i < n; i++) {
        not_visited[i] = i;
    }

    int current = home_ind;
    while (not_visited.size() > 0) {
        path.push_back(v[current]);
        remove(not_visited,current);
        ld min_dist = INF, dist;
        int next;
        for (int city : not_visited) {
            dist = v[current]-v[city];
            if (dist < min_dist) {
                min_dist = dist;
                next = city;
            }
        }
        current = next;
    }
    path.push_back(v[home_ind]);
}

int main(int argc, char** argv) {
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

 

    // INPUT

    int n;
    cin >> n;
    City v[n];
    for(int i=0; i<n; ++i)
        cin >> v[i];

    // Answer
    vector<City> ans;
    ans.reserve(n);

    // TSP
    TSP_greedy_v1(n,0,v,ans);

    // OUTPUT
    cout << ans << endl;
}
