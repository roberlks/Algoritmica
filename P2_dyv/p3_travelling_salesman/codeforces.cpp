#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ld INF = 1e18;

// Represents a city with coordinates (x,y)
// It implements dist() and operator p-q as the euclidean distance of 2 points
// Input and output operator are also implemented
struct City
{
    ll x, y;

    City(ll x = 0, ll y = 0) : x(x), y(y) {}

    // Euclidean distance (symetrical)
    ld operator-(const City &other)
    {
        return dist(other);
    }

    ld dist(const City &other)
    {
        return max(y, other.x - x);
    }

    // I/O operators
    friend std::istream &operator>>(std::istream &is, City &p)
    {
        is >> p.x >> p.y;
        return is;
    }
};

ld TSP_brute_value(int n, City p, const City v[], bool visited[])
{
    // cout << p << endl;
    ld sol = INF; // INF
    bool all_visited = true;
    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        { // If we haven't visited the city
            all_visited = false;
            visited[i] = true;
            sol = min(sol, TSP_brute_value(n, v[i], v, visited) + p.dist(v[i]));
            visited[i] = false;
        }
    }

    if (all_visited) // If we have visit all the cities we return back home
        sol = p.dist(v[0]);

    return sol;
}

//https://codeforces.com/problemset/problem/1503/C
int main()
{
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    City v[n];
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    // OUTPUT
    bool visited[n];
    memset(visited, false, sizeof(visited)); // Fill array with false
    visited[0] = true;
    std::cout << TSP_brute_value(n, v[0], v, visited) << endl;
    return 0;
}