#include <iostream>
#include <limits>
#include <vector>
#include <utility>

using namespace std;

void mss_lin (vector<int> vec) {

    // Conforme recorremos el vector, lo vamos delimitando
    // conceptualmente en subsecuencias que terminan
    // cada vez que la suma acumulada es negativa.
    // Las propiedades (no difícilmente demostrables) que tienen
    // estas subsecuencias son: 
   
    //  1. Que la SSM no puede ser
    //  partida por ellas, es decir, 
    // tiene que estar enteramente contenida
    // en alguna de éstas
    // 2. Que la SSM comienza en el principio
    // de alguna de ellas (y entonces, claramente
    // termina en cuanto se alcance la máxima
    // suma dentro de esa subsecuencia empezando por el 
    // principo)
    //
    // Por tanto, para obtener la SSM, acumulamos de la siguiente
    // manera:

    int sum_in_this_subseq_so_far = 0;
    int max_sum_this_subseq = std::numeric_limits<int>::min();

    int index_beg_this_subseq = 0;
    int index_end_max_sum_this_subseq = 0;
    
    int max_sum = std::numeric_limits<int>::min();
    int index_end_max_sum = 0;
    int index_beg_max_sum = 0;

    for (int i = 0; i < vec.size(); i++) {
        sum_in_this_subseq_so_far += vec[i];
        if (sum_in_this_subseq_so_far >= max_sum_this_subseq) {
            max_sum_this_subseq = sum_in_this_subseq_so_far;
            index_end_max_sum_this_subseq = i;
        }
        // Comprobamos si debemos terminar
        // la subsecuencia (la suma es negativa o 0)
        if (sum_in_this_subseq_so_far <= 0 || i == vec.size()-1) {
            // Hemos terminado, compruebo si la suma
            // máxima obtenida hasta ahora es mayor
            // que la suma máxima de las anteriores subsecuencias
            if (max_sum_this_subseq >= max_sum) {
                max_sum = max_sum_this_subseq;
                index_beg_max_sum = index_beg_this_subseq;
                index_end_max_sum = index_end_max_sum_this_subseq;
            }

            // En cualquier caso, como hemos terminado
            // la subseq, ponemos la suma de subsecuencia a 0
            // y la max_sum_subseq al mínimo
            sum_in_this_subseq_so_far = 0;
            max_sum_this_subseq = std::numeric_limits<int>::min();
            index_beg_this_subseq = i + 1;
        }
    }

    for (int i = index_beg_max_sum; i < index_end_max_sum; i++)
	cout << vec[i] << ", ";
    cout << vec[index_end_max_sum] << endl;
}

int main (int argc, char** argv) {
    vector<int> vec = {2,3,-1,6,1,2,-30,2,5,1};
    mss_lin(vec);
}
