#include <iostream>
#include <bits/stdc++.h>
#include "../../Include/City.h"
#include "../../Include/Solution.h"

using namespace std;

#ifndef TIME 
    #ifndef COST
        #define TSP
    #endif
#endif


// operator << for vector<City>
template <typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    for (int i=0; i < v.size(); i++) {
        os << v[i] << endl;
    }
    return os;
}

template<typename T>
void remove(vector<T> & v, const T & elem) {
    auto it = find(v.begin(), v.end(), elem); 
    if (it != v.end()) { 
        v.erase(it); 
    }
}


struct Track
{
    vector<int> track;
    vector<bool> visited; 
    ld aprox_cost;

    Track(int n=0): visited(n, false), aprox_cost(0){}

    Track(vector<int>& track, vector<bool>& visited, ld cost): track(track), visited(visited), aprox_cost(cost) {}
    bool operator>(Track other) const {
        return this->aprox_cost > other.aprox_cost;
    }
};


class TSP_solution_BB : public TSP_solution
{

    vector<City> cities;
    vector<int> best_ans;
    ld cost; 

    int podas;
    int generated;
    int version;

    public: 

    TSP_solution() : podas(0), generated(0) {};

    TSP_solution(const vector<City> & v) {
        podas = generated = 0;
        cities = v;
        TSP_greedy();
        cost = cycleDistance(best_ans,cities);
    }

    vector<City> getCities() const {
        return cities;
    }

    vector<int> getSol() const {
        return best_ans;
    }

    ld getCost() const {
        return cost;
    }

    int getPodas() const {
        return podas;
    }

    ll getPossibleNodes() const {
        // return n + n*(n-1) + n*(n-1)*(n-2) + ... + n!/2 + n!/1 + n!
        int n=cities.size();
        ll sum = 0;
        for (int k=n; k>1; k--) {
            ll product = 1;
            for (int j=k; j<=n; j++) {
                product *= j;
            }
            sum += product;
        }
        return sum+1;
    }

    int getGeneratedNodes() const {
        return generated;
    }

    void setCotaVersion(int version) {
        this->version = version;
    }

    void solve()
    {   
        if (cities.empty()) return;
        Track e_node(cities.size());
        e_node.visited[0] = true;
        e_node.track.push_back(0);
        branchAndBound(e_node);
    }

    /**
     * @brief Prints the ans calling City::printCycle
    */
    void printAns(){
        printCycle(best_ans,cities[0],cities);
    }

private: 
    void branchAndBound(Track & first_node)
    {  
        
        priority_queue<Track, vector<Track>,greater<Track>> nodos_vivos;
        
        // Se empieza desde el origen para pasar de n! a (n-1)!
        nodos_vivos.push(first_node);

        while (!nodos_vivos.empty())
        {
            Track e_node = nodos_vivos.top();
            nodos_vivos.pop();

            // Funcion de factibilidad (Se compara con la cota)
            if (e_node.aprox_cost >= cost) continue;

            // Caso base
            if (e_node.track.size() == cities.size())
            {   
                processSolution(e_node.track);
                continue; 
            }


            // Genero todos los hijos
            for (int i = 1; i < cities.size(); ++i)
            {   
                pair<bool, double> viable = feasible(e_node, i);
                if (viable.first == false) continue;

                //cout << "viable < " << viable.first << ", " <<  viable.second <<">";
                Track aux = e_node;
                aux.track.push_back(i);
                aux.aprox_cost = viable.second;
                aux.visited[i] = true; 

                //cout << aux.aprox_cost << "\n";
                nodos_vivos.push(aux);
            }

        }

    }

    pair<bool, ld> feasible(Track & e_node, int node)
    {
        
        pair<bool, ld>  viable(true, -1);
        if (e_node.visited[node]) {
            viable.first = false;
        } 
        else{
            ld cota_inf = f_cota(e_node, node);
            viable.second = cota_inf;

            if (cota_inf >= cost) {
                viable.first = false;
            }
            else {
                viable.first = true;
            }
        } 
        return viable;
    }

    ld f_cota(Track & e_node, int node) {
        ld cota_inf;
        switch(version) {
            case(1) :
                cota_inf = f_cota1(e_node,node);
                break;
            case(2) :
                cota_inf = f_cota2(e_node,node);
                break;
            case(3) :
                cota_inf = f_cota3(e_node,node);
                break;
            default :
                cerr << "Invalid f_cota version (1,2 or 3)" << endl;
                exit(1);
                break;             
        }
        return cota_inf;
    }

    ld f_cota1(Track & e_node,int node) {
        ld cota_inf = trackDistance(e_node.track) + minPossibleDistance(e_node.visited,node);

        cota_inf += (cities[node] - cities[e_node.track.back()]);

        return cota_inf;
    }

    ld f_cota2(Track & e_node, int node) {
        //TODO
        return 1;
    }

    ld f_cota3(Track & e_node, int node) {
        //TODO
        return 1;
    }

    ld trackDistance(const vector<int> & track) {
        ld dist = 0;

        for (int i = 0; i < track.size()-1; i++)
        {
            dist += (cities[track[i+1]] - cities[track[i]]);
        }
        
        return dist;
    }

    ld minPossibleDistance(const vector<bool> & visited, int node) {
        
        ld dist = 0;

        for (int i=0; i < cities.size(); ++i)
        {
            if ((node != i) && !visited[i]) {
                dist += enter_min_cost(cities, visited, i);
            }
        }
        
        // Coste para volver desde una ciudad
        dist += enter_min_cost(cities, visited, 0);

        return dist;
    }

    ld enter_min_cost(const vector<City>& cities, const vector<bool>& visited, int node)
    {   
        ld min_enter = -1;
        for(int i=0; i < visited.size(); ++i)
        {
            if (i == node) continue;
            if (!visited[i] && ((min_enter == -1) || cities[node].dist(cities[i]) < min_enter))
            {
                min_enter = cities[node].dist(cities[i]);
            }
        }
        return min_enter;
    }

    void processSolution(const vector<int> & track) {

        ld cost_aux = cycleDistance(track,cities);
        if (cost_aux < cost) {
            best_ans = track;
            cost = cost_aux;
        }
    }

    /**
     * @brief Greedy approximated solution to the Travelling Salesman Problem 
     * 
     * @param n number of cities to visit
     * @param home_ind index of the home (origin) city 
     * @param v array of cities to visit
     * @param path current path
    */
    void TSP_greedy(){

        int n = cities.size();
        // Not visited cities
        vector<int> not_visited(n);

        // Initializes with all cities
        for(int i=0; i < n; i++) {
            not_visited[i] = i;
        }
        // Start with home city
        int current = 0;

        while (not_visited.size() > 0) {
            best_ans.push_back(current);
            remove(not_visited,current);

            // Calculate the closest neighbour
            ld min_dist = INF, dist;
            int next;
            for (int city : not_visited) {
                dist = cities[current]-cities[city];
                if (dist < min_dist) {
                    min_dist = dist;
                    next = city;
                }
            }

            // Next city
            current = next;
        }
    }

    
};

int main(int argc, char** argv){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    ifstream fin(argv[1],ios::in);
    int version;
    if (argc == 3)
        version = atoi(argv[2]);
    else
        version = 1;

    // INPUT
    int n;
    fin >> n;
    vector<City> v;
    v.reserve(n);

    for(int i=0; i<n; ++i) {
        City aux;
        fin >> aux;

        v.push_back(aux);
    }

    TSP_solution_BB sol(v);

    sol.setCotaVersion(version);

    // TSP

    clock_t t_before = clock();
    sol.solve();
    clock_t t_after = clock();

    // cout << "nodes: " << sol.getGeneratedNodes() << " / " << sol.getPossibleNodes() << endl;
    // cout << "podas: " << sol.getPodas() << endl;
    // cout << sol.getSol() << endl;
    // OUTPUT
    #ifdef TSP
    sol.printAns();
    // cout << n << " " << sol.getCost() << endl;
    #endif

    #ifdef COST
    cout << n << " " << sol.getCost() << endl;
    #endif

    #ifdef TIME
    cout << n << " " << ((ld)(t_after - t_before)/ CLOCKS_PER_SEC) << endl;
    #endif

    return 0;
}