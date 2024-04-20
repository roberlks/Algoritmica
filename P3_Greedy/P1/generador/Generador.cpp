#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace std;

const int MAXN = 1e5;

random_device rd;  // Obtain a random number from hardware
mt19937 eng(rd()); // Seed the generator
uniform_int_distribution<> distr(0, MAXN); // Define the range

int main(int argc, char *argv[]) {
    if (argc < 3){
        cerr << "Error: faltan parametros\n";
        cerr << "<tamaño instancia> <nombre_fichero_salida>" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    ofstream fout(argv[2], ios::out | ios::trunc);

    if (!fout) {
        cerr << "Error: no se pudo abrir el archivo " << argv[2] << endl;
        return -1;
    }
    fout << n << endl <<  distr(eng) % n << endl;
    for (int i = 0; i < n; ++i) {
        fout << distr(eng) << " ";
    }

    fout.close();
    return 0;
}
