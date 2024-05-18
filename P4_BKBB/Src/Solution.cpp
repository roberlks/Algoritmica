#include "../Include/City.h"
#include "../Include/Solution.h"

#include <algorithm>
#include <queue>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << endl;
    }
    return os;
}

template<typename T>
void remove(vector<T>& v, const T& elem) {
    auto it = find(v.begin(),v.end(),elem);
    if (it != v.end()) {
        v.erase(it);
    }
}

TSP_solution::TSP_solution() : podas(0), generated(0), cost(INF), min_e(0) {}

TSP_solution::TSP_solution(const vector<City>& v) {
    podas = generated = 0;
    cities = v;
    TSP_greedy();
    cost = cycleDistance(best_ans, cities);
    min_e = min_edge();
}

vector<City> TSP_solution::getCities() const {
    return cities;
}

vector<int> TSP_solution::getSol() const {
    return best_ans;
}

ld TSP_solution::getCost() const {
    return cost;
}

int TSP_solution::getPodas() const {
    return podas;
}

ll TSP_solution::getPossibleNodes() const {
    int n = cities.size();
    ll sum = 0;
    for (int k = n; k > 1; k--) {
        ll product = 1;
        for (int j = k; j <= n; j++) {
            product *= j;
        }
        sum += product;
    }
    return sum + 1;
}

int TSP_solution::getGeneratedNodes() const {
    return generated;
}

void TSP_solution::setCotaVersion(int version) {
    this->version = version;
}

void TSP_solution::solve() {
    if (cities.empty()) return;
    Track e_node(cities.size());
    e_node.visited[0] = true;
    e_node.track.push_back(0);
    algorithm(e_node);
}

void TSP_solution::printAns() {
    printCycle(best_ans, cities[0], cities);
}

pair<bool,ld> TSP_solution::feasible(Track & e_node, int node)
    {
        if(e_node.track.size() < 2) return {true,0};

        ld cota_inf = f_cota(e_node, node);

        return {(cota_inf < cost),cota_inf};
    }

ld TSP_solution::f_cota(Track& e_node, int node) {
    ld cota_inf = e_node.current_cost;
    cota_inf += (cities[node] - cities[e_node.track.back()]);
    switch (version) {
        case 1:
            cota_inf += f_cota1(e_node, node);
            break;
        case 2:
            cota_inf += f_cota2(e_node, node);
            break;
        case 3:
            cota_inf += f_cota3(e_node, node);
            break;
        default:
            cerr << "Invalid f_cota version (1, 2, or 3)" << endl;
            exit(1);
            break;
    }
    return cota_inf;
}

ld TSP_solution::f_cota1(Track& e_node, int node) {
    int num_not_visited = cities.size() - e_node.track.size();
    return num_not_visited * min_e;
}

ld TSP_solution::f_cota4(Track& e_node, int node) {
    int num_not_visited = cities.size() - e_node.track.size();
    return num_not_visited * min_edge(e_node);
}

ld TSP_solution::f_cota2(Track& e_node, int node) {
    return sum_min_enter(e_node.visited,node);
}

ld TSP_solution::f_cota3(Track& e_node, int node) {
    return 1; // TODO: Implement f_cota3
}

ld TSP_solution::trackDistance(const vector<int>& track) {
    ld dist = 0;
    for (int i = 0; i < track.size() - 1; i++) {
        dist += (cities[track[i + 1]] - cities[track[i]]);
    }
    return dist;
}

ld TSP_solution::min_edge() {
    if(cities.size() < 2) return 0;
    ld min_e = cities[0] - cities[1];
    for(int i = 0; i < (int)cities.size(); ++i){
        for(int j = i+1; j < (int)cities.size(); ++j){
            min_e = min(min_e,cities[i] - cities[j]);
        }
    }
    return min_e;
}

ld TSP_solution::min_edge(const Track& e_node){
    if(cities.size() < 2) return 0;
    if(e_node.track.empty()) return min_e;
    ld cur_min_e = cities[0] - cities[e_node.track.back()];
    for(int i = 0; i < (int)cities.size(); ++i){
        if(e_node.visited[i]) continue;
        cur_min_e = min(cur_min_e, cities[0] - cities[i]);
        cur_min_e = min(cur_min_e, cities[e_node.track.back()] - cities[i]);
        for(int j = i+1; j < (int)cities.size(); ++j){
            if(!e_node.visited[j])
                cur_min_e = min(min_e,cities[i] - cities[j]);
        }
    }
    return cur_min_e;
}

ld TSP_solution::sum_min_enter(const vector<bool> & visited, int node) {
    ld dist = 0;
    for (int i = 0; i < cities.size(); ++i) {
        if ((node != i) && !visited[i]) {
            dist += enter_min_cost(cities, visited, i);
        }
    }
    dist += enter_min_cost(cities, visited, 0);
    return dist;
}

ld TSP_solution::enter_min_cost(const vector<City>& cities, const vector<bool>& visited, int node) {
    ld min_enter = -1;
    for (int i = 0; i < visited.size(); ++i) {
        if (i == node) continue;
        if (!visited[i] && ((min_enter == -1) || cities[node].dist(cities[i]) < min_enter)) {
            min_enter = cities[node].dist(cities[i]);
        }
    }
    return min_enter;
}

void TSP_solution::processSolution(const vector<int>& track) {
    ld cost_aux = cycleDistance(track, cities);
    if (cost_aux < cost) {
        best_ans = track;
        cost = cost_aux;
    }
}

void TSP_solution::TSP_greedy() {
    int n = cities.size();
    vector<int> not_visited(n);
    for (int i = 0; i < n; i++) {
        not_visited[i] = i;
    }
    int current = 0;

    while (not_visited.size() > 0) {
        best_ans.push_back(current);
        remove(not_visited, current);

        ld min_dist = INF, dist;
        int next;
        for (int city : not_visited) {
            dist = cities[current] - cities[city];
            if (dist < min_dist) {
                min_dist = dist;
                next = city;
            }
        }
        current = next;
    }
}