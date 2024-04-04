#include <iostream>
#include <cmath>
#include <vector>

typedef long long ll;
typedef long double ld;

const ld INF = 1e18;

// Represents a city with coordinates (x,y)
// It implements dist() and operator p-q as the euclidean distance of 2 points
// Input and output operator are also implemented
struct City
{
    ll x,y;
    //? maybe añadir id para que se mas facil luego imprimir ciudad 0, ciudad 2 etc para el ciclo

    // Constructor
    City(ll x=0,ll y=0) : x(x), y(y) {}

    // Euclidean distance (symetrical)
    ld operator-(const City & other) const{
        return dist(other);
    }

    ld dist(const City & other) const{
        ll dx = x - other.x;
        ll dy = y - other.y;
        return sqrt(dx*dx+dy*dy);
    }

    // Sort by x axis
    friend bool operator<(const City & a, const City & b){
        return a.x < b.x;
    }

    friend bool operator==(const City & a, const City & b){
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator<(const City & a, const City & b){
        return a.x < b.x;
    }

    // I/O operators
    friend std::istream & operator>>(std::istream & is, City & p){
        is >> p.x >> p.y;
        return is;
    }
    friend std::ostream & operator<<(std::ostream & os, const City &p){
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

};

/**
 * @brief Calculates the distance of the given cycle (cycle)
 * @param cycle the cycle to calculate the distance from
 * @param v the cities
 * @return the distance between all the consecutive cities of the cycle
*/
ld cycleDistance(const std::vector<int> & cycle,const City v[])
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

void printCycle(const std::vector<int> & cycle, int origin = 0){
    int ini = 0;
    while(cycle[ini] != origin) ++ini;
    for(int i=ini; i<(int)cycle.size(); ++i){
        std::cout << cycle[i] << " ";
    }
    for(int i=0; i<ini; ++i){
        std::cout << cycle[i] << " ";
    }
    std::cout << origin << std::endl;
}