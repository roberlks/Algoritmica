#include <bits/stdc++.h>
#include "City.h"
using namespace std;

const int UMBRAL = 2;

vector<int> swapEdges(int e1, int e2,vector<int> & cycle1,vector<int> & cycle2, const City v[]){
    int n1 = cycle1.size();
    int n2 = cycle2.size();
    vector<int> cycle;
    cycle.reserve(n1+n2);
    for(int i=e2+1; i<n2; ++i){
        cycle.push_back(cycle2[i]);
    }
    for(int i=0; i<=e2; ++i){
        cycle.push_back(cycle2[i]);
    }
    for(int i=e1+1; i <n1; ++i){
        cycle.push_back(cycle1[i]);
    }
    for(int i=0; i<=e1; ++i){
        cycle.push_back(cycle1[i]);
    }
    return cycle;
}

vector<int> fusion(vector<int> & cycle1,vector<int> & cycle2, const City v[]){
    int n1 = cycle1.size();
    int n2 = cycle2.size();
    ld old_edge1,old_edge2,new_edge1,new_edge2,cur_swap_cost,min_swap_cost = INF;
    int e1,e2;
    for(int c1=0; c1<n1; ++c1){
        old_edge1 = v[cycle1[c1]] - v[cycle1[(c1+1)%n1]]; // c1 y c1+1
        for(int c2=0; c2<n2; ++c2){
            old_edge2 = v[cycle2[c2]] - v[cycle2[(c2+1)%n2]]; // c2 y c2+1
            new_edge1 = v[cycle1[c1]] - v[cycle2[(c2+1)%n2]]; // c1 y c2+2
            new_edge2 = v[cycle1[(c1+1)%n1]] - v[cycle2[c2]]; // c1+1 y c2
            cur_swap_cost = new_edge1 + new_edge2 - old_edge1 - old_edge2;
            if(cur_swap_cost < min_swap_cost){
                min_swap_cost = cur_swap_cost;
                e1 = c1;
                e2 = c2;
            }
        }
    }

    return swapEdges(e1,e2,cycle1,cycle2,v);
}

vector<int> dyv(int ini, int fin, const City v[]){
    // Base case
    if(fin-ini <= UMBRAL){
        vector<int> cycle(fin-ini);
        for(int i=ini; i<fin; ++i){
            cycle[i-ini] = i;
        }
        return cycle;
    }
    // Divide
    // Naive division
    int mid = (ini+fin)/2;
    vector<int> cycle1,cycle2;
    cycle1 = dyv(ini,mid,v);
    cycle2 = dyv(mid,fin,v);

    // Fusion
    return fusion(cycle1,cycle2,v);
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
    vector<int> ans = dyv(0,n,v);

    // OUTPUT
    printCycle(ans,v[0],v);
}