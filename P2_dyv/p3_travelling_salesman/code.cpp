#include <bits/stdc++.h>
#include "City.h"
using namespace std;

const int UMBRAL = 2;

void closestNeighbour(const list<City> & path1, const list<City> & path2){
    for(auto it1 = path1.begin(); it1 != path1.end(); ++it1){
        for(auto it2 = path2.begin(); it2 != path2.end(); ++it2){

        }
    }
}

// [ini,fin)
void dyv(City v[], int ini, int fin, list<City> & path){
    // Base case 
    if(fin - ini < UMBRAL){ 
        return;
    }

    //Divide
    list<City> path1,path2;
    int mid = (fin-ini)/2;
    dyv(v,ini,mid,path1);
    dyv(v,mid,fin,path2);

    //Fusion
}

int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    City v[n];
    for(int i=0; i<n; ++i)
        cin >> v[i];

    // Sort by x axis
    //sort(v,v+n);

    
}