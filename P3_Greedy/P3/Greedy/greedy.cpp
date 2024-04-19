#include <iostream>
#include <vector>
#include <queue>
#include "../../Include/City.h"

using namespace std;

void Dijkstra (const vector<vector<pair<int,ld>>> & g, vector<ld> & dist, 
                vector<int> & path) {
    priority_queue<pair<ld,int>> q;
    q.push({0,0});
    dist[0] = path[0] = 0;
    while(!q.empty()) {
        auto p = q.top();
        q.pop();
        int node = p.second;
        for (auto u : g[node]) {
            int v = u.first;
            int c = u.second;
            if (dist[node] + c < dist[v]) {
                dist[v] = dist[node]+c;
                q.push({-dist[v],v});
            }
        }
    }
}

int main (int argc, char** argv) {  

/*
    Input format:
    3 --> number of cities
    (1,2) (2,0) (0,0) --> cities
    2 --> number of roads
    0 1 (road between (1,2) and (2,0))
    1 2 (road between (2,0) and (0,0))
*/

    int n,m;
    cin >> n;
    vector<City> cities(n);
    vector<vector<pair<int,ld>>> roads(n);

    for (int i=0; i<n; i++) {
        City a;
        cin >> a;
        cities[i] = a;
    }

    cin >> m;
    
    for (int i=0; i<m; i++) {
        int a,b,dist;
        cin >> a >> b;
        dist = a-b;

        roads[a].push_back({b,dist});
        roads[b].push_back({a,dist});
    }
    vector<ld> dist(n,INF);
    for (auto city : roads[0]) {
        dist[city.first] = city.second;
    }

    vector<int> path;
    
    Dijkstra(roads,dist,path);

    return 0;
}