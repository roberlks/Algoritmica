#include <bits/stdc++.h>
#include "City.h"
using namespace std;

const int UMBRAL = 2;

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

    if(fin - ini <= UMBRAL){
        bool visited[fin-ini] = {false};
        TSP_brute_path(fin-ini, v[0], v, visited, path);
        return;
    }

    //Divide
    vector<int> path1,path2;
    int mid = (fin+ini)/2;
    dyv(ini,mid, v, path1);
    dyv(mid,fin, v, path2);

    // Adjust vectors from brute force algorithm

    for (int i=0; i < mid-ini+1; ++i) {
        path1[i] += ini;
    }

    for (int i=0; i < fin-mid+1; ++i) {
        path2[i] += mid;
    }

    // Pop last zero
    path1.pop_back();
    path2.pop_back();

    // cout << "Path1: " << path1 << endl;
    // cout << "Path2: " << path2 << endl;

    //Fusion

    int r_nearest_city = mid;
    int l_nearest_city = mid-1;

    int x;
    // cout << "ini = " << ini << endl;
    // cout << "fin = " << fin << endl;
    // cout << "mid = " << mid << endl;
    // cout << "Searching " << l_nearest_city << " in path1[" << path1.size() << "]" << endl;
    for (int i=0; i < mid-ini; ++i) {
        // cout << "Accessing element " << i << endl;
        if (path1[i] == l_nearest_city) {
            x = i;
            break;
        }
    }

    int z;
    // cout << "Searching in path2[" << path2.size() << "]" << endl;


    // ? Se podría cambiar z por el elemento más cercano a x en
    // ? en lado derecho
    // ? Creo que no afecta a la eficiencia
    // ? Probado: suelen salir peores resultados
    for (int i=0; i < fin-mid; ++i) {
        // cout << "Accessing element " << i << endl;

        if (path2[i] == r_nearest_city) {
            
            z = i;
            break;
        }
    }

    //? The other method
    // ld min_dist = INF;
    // for (int i=0; i < fin-mid; ++i) {
    //     if(v[path1[x]].dist(v[path2[i]]) <= min_dist) {
    //         z = i;
    //     }
    // }

    // Calculate y and left orientation
    int inc_x = 1;
    int y1 = (x+1)%(mid-ini), y2 = (x+mid-ini-1)%(mid-ini), y = y1;
    if (path1[y1] < path1[y2]) {
        inc_x = -1;
        y = y2;
    }

    // cout << "y1 = " << y1 << endl;
    // cout << "y2 = " << y2 << endl;
    // cout << "inc_x = " << inc_x << endl;

    int inc_z = 1;
    
    // Calculate t and orientation
    int t1 = (z+1)%(fin-mid), t2 = (z+fin-mid-1)%(fin-mid), t = t1;
    if (path2[t2] < path2[t1]) {
        inc_z = -1;
        t = t2;
    }

    // cout << "x " << x << " --> " << path1[x] << endl;
    // cout << "y " << y << " --> " << path1[y] << endl;
    // cout << "z " << z << " --> " << path2[z] << endl;
    // cout << "t " << t << " --> " << path2[t] << endl;


    ld xz = v[path1[x]].dist(v[path2[z]]);
    ld xt = v[path1[x]].dist(v[path2[t]]);
    ld yz = v[path1[y]].dist(v[path2[z]]);
    ld yt = v[path1[y]].dist(v[path2[t]]);

    // cout << xt << " + " << yz << " < " << xz << " + " << yt << " ? " << boolalpha << (xt + yz < xz + yt) << endl;

    bool link_xz = xt + yz > xz + yt;

    // cout << "Link x and z ? " << boolalpha << link_xz << endl;

    // cout << "Pushing from path1[" << path1.size() << "]" << endl;

    // cout << "Pushing from " << y << " to " << x << " (jump: " << inc_x << ")" << endl;
    
    // Push path1 to path
    path.reserve(fin-ini);
    for (int i=y; i != x; i = (i+mid-ini+inc_x)%(mid-ini)) {
        //cout << "Pushing element path[" << i << "] = " << path1[i] << endl;
        path.push_back(path1[i]);
    }
    path.push_back(path1[x]);
    // cout << "Pushing from path2[" << path2.size() << "]" << endl;

    int start_z = link_xz ? z : t;

    // cout << "starts z ? " << boolalpha << (start_z == z) << endl;
    int finish_z = start_z == z ? t : z;

    // cout << "inc_z = " << inc_z << endl;

    inc_z = start_z == z ? -inc_z : inc_z;

    // cout << "inc_z = " << inc_z << endl;

    // cout << "Pushing from " << start_z << " to " << finish_z << " (jump: " << inc_z << ")" << endl;

    // Push path2 to path
    for (int i=start_z; i != finish_z; i = (i+fin-mid+inc_z)%(fin-mid)) {
        // cout << "Pushing element path[" << i << "] = " << path2[i] << endl;
        path.push_back(path2[i]);
    }
    path.push_back(path2[finish_z]);

    // cout << path << endl;

    // Adjust like brute_force format
    for (int i=0; i < path.size(); ++i) {
        path[i] -= ini;
    }
    path.push_back(0);

    // Know the cycle, salesman home must be found
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
    // Sort by x axis
    sort(v,v+n,[&](const City & a, const City & b){
        if (a.x < b.x) {
            return true;
        }
        else if (a.x == b.x) {
            return a.y < b.y;
        }
        return false;
    });

    for(City c : v){
        // cout << c << endl;
    }

    vector<int> path;

    dyv(0,n,v,path);

    path.pop_back();
    
    int pos_ini = 0;
    ld long_path = 0.0;

    // Find salesman home and length of the path
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

    cout << "Path length: " << long_path << endl;

    return 0;
}