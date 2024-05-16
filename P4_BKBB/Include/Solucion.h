// TODO
#include <iostream>
#include <vector>
#include "City.h"

using namespace std;

// operator << for vector<T>
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
private:
    vector<int> best_ans;
    double cost; 

    vector<City> cities;
public:
    TSP_solution(const vector<City> & cities = {}) : cities(cities), cost(0), best_ans({}) {}
    
    // Inline
    double getCost() const {
        return cost;
    }

    vector<int>& getBestAns(){
        return best_ans;
    }

    vector<City>& getCities(){
        return cities;
    }

    const vector<int>& getBestAns() const{
        return best_ans;
    }

    const vector<City>& getCities() const{
        return cities;
    }

    /*double f_cota(vector<bool>& visited, int node,int i){
        switch (i)
        {
        case 1:
            //f_cota1(visited,node);
            break;
        
        default:
            break;
        }
    }*/

    vector<int> & solve(double (TSP_solution::*f_cota)(vector<bool>& visited, int node))
    {   
        // Se limpia
        best_ans.clear();
        cost = 0;

        if (cities.empty()) return best_ans;
        
        // Se empieza desde el origen para pasar de n! a (n-1)!
        vector<int> track;
        track.push_back(0);                 
        vector<bool> visited(cities.size(), false);
        visited[0] = true;

        // Estable la primera cota 
        TSP_greedy_v1(cities.size(), 0, best_ans);
        cost = cycleDistance(best_ans, cities);

        algorithm(f_cota);
        return best_ans; 
    }

    /**
     * @brief Algorithm chosen for solving TSP (backtraking o branch and bound)
    */
    virtual void algorithm(double (TSP_solution::*f_cota)(vector<bool>& visited, int node));
    /*{
         // Se empieza desde el origen para pasar de n! a (n-1)!
        vector<int> track;
        track.push_back(0);                 
        vector<bool> visited(cities.size(), false);
        visited[0] = true;
        backtracking(track, visited,f_cota);
        branch_bound();
    }*/

    bool podar(vector<int>& track, vector<bool>& visited, int node, 
        double (TSP_solution::*f_cota)(vector<bool>& visited, int node))
    {
        if(track.size() < 2) return 0;

        //? Llamar cycleDistance
        ld cota_inf = 0;
        for (int i = 0; i < (int)track.size()-1; i++)
        {
            cota_inf += (cities[track[i+1]] - cities[track[i]]);
        }
        
        cota_inf += (cities[node] - cities[track.back()]);

        for (int i=0; i < (int)cities.size(); ++i)
        {
            if ((node != i) && !visited[i]) {
                cota_inf += ((*this).*(f_cota))(visited, i);
            }
        }
        
        // Coste para volver desde una ciudad
        cota_inf += ((*this).*(f_cota))(visited,0);
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
     * @brief Prints the solution cycle (index) starting and ending at origin
    */
    void printCycle(){

        int origin = 0;
        
        std::cout << best_ans << " ";
        std::cout << origin << std::endl;
    }

    /**
     * @brief Greedy approximated solution to the Travelling Salesman Problem 
     * 
     * @param n number of cities to visit
     * @param home_ind index of the home (origin) city 
     * @param v array of cities to visit
     * @param path current path
    */
    void TSP_greedy_v1(int n, int home_ind, vector<int> & path){

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
                dist = cities[current]-cities[city];
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

//? Maybe poner las cotas que valen para ambas aquí
//? Maybe hacer .h y .cpp por separado