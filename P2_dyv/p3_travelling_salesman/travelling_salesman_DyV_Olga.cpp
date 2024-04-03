#include <iostream>
#include "City.h"
#include <list>
#include <utility>

using namespace std;

typedef long long ll;

struct Auxiliar{

    typename list<int>::const_iterator it1;
    typename list<int>::const_iterator it2;

    Auxiliar(){}
    Auxiliar(typename list<int>::const_iterator it1, typename list<int>::const_iterator it2): 
        it1(it1), it2(it2) {};
    
    void set(typename list<int>::const_iterator it1, typename list<int>::const_iterator it2) {
        this->it1 = it1;
        this->it2 = it2;
    }

    string to_s() {
        string str = "(" + to_string(*it1) + "," +  to_string(*it2) + ")";
        return str;
    }
};

ostream& operator<<(ostream& os,const list<int>& l);

// Calcula los puntos con la distancia mínima entre dos conjuntos
Auxiliar puntos_cercanos(City *v, const list<int>& c1, const list<int>& c2){

    list<int>::const_iterator it1 = c1.cbegin();
    list<int>::const_iterator it2 =  c2.cbegin();
    Auxiliar solucion(it1, it2);

    ll distancia =  v[*(it1++)].dist(v[*(it2++)]);

    ll aux;
    for (; it1 != c1.cend(); ++it1) {
        for (; it2 != c2.cend(); ++it2) {

            aux = v[*it1].dist(v[*it2]);

            if( aux < distancia) {
                solucion.set(it1, it2);
                distancia = aux;
            }
        }
    }

    return solucion;
}

/**
 * @param pos_relativa si 1 -> accede al siguiente, si -1 -> accede al anterior
*/
list<int>::const_iterator acceso(int pos_relativa, const list<int>& c, list<int>::const_iterator it) {

    if  (c.size() < 1) {
        throw invalid_argument("Error: function const_iterator acceso(pos, c, it), size of c too small");
    }

    list<int>::const_iterator resultado; 

    if (pos_relativa == -1) {

        if (it != c.cbegin()) {
            resultado = it;
            --resultado;
        } else {
            resultado = c.cend();
            --resultado;
        }
    }
    else if (pos_relativa == 1) {

        resultado = it;
        resultado++;
        if (resultado == c.cend()) {
            resultado = c.cbegin();
        }
    }
    else {
        throw invalid_argument("Error: const_iterator acceso(pos, c, it), invalid pos");
    }

    return resultado;
}

// [init, fin)
void dyv (City *v, int init, int fin, list<int>& ciclo) {

    if (fin - init < 3) {
        
        for (int i = init; i < fin; ++i) {
            ciclo.push_back(i);
        } 
        return;
    }

    int mid = (fin + init)/2;

    list<int> c1,c2;
    dyv(v, init, mid, c1);
    dyv(v, mid, fin, c2);

    cout << "\nC1: " << c1;
    cout << "\nC2: " << c2;

    // Combinar las soluciones 

    // Sacar los puntos a distancia mínima 
    Auxiliar puntos_dist_min = puntos_cercanos(v, c1, c2); 

    // De los nodos consecutivos de los dos puntos, sacar un segundo par de puntos
    int pos[] = {-1,1};

    list<int>::const_iterator aux_it1 = acceso(pos[0], c1, puntos_dist_min.it1);
    list<int>::const_iterator aux_it2 = acceso(pos[0], c2, puntos_dist_min.it2);

    Auxiliar otros_puntos_dist_min(aux_it1, aux_it2);
    ll dist_aux = v[*aux_it1].dist(v[*aux_it2]);

    for (int i = 1; i < 2; ++i) {
        for(int j = 1; j < 2; ++j) {
            aux_it1 = acceso(pos[i], c1, puntos_dist_min.it1);
            aux_it2 = acceso(pos[j], c2, puntos_dist_min.it2);

            if (v[*aux_it1].dist(v[*aux_it2]) < dist_aux) {
                otros_puntos_dist_min.set(aux_it1, aux_it2);
                dist_aux = v[*aux_it1].dist(v[*aux_it2]);
            }
        }
    }

    // Insertar un ciclo en otro


    cout << "\nElegidos_1: " << puntos_dist_min.to_s();
    cout << "\nElegidos_2: " << otros_puntos_dist_min.to_s();

    // Ciclos a combinar son los indicados en puntos_dist_min y otros_puntos_dist_min

    typename list<int>::const_iterator it_fusion = puntos_dist_min.it1;

    int sentido = 1;         // Avanza en la lista
    int insertados = 0;

    if (acceso(sentido, c1, it_fusion) == otros_puntos_dist_min.it1) {
        sentido = -1;       // Se va en sentido inverso, retrocede en la lista 
    }

    // Hasta que no se hayan insertado todos los elementos 
    // Hasta que el iterador no de el ciclo entero
    // Ambas condiciones son equivalentes
    // Es por debuguo 

    do {
        ciclo.push_back(*it_fusion);
        it_fusion = acceso(sentido, c1, it_fusion);
    } while (insertados < c1.size() && it_fusion != puntos_dist_min.it1);

    cout << "\nInsertado_fase1: " << ciclo;

    // Se inserta la siguiente lista

    it_fusion = otros_puntos_dist_min.it2;
    insertados = 0;

    if (acceso(sentido, c2, it_fusion) == puntos_dist_min.it2) {
        sentido = -sentido;             // Se cambia de sentido  
    }

    do {
        ciclo.push_back(*it_fusion);
        it_fusion = acceso(sentido, c2, it_fusion);

    } while (insertados < c2.size() && it_fusion != otros_puntos_dist_min.it2);

   cout << "\nInsertado_fase2: " << ciclo;
}

int main() {

    int n;

    cin >> n;

    City *vector = new City[n];

    for (int i = 0; i < n; i++) {
        cin >> vector[i];
    }
    
    // sort(vector, vector+n); Falta definir el operador relacional  

    for (int i = 0; i < n; i++) {
        cout << vector[i] << " ";
    }


    list<int> ciclo_resultado;

    dyv(vector, 0, n, ciclo_resultado);

    cout << "\nSe imprimirá el ciclo obtenido ( size = " << ciclo_resultado.size() << "): \n";

    cout << ciclo_resultado;

    cout << endl;
}

ostream& operator<<(ostream& os,const list<int>& l) {

    for (typename list<int>::const_iterator it = l.cbegin(); 
                                                        it != l.cend(); ++it) {
        cout << *it << " ";
    }
    return os;
}