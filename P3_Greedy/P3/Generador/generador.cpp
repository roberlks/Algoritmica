#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>
#include "../../Include/City.h"
using namespace std;

const ld MAX_COORDINATE = 1e9;

void make_set(int node,vector<int> & parent, vector<int> & rank){
    parent[node] = node;
    rank[node] = 0;
}

int find_set(int node, vector<int> & parent){
    if(parent[node] == node) return node;
    return parent[node] = find_set(parent[node],parent);
}

bool same_set(int u, int v, vector<int> & parent){
    return find_set(u,parent) == find_set(v,parent);
}

bool union_sets(int u, int v, vector<int> & parent, vector<int> & rank){
    int pu = find_set(u,parent);
    int pv = find_set(v,parent);

    if(pu == pv) // Nothing to join here
        return false;

    if(rank[pu] < rank[pv])
        swap(pu,pv);
    parent[pv] = pu;
    if(rank[pu] == rank[pv])
        ++rank[pu];
    return true;
}

/**
 * @brief Returns a random float x € [a,b)
 * @param a minimum possible number (inclusive)
 * @param b maximum possible number (exclusive)
 * @return random float x € [a,b)
*/
ld rnd(ld a, ld b){
    ld f = (ld)rand() / RAND_MAX;
    return a + f*(b-a);
}

int main(int argc, char * argv[]){
    // Check arguments
    if(argc < 2){
        cerr << "Error: faltan parametros\n";
        cerr << "<tamaño instancia> <nombre_fichero_salida>" << endl;
        return -1;
    }

    // Extract arguments
    int n = atoi(argv[1]); // Size of the output to be generated
    // Name of the output file
    char output_file[80] = ""; // Path of the output file
    strcat(output_file,argv[2]);
    // Open/create output file (truncate if it existed befores)
    ofstream fout(output_file,ios::out|ios::trunc);
    // Check for errors opening the file
    if(!fout){
        cerr << "Error: no se pudo abrir el archivo " << output_file << endl;
        return -1;
    }

    // OUPUT
    srand(n);
    #ifndef VISUAL
        fout << n << endl; // Number of cities
    #endif
    // Generate n random cities
    vector<City> cities(n);
    for(int i=0; i<n; ++i){
        cities[i] =  City(rnd(-MAX_COORDINATE,MAX_COORDINATE),rnd(-MAX_COORDINATE,MAX_COORDINATE));
        #ifndef VISUAL
            fout << cities[i] << endl;
        #endif
    }

    // Generate random edges
    set<pair<int,int>> edges;
    int n_sets = n;
    vector<int> parent(n),rank(n);
    for(int i = 0; i < n; ++i){
        make_set(i,parent,rank);
    }
    int x,y, m=0;
    while(n_sets > 1){
        x = rnd(0,n);
        do { // Self edges not allowed
            y = rnd(0,n);
        }while(x == y);
        if(edges.emplace(min(x,y),max(x,y)).second){
            ++m;
            n_sets -= union_sets(x,y,parent,rank);
        }
    }

    #ifndef VISUAL
        fout << m << endl; // Number of edges
    #endif
    for(auto it = edges.begin(); it != edges.end(); ++it){
        #ifndef VISUAL
            fout << it->first << " " << it->second << endl;
        #else
            //fout << cities[it->first] << " " << cities[it->second] << endl;
            fout << cities[it->first] << endl;
            fout << cities[it->second] << endl;
            fout << endl;
        #endif
    }
    fout.close();
    return 0;
}