#include <bits/stdc++.h>
#include "City.h"
using namespace std;

/**
 * @brief Brute force solution to the Travelling Salesman Problem (only value).
 * @param n number of cities to visit
 * @param cnt number of visited cities
 * @param prev index of the previous city
 * @param home_ind index of the home (origin) city 
 * @param v array of cities to visit
 * @param visited whether city i has been visited or not
*/
void TSP_branch_bound(int n,int prev,int home_ind, int cnt,const City v[],bool visited[], ld dist, ld & best_dist, vector<int> cur_cycle, vector<int> &best_cycle){
    if(cnt == n-1){ // Base case
        ld new_dist = dist + v[prev].dist(v[home_ind]);
        if(new_dist < best_dist){
            best_dist = new_dist;
            best_cycle = cur_cycle;
        }
        return;
    }

    for(int i=0; i<n; ++i){
        if(!visited[i]){
            visited[i] = true;
            ld new_dist = dist + v[i].dist(v[prev]);
            if(new_dist < best_dist){
                cur_cycle.push_back(i);
                TSP_branch_bound(n,i,home_ind,cnt+1,v,visited,new_dist,best_dist,cur_cycle,best_cycle);
                cur_cycle.pop_back();
            }
            visited[i] = false;
        }
    }
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
    City home = v[0];

    sort(v,v+n); // sort by x axis
    int home_ind = 0;
    while(v[home_ind] != home) ++home_ind;
    ld best_dist = INF;
    bool visited[n];
    memset(visited,false,sizeof(visited));
    visited[home_ind] = true;
    vector<int> ans;
    ans.reserve(n);
    ans.push_back(home_ind);
    TSP_branch_bound(n,home_ind,home_ind,0,v,visited,0,best_dist,ans,ans);
    //printCycle(ans);
    printCycle(ans,home,v);
    cout << cycleDistance(ans,v) << endl;
}