#include <iostream>
#include <cmath>

typedef long long ll;
typedef long double ld;

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
    ld operator-(const City & other){
        return dist(other);
    }

    ld dist(const City & other){
        ll dx = x - other.x;
        ll dy = y - other.y;
        return sqrt(dx*dx+dy*dy);
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