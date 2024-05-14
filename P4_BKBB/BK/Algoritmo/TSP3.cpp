#include <iostream>
#include <bits/stdc++.h>
#include "../../Include/City.h"

using namespace std;


class TSP_solution
{
    vector<int> best_ans;
    double cost; 

    public: 

    TSP_solution(){};

    vector<int> solve(vector<City>& cities)
    {   
        // Se limpia
        best_ans.clear();
        cost = 0;

        if (cities.empty()) return best_ans;
        
        vector<int> track;
        track.push_back(0);                 // Se empieza desde el origen 
        vector<bool> visited(cities.size(), false);
        visited[0] = true;

        // Se puede llamar a greedy antes para podar 
        cost = -1;
        backtracking(cities, track, visited);
        return best_ans; 
    }

    void backtracking(vector<City>& cities, vector<int>& track, vector<bool>& visited)
    {
        if (track.size() >= cities.size())
        {
            // Keep the best
            double cost_aux = cycleDistance(track, cities);
            if (cost == -1 || cost_aux < cost) {
                best_ans = track;
                cost = cost_aux;
            }

            return;
        }
        // La primera ciudad se ignora
        for (int i=1; i < cities.size(); ++i)
        {
            if (visited[i]) continue;
            //if (visited[i] == true || podar(cities, track, visited, i)) continue;
            
            // Meter funcion podar segun el valor de la cota local

            track.push_back(i);
            visited[i] = true;
            backtracking(cities, track, visited);
            track.pop_back();
            visited[i] = false;
        }
    }

    double enter_min_cost(vector<City>& cities, vector<bool>& visited, int node)
    {   
        double min_enter = -1;
        for(int i=0; i < visited.size(); ++i)
        {
            if (!visited[i] && ((min_enter == -1) || cities[node].dist(cities[i]) < min_enter))
            {
                min_enter = cities[node].dist(cities[i]);
            }
        }
        return min_enter;
    }

    bool podar(vector<City>& cities, vector<int>& track, vector<bool>& visited, int node)
    {
        if(track.size() < 2) return 0;

        ld cota_inf = 0;
        for (int i = 0; i < track.size()-1; i++)
        {
            cota_inf += (cities[track[i+1]] - cities[track[i]]);
        }
        
        cota_inf += cities[node] - cities.back();

        for (int i=0; i < cities.size(); ++i)
        {
            if ((node != i) && !visited[i]) {
                cota_inf += enter_min_cost(cities, visited, i);
            }
        }

        return (cota_inf >= cost);
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

    double getCost() const {
        return cost;
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

    sol.solve(v);

    // OUTPUT
    sol.printCycle(); 

    cout << endl << n << " " << sol.getCost()<< endl;

    return 0;
}