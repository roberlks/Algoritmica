#include <bits/stdc++.h>
#include "City.h"
using namespace std;

/**
 * @brief Brute force solution to the Travelling Salesman Problem (only value).
 * @param n number of cities to visit
 * @param p previous city
 * @param v array of cities to visit
 * @param visited whether city i has been visited or not
*/
ld TSP_brute_value(int n,City p,const City v[],bool visited[]){
    //cout << p << endl;
    ld sol = INF; // INF
    bool all_visited = true;
    for(int i=0; i<n; ++i){
        if(!visited[i]){ // If we haven't visited the city
            all_visited = false;
            visited[i] = true;
            sol = min(sol,TSP_brute_value(n,v[i],v,visited) + p.dist(v[i]));
            visited[i] = false;
        }
    }
    
    if(all_visited) // If we have visit all the cities we return back home
        sol =  p.dist(v[0]);
        
    return sol;
}

/**
 * @brief Brute force solution to the Travelling Salesman Problem (path).
 * @param n number of cities to visit
 * @param p previous city
 * @param v array of cities to visit
 * @param visited whether city i has been visited or not
*/
ld TSP_brute_path(int n,City p,const City v[],bool visited[], vector<int> & path){
    ld sol = INF; // INF
    bool all_visited = true;
    for(int i=0; i<n; ++i){
        if(!visited[i]){ // If we haven't visited the city
            all_visited = false;
            visited[i] = true;
            vector<int> cur_path;
            ld cur_sol = TSP_brute_path(n,v[i],v,visited,cur_path) + p.dist(v[i]);
            if(sol > cur_sol){
                cur_path.push_back(i);
                path = cur_path;
                sol = cur_sol;
            }
            visited[i] = false;
        }
    }
    
    if(all_visited) {// If we have visit all the cities we return back home
        sol =  p.dist(v[0]);
        path = {0};
    }
        
    return sol;
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

    // OUTPUT
    bool visited[n];
    memset(visited,false,sizeof(visited)); // Fill array with false
    visited[0] = true;
    std::cout << TSP_brute_value(n,v[0],v,visited) << endl;
    /*memset(visited,false,sizeof(visited)); // Fill array with false
    visited[0] = true;
    vector<int> path;
    TSP_brute_path(n,v[0],v,visited,path); 
    // No need to reverse the path (its a cycle and dist(p,q) == dist(q,p))
    for(int i=0; i<n; i++){ // Print the order
        cout << path[i] << " ";
    }
    cout << 0 << endl; // Cycle*/
    return 0;
}