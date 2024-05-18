#ifndef SOLUTION_H
#define SOLUTION_H

#include "City.h"

#include <set>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v);

template<typename T>
void remove(std::vector<T>& v, const T& elem);

struct Track {
    std::vector<int> track;
    std::vector<bool> visited;
    ld aprox_cost;

    Track(int n = 0) : visited(n, false), aprox_cost(0) {}
    Track(std::vector<int>& track, std::vector<bool>& visited, ld cost) : track(track), visited(visited), aprox_cost(cost) {}
    bool operator>(Track other) const {
        return this->aprox_cost > other.aprox_cost;
    }
};

class TSP_solution {

protected:
    std::vector<City> cities;
    std::vector<int> best_ans;
    ld cost;

    int podas;
    int generated;
    int version;

public:
    TSP_solution();
    TSP_solution(const std::vector<City>& v);

    std::vector<City> getCities() const;
    std::vector<int> getSol() const;
    ld getCost() const;
    int getPodas() const;
    ll getPossibleNodes() const;
    int getGeneratedNodes() const;
    void setCotaVersion(int version);
    void solve();
    void printAns();

private:
    virtual void algorithm(Track & e_node) = 0;
    ld f_cota1(Track& e_node, int node);
    ld f_cota2(Track& e_node, int node);
    ld f_cota3(Track& e_node, int node);
    ld trackDistance(const std::vector<int>& track);
    ld sumMinEnter(const std::vector<bool>& visited, int node);
    ld sumMinExit(const std::vector<bool>& visited, int node);
    ld enter_min_cost(const std::vector<bool>& visited, int node);
    ld exit_min_cost(const std::vector<bool>& visited, int node);
    std::set<ld> orderedEdges(const std::vector<bool>& visited, int node);
    void TSP_greedy();

protected:
    ld f_cota(Track& e_node, int node);
    std::pair<bool, ld> feasible(Track& e_node, int node);
    void processSolution(const std::vector<int>& track);
};

#endif
