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

class TSP_solution
{
    vector<int> best_ans;
    double cost; 

    vector<City> cities;
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
        
        // Se empieza desde el origen para pasar de n! a (n-1)!
        vector<int> track;
        track.push_back(0);                 
        vector<bool> visited(cities.size(), false);
        visited[0] = true;

        // Estable la primera cota 
        TSP_greedy_v1(cities.size(), 0, cities, best_ans);
        cost = cycleDistance(best_ans, cities);

        backtracking(cities, track, visited);
        return best_ans; 
    }

    void backtracking(vector<City>& cities, vector<int>& track, vector<bool>& visited)
    {
        if (track.size() >= cities.size())
        {
            // Keep the best
            double cost_aux = cycleDistance(track, cities);
            if (cost_aux < cost) {
                best_ans = track;
                cost = cost_aux;
            }

            return;
        }
        // La primera ciudad se ignora
        for (int i=1; i < cities.size(); ++i)
        {
            //if (visited[i]) continue;
            if (visited[i] == true || podar(cities, track, visited, i)) continue;

            track.push_back(i);
            visited[i] = true;
            backtracking(cities, track, visited);
            track.pop_back();
            visited[i] = false;
        }
    }

    bool podar(vector<City>& cities, vector<int>& track, vector<bool>& visited, int node)
    {
        if(track.size() < 2) return 0;

        //? Llamar cycleDistance
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

        return (cota_inf >= cost);
    }

    /**
     * @brief Calculates the distance of the given cycle (cycle)
     * @param cycle the cycle to calculate the distance from
     * @param v the cities
     * @return the distance between ald the consecutive cities of the cycle
    */
    ld cycleDistance(const std::vector<int> & cycle,const vector<City> & v)
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

    /**
     * @brief Prints a cycle (index) starting and ending at origin
    */
    void printCycle(){

        int origin = 0;
        int ini = 0;
        
        for(int i=ini; i<(int)best_ans.size(); ++i){
            std::cout << best_ans[i] << " ";
        }
        for(int i=0; i<ini; ++i){
            std::cout << best_ans[i] << " ";
        }
        std::cout << origin << std::endl;
    }

    private:

    double enter_min_cost(vector<City>& cities, vector<bool>& visited, int node)
    {   
        double min_enter = -1;
        for(int i=0; i < cities.size(); ++i)
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

int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    vector<City> v;
    v.reserve(n);

    for(int i=0; i<n; ++i) {
        City aux;
        cin >> aux;

        v.push_back(aux);
    }

    TSP_solution sol;

    // TSP

    clock_t t_before = clock();
    sol.solve(v);
    clock_t t_after = clock();

    // OUTPUT
    #ifdef TSP
    sol.printCycle();
    #endif

    #ifdef COST
    cout << n << " " << sol.getCost() << endl;
    #endif

    #ifdef TIME
    cout << n << " " << ((double)(t_after - t_before)/ CLOCKS_PER_SEC) << endl;
    #endif

    return 0;
}