#include <iostream>
#include "City.h"
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;

const int UMBRAL = 2;

/**
 * @struct Auxiliar 
 * @details Almacena parejas de iteradores constantes de list<int> que servirán de auxiliares en 
 * la resolución del problema
*/
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

/**
 * @brief Operador de salida, pinta una lista de int
*/
ostream& operator<<(ostream& os,const list<int>& l);

/**
 * @brief Calcula los puntos, uno de cada ciclo, cuya distancia sea mínima
 * @param v Vector de City, donde se almacena información relativa a las ciudades
 * @param c1 Lista donde guardan los índices de los elementos de un subconjunto de v
 * @param c2 Lista donde guardan los índices de los elementos de un subconjunto de v
 * @return Devuelva una pareja de iteradores que apuntan a elementos de V, un 
 * iterador de cada conjunto
*/
Auxiliar puntos_cercanos(City *v, const list<int>& c1, const list<int>& c2){

    list<int>::const_iterator it1 = c1.cbegin();
    list<int>::const_iterator it2 =  c2.cbegin();
    Auxiliar solucion(it1, it2);

    ll distancia =  v[*(it1)].dist(v[*(it2++)]);

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
 * @brief Avanza o retrocede el iterador según @pos_relativa
 * @param pos_relativa si 1 -> accede al siguiente, si -1 -> accede al anterior
 * @param c lista al cual pertenece el iterador @p it
 * @param it iterador con la que se manipula 
 * @return retorna un iterador que apunta a la posición a la que se quiere avanzar
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

/**
 * @brief Encuentra una aproximación del ciclo con valor mínimo que se puede establecer
 * con las ciudades de @p v .El valor de un ciclo es la suma de las distancias a recorrer para 
 * pasar por todas las ciudades en ciclo. 
 * @param v vector que contiene a las ciudades
 * @param init el primer elemento que se tiene en cuenta del vector
 * @param fin el último elemento que se tiene en cuenta del vector
 * @param ciclo lista donde se va a almacenar el orden en que se va a recorrer las ciudades 
*/

void dyv (City *v, int init, int fin, list<int>& ciclo) {

    if (fin - init <= UMBRAL) {
        
        for (int i = init; i < fin; ++i) {
            ciclo.push_back(i);
        } 
        return;
    }

    int mid = (fin + init)/2;

    list<int> c1,c2;
    dyv(v, init, mid, c1);
    dyv(v, mid, fin, c2);

    //cout << "\nC1: " << c1;
    //cout << "\nC2: " << c2;

    // Combinar las soluciones 

    // Sacar los puntos a distancia mínima 
    Auxiliar puntos_dist_min = puntos_cercanos(v, c1, c2); 

    // De los nodos adyacentes a los dos nodos seleccionados, sacar un segundo par de nodos con 
    // distancia mínima

    int pos[] = {-1,1};

    list<int>::const_iterator aux_it1 = acceso(pos[0], c1, puntos_dist_min.it1);
    list<int>::const_iterator aux_it2 = acceso(pos[0], c2, puntos_dist_min.it2);

    Auxiliar otros_puntos_dist_min(aux_it1, aux_it2);
    ll dist_aux = v[*aux_it1].dist(v[*aux_it2]);

    for (int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            aux_it1 = acceso(pos[i], c1, puntos_dist_min.it1);
            aux_it2 = acceso(pos[j], c2, puntos_dist_min.it2);

            if (v[*aux_it1].dist(v[*aux_it2]) < dist_aux) {
                otros_puntos_dist_min.set(aux_it1, aux_it2);
                dist_aux = v[*aux_it1].dist(v[*aux_it2]);
            }
        }
    }

    // Insertar un ciclo en otro


    //cout << "\nElegidos_1: " << puntos_dist_min.to_s();
    //cout << "\nElegidos_2: " << otros_puntos_dist_min.to_s();

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
    // Es por debugueo 

    do {
        ciclo.push_back(*it_fusion);
        it_fusion = acceso(sentido, c1, it_fusion);
    } while (insertados < c1.size() && it_fusion != puntos_dist_min.it1);

    //cout << "\nInsertado_fase1: " << ciclo;

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

   //cout << "\nInsertado_fase2: " << ciclo;
}

int main() {

    int n;

    cin >> n;

    City *vector = new City[n];

    for (int i = 0; i < n; i++) {
        cin >> vector[i];
    }
    City home = vector[0];

    sort(vector, vector+n);         //Falta definir el operador relacional  
/*
    for (int i = 0; i < n; i++) {
        //cout << vector[i] << " ";
    }
*/

    list<int> ciclo_resultado;

    dyv(vector, 0, n, ciclo_resultado);

    //  cout << "\nSe imprimirá el ciclo obtenido ( size = " << ciclo_resultado.size() << "): \n";

    // Girar ciclo_resultado hasta cero / ciudad inicial por defecto
    
    list<int> rotado;

    

    typename list<int>::iterator it = ciclo_resultado.begin();

    while (*it != 0) {
        rotado.push_back(*it);
        ++it;
    }

    rotado.insert(rotado.begin(), it, ciclo_resultado.end());

    // cout << rotado;
    // cout << *rotado.begin();

    // cout << endl;

    int pos_ini;
    for(int i=0; i < n; i++) {
        if (vector[i] == home)
            pos_ini = i;
    }

    auto it_origin = find(rotado.begin(),rotado.end(),pos_ini);
    for (typename list<int>::const_iterator it = it_origin; 
                                                        it != rotado.end(); ++it) {
        cout << vector[*it] << " ";
    }
    for (typename list<int>::const_iterator it = rotado.begin(); 
                                                        it != it_origin; ++it) {
        cout << vector[*it] << " ";
    }
    cout << vector[*it_origin];

    
    double sum = 0;
    typename list<int>::const_iterator pre  = rotado.cbegin();
    typename list<int>::const_iterator post = pre;
    ++post;

    for (; post != rotado.cend(); ++post) {
        sum += vector[*post].dist(vector[*(pre)]);
        pre = post;
    }

    cout << sum << endl;

    return 0;
}

/*ostream& operator<<(ostream& os,const list<int>& l) {

    for (typename list<int>::const_iterator it = l.cbegin(); 
                                                        it != l.cend(); ++it) {
        cout << *it << " ";
    }
    return os;
}*/

ostream& operator<<(ostream& os,const list<int>& l) {

    auto it_origin = find(l.cbegin(),l.cend(),0);
    for (typename list<int>::const_iterator it = it_origin; 
                                                        it != l.cend(); ++it) {
        cout << *it << " ";
    }
    for (typename list<int>::const_iterator it = l.cbegin(); 
                                                        it != it_origin; ++it) {
        cout << *it << " ";
    }
    cout << *it_origin;
    return os;
}