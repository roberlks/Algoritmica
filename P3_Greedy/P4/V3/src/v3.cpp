#include "../include/City.h"
#include "../include/Edge.h"
#include <utility>
#include <algorithm>

using namespace std;

/*
   * 
   *
   *
   *
   *
*/
// En cada paso escojo añadir al proyecto de camino
// la arista que tenga mínimo coste (es decir, el par
// de ciudades más cercanas), cumpliendo todo el rato
// las siguietnes restricciones:
// - No hay nunca una ciudad con grado mayor de 2
//   (grado = nº de ciudades con las que está conectada)
// - No hay nunca un ciclo (si no hemos llegado
// ya a las n aristas)
// - Si ya tenemos n aristas, hemos terminado

// Por tanto, dado el vector de ciudades City v[],
// vamos añadiendo "aristas" a un vector de pares
// pares de enteros con las anteriores restricciones,
// y después transformamos el vector de aristas
// en un vector de ciudades normal. ¿Cómo? Pues escojo
// una ciudad cualquiera y la meto en el normal, la busco en 
// el vector de pares y meto su compañera. Ahora busco
// un par con esa y con alguna compañera distinta de la 
// primera que metimos, y añado esa compañera.


void fill_with_edges(int ini, int fin, City v[], vector<Edge> &vec_arist) {
    for (int i = ini; i <= fin; i++) {
	// para cada ciudad v[i], meto su arista con todas las
	// que no lo haya metido ya

	for (int j = i+1; j <= fin; j++) {
	    vec_arist.push_back(Edge(v[i],v[j]));
	}
    }
}

bool busca_camino(vector<pair<int,int>> v, int sig, int beg)
{
    // La función recursivamente va tirando del hilo desde
    // el princpio de la cadena de enteros. Si llega
    // a donde emepezó (beg), entonces es que el grafo
    // es un ciclo

    bool encontrado = false;
    
    bool f = false;
    bool s = false;
    auto index = v.end();
    

    for (auto it = v.begin(); (it != v.end()) && !encontrado; it=next(it)) {
	f = (*it).first == sig;
	s = (*it).second == sig;
	encontrado = f || s;
	if (encontrado){
	    index = it;
	} 
    }

    if (!encontrado) return false; // El camino se corta
    else {
	int other;
	if (f) {
	    sig = (*index).second; // El siguiente a buscar en la cadena
	}
	else {
	    sig = (*index).first;
	}

	if (sig == beg || other == beg) // Hemos encontardo el que veníamos buscando 
	    return true;
	else {
	    v.erase(index); 
	    return busca_camino(v, sig, beg);
	}
    }

}


// Función que dado un camino con aristas nos devuelve si
// es un ciclo
// (Notemos que, en esta implementación, por haber comprobado
// el grado, solo hay ciclo en el grafo si el grafo total
// es un ciclo)

bool hay_ciclo(vector<pair<int,int>> v)
{
    // Es un ciclo si y solo
    // si podemos empezar en algun
    // nodo y terminar en ese mismo
    // siguiendo el camino que nos dan las aristas

    if (v.size() > 0) {
	int beg_node = v.at(0).first; // Por ejemplo
	int sig = v.at(0).second;
	v.erase(v.begin());

	return busca_camino(v,sig,beg_node);
    } else return true;
}


void greedy_tsp(int ini, int fin, City v[], vector<int> &path) {

    int n_cities = fin-ini+1; // Numero de ciudades
    vector<pair<int,int>> res_arist;

    // Guardamos en un vector todas las aristas y las ordenamos
    // por coste (dist euclídea en este caso, pues está implementado así el
    // operador <)

    vector<Edge> vec_todas_arist;
    fill_with_edges(ini,fin,v,vec_todas_arist);

    int n_edges = vec_todas_arist.size();
    sort(vec_todas_arist.begin(),vec_todas_arist.end());

    vector<int> deg(n_cities); // Vector con los grados de cada ciudad

    int n = 0;
    bool bad_degree = 0;

    for (int i = 0; i < n_edges; i++) {
	Edge min_arist = vec_todas_arist.at(i);

	// Tomamos los índices de las ciudades de la arista en el vector City
	int index_A;
	int index_B;
	for (int j = 0; j < n_cities; j++) {
	    if (v[j] == min_arist.A) index_A = j;
	    else if (v[j] == min_arist.B) index_B = j;
	}

	bad_degree = deg.at(index_A) > 1 || deg.at(index_B) > 1;

	if (!bad_degree)
	{
	    res_arist.push_back(pair(index_A, index_B)); // Intentamos meter la siguiente arista con menos coste
	    
	    bool cycle = hay_ciclo(res_arist);

	    if (cycle && (i != n_edges-1))  // Si hemos metido un ciclo indebido, quitamos esa arista
		vec_todas_arist.pop_back();
	    else { // Si no, dejamos la arista y actualizamos el grado de las ciudades en el vector
		deg.at(index_A)++;
		deg.at(index_B)++;
	    }
	}
    }
}

int main() {
    std::vector<std::pair<int, int>> graph5 = { {4, 5}, {1, 3},{3, 4},{1, 5}};

    
    cout << boolalpha << hay_ciclo(graph5) << endl;
    return(0);
}
