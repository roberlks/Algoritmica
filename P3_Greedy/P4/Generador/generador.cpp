#include <iostream>
#include <fstream>
#include <cstring>
#include "../../Include/City.h"
using namespace std;

const ld MAX_COORDINATE = 1e9;

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
    fout << n << endl; // Number of cities
    // Generate n random cities
    for(int i=0; i<n; ++i){
        City random_city(rnd(-MAX_COORDINATE,MAX_COORDINATE),rnd(-MAX_COORDINATE,MAX_COORDINATE));
        fout << random_city << endl;
    }

    fout.close();
    return 0;
}