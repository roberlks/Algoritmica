#include <iostream>
#include <bits/stdc++.h>
#include "../../Include/City.h"

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


class TSP_solution
{

    vector<City> cities;

    vector<int> best_ans;
    ld cost; 

    public: 

    TSP_solution(){};

    double getCost() const {
        return cost;
    }

    vector<int> solve(vector<City>& v)
    {   
        // Se limpia
        best_ans.clear();
        cost = 0;

        cities = v;

        if (cities.empty()) return best_ans;

        // Estable la primera cota 
        TSP_greedy_v1(cities.size(), 0, cities, best_ans);
        cost = cycleDistance(best_ans, cities);

        branchAndBound();
        return best_ans; 
    }

    /**
     * @brief Prints the ans calling City::printCycle
    */
    void printAns(){
        printCycle(best_ans,cities[0],cities);
    }

    void branchAndBound()
    {  
        
        priority_queue<Track, vector<Track>,greater<Track>> nodos_vivos;
        
        // Se empieza desde el origen para pasar de n! a (n-1)!
        vector<int> track;           
        vector<bool> visited(cities.size(), false);

        track.push_back(0);  
        visited[0] = true;

        nodos_vivos.emplace(track, visited, -1);

        while (!nodos_vivos.empty())
        {
            Track e_node = nodos_vivos.top();
            nodos_vivos.pop();

            // Funcion de factibilidad (Se compara con la cota)
            if (e_node.aprox_cost >= cost) continue;

            // Caso base
            if (e_node.track.size() == cities.size())
            {   
                ld cost_aux = cycleDistance(e_node.track, cities); // Distancia real
                if (cost_aux < cost) 
                {
                    best_ans = e_node.track;
                    cost = cost_aux;
                }
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

    pair<bool, double> feasible(Track& t, int node)
    {
        
        pair<bool, double>  viable(true, -1);
        if (t.visited[node]) {
            viable.first = false;
        } 
        else{
            ld cota_inf = cota_local(cities, t.track, t.visited, node);
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

    ld cota_local(vector<City>& cities, vector<int>& track, vector<bool>& visited, int node)
    {
        if(track.size() < 2) return 0;

        ld cota_inf = 0;
        for (int i = 0; i < track.size()-1; i++)
        {
            cota_inf += (cities[track[i+1]] - cities[track[i]]);
        }
        
        cota_inf += (cities[node] - cities[track.back()]);

        for (int i=0; i < cities.size(); ++i)
        {
            if ((node != i) && !visited[i]) {
                cota_inf += enter_min_cost(cities, visited, i);
            }
        }
        
        // Coste para volver desde una ciudad
        cota_inf +=enter_min_cost(cities, visited, 0);
        
        return cota_inf;
    }

    /**
     * @brief Calculates the distance of the given cycle (cycle)
     * @param cycle the cycle to calculate the distance from
     * @param v the cities
     * @return the distance between ald the consecutive cities of the cycle
    */
    ld cycleDistance(const std::vector<int> & cycle,const vector<City> v)
    {
        if(cycle.size() < 2) return 0;
        ld total = 0;
        for (int i = 0; i < (int)cycle.size()-1; i++)
        {
            total += (v[cycle[i+1]] - v[cycle[i]]);
        }
        total += (v[cycle[0]] - v[cycle[cycle.size() - 1]]);

        return total;
    }

    private:

    double enter_min_cost(vector<City>& cities, vector<bool>& visited, int node)
    {   
        double min_enter = -1;
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

    /**
     * @brief Greedy approximated solution to the Travelling Salesman Problem 
     * 
     * @param n number of cities to visit
     * @param home_ind index of the home (origin) city 
     * @param v array of cities to visit
     * @param path current path
    */
    void TSP_greedy_v1(int n, int home_ind, vector<City>& v, vector<int> & path){

        // Not visited cities
        vector<int> not_visited(n);

        // Initializes with all cities
        for(int i=0; i < n; i++) {
            not_visited[i] = i;
        }
        // Start with home city
        int current = home_ind;

        while (not_visited.size() > 0) {
            path.push_back(current);
            remove(not_visited,current);

            // Calculate the closest neighbour
            ld min_dist = INF, dist;
            int next;
            for (int city : not_visited) {
                dist = v[current]-v[city];
                if (dist < min_dist) {
                    min_dist = dist;
                    next = city;
                }
            }

            // Next city
            current = next;
        }
        path.push_back(home_ind);
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

    TSP_solution sol;

    // sol.setCotaVersion(version);

    // TSP

    clock_t t_before = clock();
    sol.solve(v);
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