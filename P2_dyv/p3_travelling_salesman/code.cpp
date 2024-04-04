#include <bits/stdc++.h>
#include "City.h"
using namespace std;

const int UMBRAL = 3;

ostream & operator<<(ostream & os, const vector<int> & v) {
    for (int i=0; i < v.size(); ++i) {
        os << v[i] << " ";
    }
    return os;
}

void closestNeighbour(const list<City> & path1, const list<City> & path2){
    double min_dist = 0;
    for(auto it1 = path1.begin(); it1 != path1.end(); ++it1){
        for(auto it2 = path2.begin(); it2 != path2.end(); ++it2){
            
        }
    }
}

/**
 * @brief Brute force solution to the Travelling Salesman Problem (path).
 * @param n number of cities to visit
 * @param p previous city
 * @param v array of cities to visit
 * @param visited whether city i has been visited or not
*/
ld TSP_brute_path(int n,City p,City v[],bool visited[], vector<int> & path){
    ld sol = 1e18; // INF
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



// [ini,fin)

void dyv(int ini, int fin, City v[], vector<int> & path){
    // Base case 
    // cout << ini << " " << fin << endl;

    if(fin - ini <= UMBRAL){
        // cout << "base case\n";
        bool visited[fin-ini] = {false};
        TSP_brute_path(fin-ini, v[0], v, visited, path);
        //path.push_back(ini);
        return;
    }

    //sort(v,v+fin-ini);

    //Divide
    vector<int> path1,path2;

    int mid = (fin+ini)/2;
    
    dyv(ini,mid, v, path1);
    dyv(mid,fin, v, path2);

    for (int i=0; i < fin-mid+1; ++i) {
        path2[i] += mid;
    }

    path1.pop_back();
    path2.pop_back();

    // cout << "Path1: " << path1 << endl;
    // cout << "Path2: " << path2 << endl;

    // cout << "path1" <<endl;
    // for(int i : path1){
    //     cout << i << endl;
    // }
    // cout << "path2" <<endl;
    // for(int i : path2){
    //     cout << i << endl;
    // }
    // return ;
    //Fusion

    int r_nearest_city = mid;
    int l_nearest_city = mid-1;

    bool found_first = false, found_second = false;
    int x;
    // cout << "Searching in path1[" << path1.size() << "]" << endl;
    for (int i=0; i < mid-ini; ++i) {
        // cout << "Accessing element " << i << endl;
        if (path1[i] == l_nearest_city) {
            x = i;
            break;
            // found_first = true;
        }
        // else if (path1[i] == l_nearest_cities.second) {
        //     y = i;
        //     found_second = true;
        // }
        // if (found_first && found_second) break;
    }

    found_first = found_second = false;
    int z;
    // cout << "Searching in path2[" << path2.size() << "]" << endl;

    for (int i=0; i < fin-mid; ++i) {
        // cout << "Accessing element " << i << endl;

        if (path2[i] == r_nearest_city) {
            
            z = i;
            break;
            // found_first = true;
        }
        // else if (path2[i] == r_nearest_cities.second) {
        //     t = i;
        //     found_second = true;
        // }
        // if(found_first && found_second) break;
    }
    int inc_x = -1;
    int y1 = (x+1)%(mid-ini), y2 = (x+mid-ini-1)%(mid-ini), y = y1;
    if (v[y1].x < v[y2].x) {
        inc_x = 1;
        y = y2;
    }

    int inc_z = -1;
    int t1 = (z+1)%(fin-mid), t2 = (z+fin-mid-1)%(fin-mid), t = t1;
    if (v[t1].x < v[t2].x) {
        inc_z;
        t = t2;
    }

    bool link_xz = true;
    int xz = v[x].dist(v[z]);
    int xt = v[x].dist(v[t]);
    int yz = v[y].dist(v[z]);
    int yt = v[y].dist(v[t]);

    if (xt + yz < xz + yt) {
        link_xz = false;
    }

    // cout << "x " << x << endl;
    // cout << "y " << y << endl;
    // cout << "z " << z << endl;
    // cout << "t " << t << endl;

    // cout << "Pushing from path1[" << path1.size() << "]" << endl;

    int start_x  = inc_x == 1 ? y : x;
    int finish_x = inc_x == 1 ? x : y;

    // cout << "Pushing from " << start_x << " to " << finish_x << " (jump: " << inc_x << ")" << endl;
    for (int i=start_x; i != finish_x; i = (i+mid-ini+inc_x)%(mid-ini)) {
        // cout << "Pushing element path[" << i << "] = " << path1[i] << endl;
        path.push_back(path1[i]);
    }
    path.push_back(path1[finish_x]);
    // cout << "Pushing from path2[" << path1.size() << "]" << endl;

    int start_z;
    if(finish_x == x) {
        start_z = link_xz ? z : t;
    }
    else { // finish_x == y
        start_z = link_xz ? t : z;
    }
    int finish_z = start_z == z ? t : z;
    for (int i=start_z; i != finish_z; i = (i+fin-mid+inc_z)%(fin-mid)) {
        // cout << "Pushing element path[" << i << "] = " << path2[i] << endl;
        path.push_back(path2[i]);
    }
    path.push_back(path2[finish_z]);

    cout << path << endl;
}

int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    City v[n];
    City home = v[0];
    for(int i=0; i<n; ++i)
        cin >> v[i];

    // Sort by x axis
    sort(v,v+n,[&](const City & a, const City & b){
        return a.x < b.x;
    });

    // for(City c : v){
    //     cout << c << endl;
    // }

    vector<int> path;

    dyv(0,n,v,path);
    
    int pos_ini = 0;
    ld long_path = 0.0;
    for(int i=0; i < n; i++) {
        if (v[path[i]] == home)
            pos_ini = i;
        if (i < n-1) {
            long_path += v[path[i]].dist(v[path[i+1]]);
        }
    }
    long_path += v[path[n-1]].dist(v[path[0]]);

    for(int i=pos_ini; i<n; i++){ // Print the order
        cout << v[path[i]] << " ";
    }

    for(int i=0; i<pos_ini; i++){ // Print the order
        cout << v[path[i]] << " ";
    }
    cout << v[path[pos_ini]] << endl; // Cycle

    cout << "Long path: " << long_path << endl;

    return 0;
}