#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

/**
 * @brief Returns a random number x € [a,b)
 * @param a minimum possible number (inclusive)
 * @param b maximum possible number (exclusive)
 * @return random int x € [a,b)
*/

int rnd(int a, int b){
    return a + rand() % (b - a + 1);
}

/**
 * @brief Generator for problem assign_classroom2exams
 * @param argv[0] -> number of exams
 * @param argv[1] -> name of the output file
*/

int main(int argc, char * argv[]){
    // Check arguments
    if(argc < 2){
        cerr << "Error: faltan parametros\n";
        cerr << "<número de examenes> <nombre_fichero_salida>" << endl;
        return -1;
    }

    // Extract arguments
    int n = atoi(argv[1]);      // Number of exams

    // Name of the output file
    char output_file[80] = ""; // Path of the output file
    strcat(output_file,argv[2]);

    // Open/create output file (truncate if it existed befores)
    ofstream fout(output_file,ios::trunc);

    // Check for errors opening the file
    if(!fout){
        cerr << "Error: no se pudo abrir el archivo " << output_file << endl;
        return -1;
    }

    srand(n);


    int h,m;        // h:m --> hour:minutes ( the start time of the exam) 
    int duration;   // duration of the exam

    // horas y duracion de los examenes
    fout << n << endl << endl;

    for (int i = 0; i < n; ++i) {
        h = rnd(0,24);      // hour
        m = rnd(0,60);      // minutes
        duration = rnd(15,120);     // duration

        fout << h << ":" <<  setfill('0') << setw(2) << right << m << "\t" << duration << endl;   
    }

    fout.close();
    return 0;
}