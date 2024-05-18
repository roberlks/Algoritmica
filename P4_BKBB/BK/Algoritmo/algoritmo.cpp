#include <bits/stdc++.h>
#include "../../Include/City.h"
#include "../../Include/Solution.h"

using namespace std;

#ifndef TIME 
    #ifndef COST
        #ifndef NODES
            #define TSP
        #endif
    #endif
#endif

//? En lugar de herencia se podría hacer una función a la que se le pase
//? TSP_solution

class BK_solution : public TSP_solution
{

public:
    
    BK_solution(const vector<City> & v) : TSP_solution(v) {};

private:

    void algorithm(Track& e_node) override {
        generated++;
        if (e_node.track.size() == cities.size())
        {
            // Keep the best
            processSolution(e_node.track);
            return;
        }
        // La primera ciudad se ignora
        for (int i=1; i < cities.size(); ++i)
        {
            if (e_node.visited[i]) continue;
            if (!feasible(e_node,i).first) {
                podas++;
                continue;
            }

            e_node.current_cost += (cities[e_node.track.back()] - cities[i]);
            e_node.track.push_back(i);
            e_node.visited[i] = true;
            algorithm(e_node);
            e_node.track.pop_back();
            e_node.visited[i] = false;
            e_node.current_cost -= (cities[e_node.track.back()] - cities[i]);
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

    BK_solution sol(v);

    sol.setCotaVersion(version);

    // TSP

    clock_t t_before = clock();
    sol.solve();
    clock_t t_after = clock();

    // cout << sol.getSol() << endl;
    // OUTPUT
    #ifdef TSP
    sol.printAns();
    // cout << n << " " << sol.getCost() << endl;
    #endif

    #ifdef NODES
    cout << "nodes: " << sol.getGeneratedNodes() << " / " << sol.getPossibleNodes() << endl;
    cout << "podas: " << sol.getPodas() << endl << endl;
    #endif

    #ifdef COST
    cout << n << " " << sol.getCost() << endl;
    #endif

    #ifdef TIME
    cout << n << " " << ((ld)(t_after - t_before)/ CLOCKS_PER_SEC) << endl;
    #endif

    return 0;
}