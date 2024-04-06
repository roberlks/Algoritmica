#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Maximum size of the array
const int MAXN = 1e5;

/**
 * @brief Returns a random int x € [a,b)
*/
int rnd(int a, int b){
    return a + rand() % (b - a + 1);
}

/**
 * @brief Generator for problem subsequence
 * @param argv[0] -> the number of elements of the vector
 * @param argv[1] -> name of instance created
*/
int main(int argc, char * argv[]){

    // Check arguments
    if(argc < 2){
        cerr << "Error: faltan parametros\n";
        cerr << "<tamaño instancia> <nombre_fichero_salida>" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    char output_file[80] = "."; // Path of the output file
    strcat(output_file,argv[2]);
    // Open/create output file (truncate if it existed befores)
    ofstream fout(output_file,ios::out|ios::trunc);
    // Check for errors opening the file
    if(!fout){
        cerr << "Error: no se pudo abrir el archivo " << output_file << endl;
        return -1;
    }
    // OUTPUT
    srand(n);
    fout << n << endl;
    for(int i=0; i<n; ++i){
        // Generate random positive and negative numbers
        fout << rnd(-MAXN,MAXN+1) << " ";
    }

    fout.close();
    return 0;
}