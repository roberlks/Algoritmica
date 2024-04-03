#include <bits/stdc++.h>
#include "City.h"
using namespace std;

typedef long double ld;

/**
 * @brief Calculates the distance of the given cycle (cycle)
 * @param cycle the cycle to calculate the distance from
 * @param v the cities
 * @return the distance between all the consecutive cities of the cycle
*/
ld cycleDistance(vector<int> cycle, City v[])
{
    if(cycle.size() < 2) return 0;
    ld total = 0;
    for (int i = 0; i < (int)cycle.size()-1; i++)
    {
        total += (v[cycle[i+1]] - v[cycle[i]]);
    }
    total += (v[cycle[0]] - v[cycle[cycle.size() - 1]]);

    return total;
}

vector<int> bruteFoce(int n, City v[]){
    vector<int> cycle(n),ans;
    for(int i=0; i<n; ++i) cycle[i] = i;

    ld best_dist, cur_dist;
    best_dist = cycleDistance(cycle,v);
    ans = cycle;
    do{
        cur_dist = cycleDistance(cycle,v);
        if(cur_dist < best_dist){
            best_dist = cur_dist;
            ans = cycle;
        }
    }while (next_permutation(cycle.begin(),cycle.end()));

    return ans;
}

int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    City v[n];
    for(int i=0; i<n; ++i)
        cin >> v[i];

    // TSP
    vector<int> ans = bruteFoce(n,v);

    // OUTPUT
    cout << cycleDistance(ans,v) << endl;
    for(int i : ans){
        cout << i << " ";
    }
    cout << endl;
}