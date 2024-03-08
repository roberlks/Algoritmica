#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define TYPE string


/* ************************************************************ */
/*  M�todo de ordenaci�n r�pida  */

/**
   @brief Ordena un vector por el m�todo quicksort.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo quicksort.
*/
inline static void quicksort(TYPE T[], int num_elem);

/**
   @brief Ordena parte de un vector por el m�todo quicksort.

   @param T: vector de elementos. Tiene un n�mero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar.
       inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo quicksort.
*/
static void quicksort_lims(TYPE T[], int inicial, int final);

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
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
static void insercion_lims(TYPE T[], int inicial, int final);

/**
   @brief Redistribuye los elementos de un vector seg�n un pivote.

   @param T: vector de elementos. Tiene un n�mero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar.
       inicial < final.
   @param pp: Posici�n del pivote. Es MODIFICADO.

   Selecciona un pivote los elementos de T situados en las posiciones
   entre inicial y final - 1. Redistribuye los elementos, situando los
   menores que el pivote a su izquierda, despu�s los iguales y a la
   derecha los mayores. La posici�n del pivote se devuelve en pp.
*/
static void dividir_qs(TYPE T[], int inicial, int final, int &pp);

/**
   Implementaci�n de las funciones
**/

const int UMBRAL_QS = 50;

inline void quicksort(TYPE T[], int num_elem)
{
    quicksort_lims(T, 0, num_elem);
}

static void quicksort_lims(TYPE T[], int inicial, int final)
{
    int k;
    if (final - inicial < UMBRAL_QS)
    {
        insercion_lims(T, inicial, final);
    }
    else
    {
        dividir_qs(T, inicial, final, k);
        quicksort_lims(T, inicial, k);
        quicksort_lims(T, k + 1, final);
    };
}


static void insercion_lims(TYPE T[], int inicial, int final)
{
    int i, j;
    TYPE aux;
    for (i = inicial + 1; i < final; i++)
    {
        j = i;
        while ((j > inicial)&&(T[j] < T[j - 1]))
        { // Creo que habría que poner j > inicial
            aux = T[j];
            T[j] = T[j - 1];
            T[j - 1] = aux;
            j--;
        };
    };
}


static void dividir_qs(TYPE T[], int inicial, int final, int &pp)
{
    TYPE pivote, aux;
    int k, l;

    pivote = T[inicial];
    k = inicial;
    l = final;
    do
    {
        k++;
    } while ((T[k] <= pivote) && (k < final - 1));
    do
    {
        l--;
    } while (T[l] > pivote);
    while (k < l)
    {
        aux = T[k]; // swap(k,l)
        T[k] = T[l];
        T[l] = aux;
        do
            k++;
        while (T[k] <= pivote);
        do
            l--;
        while (T[l] > pivote);
    };
    aux = T[inicial]; // swap(inicial,l)
    T[inicial] = T[l];
    T[l] = aux;
    pp = l;
};

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cerr << "Uso: ./burbuja <n>" << endl;
        exit(1);
    }

    int n = atoi(argv[1]);

    TYPE *T = new TYPE[n];
    assert(T);

    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> transcurrido;

    ifstream is;
    TYPE elem;
    is.open("../Datos/quijote.txt");
    if(!is) {
        cerr << "Error al abrir el archivo ../Datos/quijote.txt" << endl;
        exit(1);
    }

    for (int i = 0; i < n && is; i++)
    {
        is >> elem;
        T[i] = elem;
    };

	is.close();

    tantes = chrono::high_resolution_clock::now();

    quicksort(T, n);

    tdespues = chrono::high_resolution_clock::now();

    transcurrido = tdespues - tantes;

    cout << n << " " << transcurrido.count() << endl;
	
    delete[] T;

    return 0;
};



// int main(int argc, char* argv[])
// {
//   // int n;
//   // cout << "Introduce n�mero de elementos del vector: ";
//   // cin >> n;

//   if (argc != 2) {
//     cerr << "Uso: ./quicksort_type <n>" << endl;
//     exit(1);
//   }

//   int n = atoi(argv[1]);

//   TYPE * T = new TYPE[n];
//   assert(T);

//   chrono::high_resolution_clock::time_point tantes, tdespues;
//   chrono::duration<double> transcurrido;
//   srandom(time(0));

//   for (int i = 0; i < n; i++)
//     {
//       T[i] = random();
//     };

//   tantes = chrono::high_resolution_clock::now();

//   quicksort(T, n);

//   tdespues = chrono::high_resolution_clock::now();

//   transcurrido = tdespues - tantes;

//   cout << n << " " << transcurrido.count() << endl;
//   delete [] T;

//   return 0;
// };