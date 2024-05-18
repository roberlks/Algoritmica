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

TSP_solution::TSP_solution() : podas(0), generated(0), cost(INF) {}

TSP_solution::TSP_solution(const vector<City>& v) {
    podas = generated = 0;
    cities = v;
    TSP_greedy();
    cost = cycleDistance(best_ans, cities);
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
    ld cota_inf;
    switch (version) {
        case 1:
            cota_inf = f_cota1(e_node, node);
            break;
        case 2:
            cota_inf = f_cota2(e_node, node);
            break;
        case 3:
            cota_inf = f_cota3(e_node, node);
            break;
        default:
            cerr << "Invalid f_cota version (1, 2, or 3)" << endl;
            exit(1);
            break;
    }
    return cota_inf;
}

ld TSP_solution::f_cota1(Track& e_node, int node) {
    ld cota_inf = trackDistance(e_node.track) + sumMinEnter(e_node.visited, node);
    cota_inf += (cities[node] - cities[e_node.track.back()]);
    return cota_inf;
}

ld TSP_solution::f_cota2(Track& e_node, int node) {
    return 1; // TODO: Implement f_cota2
}

ld TSP_solution::f_cota3(Track& e_node, int node) {

    ld cota_inf = (enter_min_cost(e_node.visited,e_node.track[0]) +
        enter_min_cost(e_node.visited,e_node.track.back())) / 2;
    
    cota_inf += (sumMinEnter(e_node.visited,node)) / 2;
    return cota_inf; // TODO: Implement f_cota3
}

ld TSP_solution::trackDistance(const vector<int>& track) {
    ld dist = 0;
    for (int i = 0; i < track.size() - 1; i++) {
        dist += (cities[track[i + 1]] - cities[track[i]]);
    }
    return dist;
}

ld TSP_solution::sumMinEnter(const vector<bool>& visited, int node) {
    ld dist = 0;
    for (int i = 0; i < cities.size(); ++i) {
        if ((node != i) && !visited[i]) {
            dist += enter_min_cost(visited, i);
        }
    }
    dist += enter_min_cost(visited, 0);
    return dist;
}

ld TSP_solution::sumMinExit(const vector<bool>& visited, int node) {
    ld dist = 0;
    for (int i = 0; i < cities.size(); ++i) {
        if ((node != i) && !visited[i]) {
            dist += exit_min_cost(visited, i);
        }
    }
    dist += exit_min_cost(visited, 0);
    return dist;
}

// ld TSP_solution::sumMinEnterExit(const vector<bool>& visited, int node) {
//     ld dist = 0;

//     for (int i = 0; i < cities.size(); ++i) {
//         if ((node != i) && !visited[i]) {
//             dist += exit_min_cost(visited, i);
//         }
//     }
//     dist += exit_min_cost(visited, 0);
//     return dist;
// }

ld TSP_solution::enter_min_cost(const vector<bool>& visited, int node) {
    return *(orderedEdges(visited,node).begin());
}

ld TSP_solution::exit_min_cost(const vector<bool>& visited, int node) {
    return *(++orderedEdges(visited,node).begin());
}

set<ld> TSP_solution::orderedEdges(const vector<bool> & visited, int node) {
    set<ld> edges;
    for (int i=0; i < visited.size(); ++i) {
        if (i==node) continue;
        if (!visited[i]) {
            edges.insert(cities[node] - cities[i]);
        }
    }
    return edges;
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