/**
   @file Ordenaci�n por inserci�n
*/

#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <fstream>

#define TYPE double

/* ************************************************************ */
/*  M�todo de ordenaci�n por inserci�n  */

/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
			 Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
inline static void insercion(TYPE T[], int num_elem);

/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos
				   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
				   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
				   vector a ordenar.
	   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
static void insercion_lims(TYPE T[], int inicial, int final);

/**
   Implementaci�n de las funciones
**/

inline static void insercion(TYPE T[], int num_elem)
{
	insercion_lims(T, 0, num_elem);
}

static void insercion_lims(TYPE T[], int inicial, int final)
{
	int i, j;
	TYPE aux;
	for (i = inicial + 1; i < final; i++)
	{
		j = i;
		while ((j > inicial) && (T[j] < T[j - 1]))
		{ 
			aux = T[j];
			T[j] = T[j - 1];
			T[j - 1] = aux;
			j--;
		};
	};
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Uso: ./insercion <n>" << endl;
		exit(1);
	}

	int n = atoi(argv[1]);

	TYPE *T = new TYPE[n];
	assert(T);

	chrono::high_resolution_clock::time_point tantes, tdespues;
	chrono::duration<double> transcurrido;
	srandom(time(0));

	for (int i = 0; i < n; i++)
	{
		T[i] = random();
	};

	tantes = chrono::high_resolution_clock::now();

	insercion(T, n);

	tdespues = chrono::high_resolution_clock::now();

	transcurrido = tdespues - tantes;

	cout << n << " " << transcurrido.count() << endl;
	delete[] T;

	return 0;
};

// int main(int argc, char *argv[])
// {

//     if (argc != 2)
//     {
//         cerr << "Uso: ./insercion <n>" << endl;
//         exit(1);
//     }

//     int n = atoi(argv[1]);

//     TYPE *T = new TYPE[n];
//     assert(T);

//     chrono::high_resolution_clock::time_point tantes, tdespues;
//     chrono::duration<double> transcurrido;

//     ifstream is;
//     is.open("../Datos/quijote.txt");
//     if(!is) {
//         cerr << "Error al abrir el archivo ../Datos/quijote.txt" << endl;
//         exit(1);
//     }

//     for (int i = 0; i < n && is; i++)
//     {
//         is >> T[i];
//     }

// 	is.close();

//     tantes = chrono::high_resolution_clock::now();

//     insercion(T, n);

//     tdespues = chrono::high_resolution_clock::now();

//     transcurrido = tdespues - tantes;

//     cout << n << " " << transcurrido.count() << endl;

//     ofstream os;
//     os.open("../Datos/quijote_ordenado.txt");
//     int p_lin = 20;
//     for (int i=0; i < n; i++) {
//         os << T[i] << " ";
//         if(i%p_lin==p_lin-1) {
//             os << endl;
//         }
//     }
//     os.close();
	
//     delete[] T;

//     return 0;
// };

