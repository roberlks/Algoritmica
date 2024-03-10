/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

#include <iostream>
using namespace std;
#include <ctime>

/**
   @brief Calcula el término n-ésimo de la sucesión de Fibonacci.

   @param n: número de orden del término buscado. n >= 1.

   @return: término n-ésimo de la sucesién de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n - 1) + fibo(n - 2);
}

/*int main()
{

  int n;
  int f;

  cout << "�N�mero del t�rmino: ";
  cin >> n;

  f = fibo(n);

  cout << "El t�rmino " << n << "-�simo es: " << f << endl;

  return 0;
}*/

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "Formato " << argv[0] << " <num_elem>" << endl;
    return -1;
  }

  const int TAM_GRANDE = 41;
  const int NUM_VECES = 30;

  int n = atoi(argv[1]);

  if (n > TAM_GRANDE)
  {
    clock_t t_antes = clock();

    fibo(n);

    clock_t t_despues = clock();

    cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC
         << endl;
  }
  else
  {
    clock_t t_antes = clock();

    for (int veces = 0; veces < NUM_VECES; ++veces)
      fibo(n);

    clock_t t_despues = clock();

    cout << n << " \t  "
         << (double)(t_despues - t_antes) / (CLOCKS_PER_SEC * NUM_VECES)
         << endl;
  }
}