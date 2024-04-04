#include <bits/stdc++.h>
#include "City.h"
using namespace std;

typedef long double ld;

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
    //cout << cycleDistance(ans,v) << endl;
    /*for(int i : ans){
        cout << i << " ";
    }
    cout << endl;*/
    printCycle(ans);
}