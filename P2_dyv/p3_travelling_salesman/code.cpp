#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

// Represents a point with coordinates (x,y)
// It implements dist() and operator p-q as the euclidean distance of 2 points
// Input and output operator are also implemented
struct P
{
    ll x,y;
    //? maybe añadir id para que se mas facil luego imprimir ciudad 0, ciudad 2 etc para el ciclo

    // Constructor
    P(ll x=0,ll y=0) : x(x), y(y) {}

    // Euclidean distance 
    ld operator-(const P & other){
        return dist(other);
    }

    ld dist(const P & other){
        ll dx = x - other.x;
        ll dy = y - other.y;
        return sqrt(dx*dx+dy*dy);
    }

    // I/O operators
    friend istream & operator>>(istream & is, P p){
        is >> p.x >> p.y;
        return is;
    }
    friend ostream & operator<<(ostream & os, P p){
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

};

//TODO Divide and conquer implementation
//TODO Since we will be using the Euclidean Distance, its probably useful to order the points
//TODO either by this distance or one of the coordinates
//TODO I suggest one of the coordinates (x for example)


int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    P v[n];
    for(int i=0; i<n; ++i)
        cin >> v[i];
}