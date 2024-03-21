
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <cfloat>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define TYPE string
//#define TYPE_MAX DBL_MAX

 
/* ************************************************************ */
/*  M�todo de ordenaci�n por mezcla  */

/**
   @brief Ordena un vector por el m�todo de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static void mergesort(TYPE T[], int num_elem);

/**
   @brief Ordena parte de un vector por el m�todo de mezcla.

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
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(TYPE T[], int inicial, int final);

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
   Aplica el algoritmo de la inserci�n.
*/
static void insercion_lims(TYPE T[], int inicial, int final);

/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un n�mero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a escribir.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a escribir
       inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El n�mero de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static void fusion(TYPE T[], int inicial, int final, TYPE U[], TYPE V[]);

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
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((j > inicial)&&(T[j] < T[j-1])) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_MS = 100;



void mergesort(TYPE T[], int num_elem)
{
    mergesort_lims(T, 0, num_elem);
}

static void mergesort_lims(TYPE T[], int inicial, int final)
{
    if (final - inicial < UMBRAL_MS)
    {
        insercion_lims(T, inicial, final);
    }
    else
    {
        
        int k = (final - inicial) / 2;

        TYPE *U = new TYPE[k - inicial + 1];
        assert(U);
        int l, l2;

        
        for (l = 0, l2 = inicial; l < (k-inicial); l++, l2++)
            U[l] = T[l2];
        
        
        
        TYPE *V = new TYPE[final - k + 1];
        assert(V);
        for (l = 0, l2 = k; l < final - k; l++, l2++)
            V[l] = T[l2];
        
        
        
        mergesort_lims(U, 0, k-inicial);
        mergesort_lims(V, 0, final - k);

        
        fusion(T, inicial, final, U, V);
        
        delete[] U;
        delete[] V;
    };
}

static void fusion(TYPE T[], int inicial, int final, TYPE U[], TYPE V[])
{
    int j = 0;
    int k = 0;
    int tam = (final - inicial) / 2;
    for (int i = inicial; i < final; i++)
    {


        if ((k==tam)  || ((j<tam) && (U[j] < V[k])) )
        {
            T[i] = U[j];
            j++;
        }
        else
        {
            T[i] = V[k];
            k++;
        };
    };
}
/*MAIN PARA TIPOS GENERALES
int main(int argc, char* argv[])
{
  // int n;
  // cout << "Introduce n�mero de elementos del vector: ";
  // cin >> n;

  if (argc != 2) {
    cerr << "Uso: ./mergesort_type <n>" << endl;
    exit(1);
  }

  int n = atoi(argv[1]);

  TYPE * T = new TYPE[n];
  assert(T);

  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;
  srandom(time(0));

  for (int i = 0; i < n; i++)
    {
      T[i] = random();
    };

  tantes = chrono::high_resolution_clock::now();

  mergesort(T, n);

  tdespues = chrono::high_resolution_clock::now();

  transcurrido = tdespues - tantes;

  cout << n << " " << transcurrido.count() << endl;
  delete [] T;

  return 0;
};*/


/*MAIN PARA STRING*/
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

    for (int i = 0; is && i<n; i++)
    {
        is >> elem;
        T[i] = elem;
    };

	is.close();

    tantes = chrono::high_resolution_clock::now();

    mergesort(T, n);

    tdespues = chrono::high_resolution_clock::now();

    transcurrido = tdespues - tantes;

    cout << n << " " << transcurrido.count() << endl;
	
    delete[] T;

    return 0;
};
