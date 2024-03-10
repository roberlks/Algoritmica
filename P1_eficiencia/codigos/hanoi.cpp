/**
   @file Resoluci�n del problema de las Torres de Hanoi
*/

   
#include <iostream>
using namespace std;
#include <ctime>


/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: n�mero de discos. M > 1.
   @param i: n�mero de columna en que est�n los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: n�mero de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta funci�n imprime en la salida est�ndar la secuencia de 
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restricci�n de que ning�n
   disco se puede situar sobre otro de tama�o menor. Utiliza
   una �nica columna auxiliar.
*/
void hanoi (int M, int i, int j);




void hanoi (int M, int i, int j)
{
  if (M > 0)
    {
      hanoi(M-1, i, 6-i-j);
      //cout << i << " -> " << j << endl;
      hanoi (M-1, 6-i-j, j);
  }
}
/*
int main()
{

  int M;
  do
    {
      cout << "N�mero de discos: ";
      cin >> M;
    } while (M <= 0);

  hanoi(M, 1, 2);

  return 0;
}
*/
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "Formato " << argv[0] << " <num_elem>" << endl;
    return -1;
  }

  const int TAM_GRANDE = 28;
  const int NUM_VECES = 10;

  int n = atoi(argv[1]);

  if (n > TAM_GRANDE)
  {
    clock_t t_antes = clock();

    hanoi(n, 1, 2);

    clock_t t_despues = clock();

    cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC
         << endl;
  }
  else
  {
    clock_t t_antes = clock();

    for (int veces = 0; veces < NUM_VECES; ++veces)
      hanoi(n, 1, 2);;

    clock_t t_despues = clock();

    cout << n << " \t  "
         << (double)(t_despues - t_antes) / (CLOCKS_PER_SEC * NUM_VECES)
         << endl;
  }
}