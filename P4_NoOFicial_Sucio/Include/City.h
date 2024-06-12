#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <cmath>
#include <vector>

typedef long long ll;
typedef long double ld;

// Infinity (biggest possible number)
const ld INF = 1e18;

// Represents a city with coordinates (x, y)
struct City {
    ld x, y;

    // Constructor
    City(ld x = 0, ld y = 0) : x(x), y(y) {}

    // Euclidean distance (symmetrical)
    ld operator-(const City& other) const;
    ld dist(const City& other) const;

    // Sort by x axis
    friend bool operator<(const City& a, const City& b);
    friend bool operator==(const City& a, const City& b);
    friend bool operator!=(const City& a, const City& b);

    // I/O operators
    friend std::istream& operator>>(std::istream& is, City& p);
    friend std::ostream& operator<<(std::ostream& os, const City& p);
};

// Calculates the distance of the given cycle (cycle)
ld cycleDistance(const std::vector<int>& cycle, const std::vector<City>& v);

// Prints a cycle (index) starting and ending at origin
void printCycle(const std::vector<int>& cycle, int origin = 0);

// Prints a cycle (the cities) starting and ending at origin
void printCycle(const std::vector<int>& cycle, const City& origin, const std::vector<City>& v);

#endif // CITY_H
