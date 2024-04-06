#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

/**
 * @brief Returns a random float x € [a,b)
 * @param a minimum possible number (inclusive)
 * @param b maximum possible number (exclusive)
 * @return random float x € [a,b)
*/
int rnd(int a, int b){
    return a + rand() % (b - a + 1);
}

/**
 * @brief Generator for problem L-shape
 * @param argv[0] -> the seed for the random numbers
*/
int main(int argc, char * argv[]){
    // Check arguments
    if(argc < 2){
        cerr << "Error: faltan parametros\n";
        cerr << "<tamaño instancia> <nombre_fichero_salida>" << endl;
        return -1;
    }

    // Extract arguments
    int k = atoi(argv[1]); // Size of the output to be generated
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
    // n must be a power of 2 (size of the square)
    int n = 1 << k;

    srand(n);
    // (r,c) -> position of the square tile (zero base)
    int r = rnd(0,n-1);
    int c = rnd(0,n-1);
    // OUTPUT
    fout << n << endl;
    fout << r << " " << c;

    fout.close();
    return 0;
}
