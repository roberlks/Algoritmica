#include <bits/stdc++.h>
#include "../../../Include/City.h"
#include "../../../Include/Edge.h"

using namespace std;

// operator << for vector<City>
ostream& operator<<(ostream& os, vector<City> v) {
    for (int i=0; i < v.size(); i++) {
        os << v[i] << endl;
    }
    return os;
}

// operator << for vector<int>
ostream& operator<<(ostream& os, vector<int> v) {
    os << "[";
    for (int i=0; i < v.size()-1; i++) {
        os << v[i] << ", "; 
    }
    os << v[v.size()-1] << "]" << endl;
    return os;
}

ostream& operator<<(ostream& os, vector<pair<int,int>> v) {
    for (int i=0; i < v.size()-1; i++) {
        os << v[i].first << ", " << v[i].second << endl; 
    }
    os << v[v.size()-1].first << ", " << v[v.size()-1].second << endl; 
    return os;
}

ostream& operator<<(ostream& os, vector<Edge> v) {
    for (int i=0; i < v.size()-1; i++) {
        os << "["<<v[i].A << ", " << v[i].B << "]"<< endl; 
    }
    return os;
}

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
    for (int i = ini; i < fin; i++) {
	// para cada ciudad v[i], meto su arista con todas las
	// que no lo haya metido ya

	for (int j = i+1; j < fin; j++) {
	    vec_arist.push_back(Edge(v[i],v[j]));
	}
    }
}

// Función que junto con "hay_ciclo" reconocen
// si cierto puñao de enteros (que representan ciudades: índices en el vector)
// forman un ciclo

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
	if (f) {
	    sig = (*index).second; // El siguiente a buscar en la cadena
	}
	else {
	    sig = (*index).first;
	}

	if (sig == beg) // Hemos encontardo el que veníamos buscando 
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

bool hay_ciclo(vector<pair<int,int>> vec)
{
    // Es un ciclo si y solo
    // si podemos empezar en algun
    // nodo y terminar en ese mismo
    // siguiendo el camino que nos dan las aristas

    if (vec.size() > 0) {
	bool ciclo = false;
	for (int i = 0; i < vec.size() && !ciclo; i++) {
	    vector<pair<int,int>> v = vec; 
	    int beg_node = v.at(i).first; // Empezamos por el primero de cada arista
	    int sig = v.at(i).second;
	    auto it = v.begin() + i;
	    v.erase(it);
	    
	    ciclo =  busca_camino(v,sig,beg_node);
	}

	return ciclo;

    } else return true;
}


// Par de funciones bastante similare a las primeras
// (se podrá encapsular en otra función la búsqueda del elemento pero
// creo qu quedaría más confuso) pero que lo que hacen es pasar
// de una representación de aristas a una representación
// de vector ordenado de enteros el camino (ya con un ciclo)

void rellenar_ciclo(vector <pair<int,int>> v, vector<int> &path, int sig, int beg)
{
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

    if (!encontrado) {
	return;
    }
    else {
	if (f)
	    sig = (*index).second; // El siguiente a buscar en la cadena
	else 
	    sig = (*index).first;
	path.push_back(sig); // El que buscamos en la siguiente

	if (sig == beg) {// Hemos encontardo el que veníamos buscando 
	    return;
	}
	else {
	    v.erase(index); 
	    return rellenar_ciclo(v, path, sig, beg);
	}
    }
}

// Función que pasa un vector de aristas con un ciclo a un vector
// de índices 

void edges_to_vector(vector<pair<int,int>> v, vector<int> &path) 
{
    // Metemos el primer elemento y llamamos la función recursiva
    if (v.size() > 0) {
	int beg = v.at(0).first;
	int sig = v.at(0).second;

	path.push_back(beg);
	path.push_back(sig);
	v.erase(v.begin());
	rellenar_ciclo(v,path,sig,beg);
    }
}


void TSP_greedy_v3(int ini, int fin, City v[], vector<City> &path) {

    int n_cities = fin-ini; // Numero de ciudades
    vector<pair<int,int>> res_arist;

    // Guardamos en un vector todas las aristas y las ordenamos
    // por coste (dist euclídea en este caso, pues está implementado así el
    // operador <)

    vector<Edge> vec_todas_arist;
    fill_with_edges(ini,fin,v,vec_todas_arist);

    int n_edges = vec_todas_arist.size();
    sort(vec_todas_arist.begin(),vec_todas_arist.end());
    reverse(vec_todas_arist.begin(), vec_todas_arist.end());

    // cout << "VECTOR DE ARISTAS EN ORDEN DE CERCANÍA: " << endl;
    // cout << vec_todas_arist;

    vector<int> deg(n_cities); // Vector con los grados de cada ciudad

    int n = 0;
    bool bad_degree = false;


    for (int i = 0; (i < n_edges) && (res_arist.size() < n_cities); i++) {
	Edge min_arist = vec_todas_arist.at(i);
	// Tomamos los índices de las ciudades de la arista en el vector City
	int index_A;
	int index_B;
	for (int j = 0; j < n_cities; j++) {
	    if (v[j] == min_arist.A) index_A = j;
	    else if (v[j] == min_arist.B) index_B = j;
	}

	bad_degree = deg.at(index_A) > 1 || deg.at(index_B) > 1;

	//cout << "ARISTA: [" << index_A << ", " << index_B << "]" << endl;
	if (!bad_degree)
	{
	    //cout << " (GOOD DEGREE) INTENTO AÑADIR" << endl;
	    res_arist.push_back(pair(index_A, index_B)); // Intentamos meter la siguiente arista con menos coste
	    
	    bool cycle = hay_ciclo(res_arist);

	    if (cycle && (res_arist.size() != n_cities)) {
		//cout << "NO AÑADO PORQUE ME SALE CICLO ANTICIPADO" << endl;
		res_arist.pop_back();
	    }  // Si hemos metido un ciclo indebido, quitamos esa arista
	    else { // Si no, dejamos la arista y actualizamos el grado de las ciudades en el vector
		//cout << "AÑADO" << endl;
		deg.at(index_A)++;
		deg.at(index_B)++;
	    }
	}
    }  // for

    // Paso el vector final de aristas a un vector de índices y relleno el vector de ciudades
    vector<int> index_path;
    edges_to_vector(res_arist, index_path);
    for (int i = 0; i < index_path.size(); i++)
	path.push_back(v[index_path[i]]);
    path.push_back(v[index_path[0]]);
}


int main(int argc, char** argv) {
    // Faster I/O
    ios::sync_with_stdio(false);

    if (argc < 2) {
        cout << "Uso: ./greedy <input_file>" << endl;
        return 1;
    }

    // INPUT

    ifstream fin(argv[1], ios::in);
    int n;
    fin >> n;
    City v[n];
    for(int i=0; i<n; ++i)
        fin >> v[i];

    // Answer
    vector<City> ans;
    ans.reserve(n);

    // TSP
    TSP_greedy_v3(0,n,v,ans);

    // OUTPUT

    #ifdef TSP
    cout << ans << endl;
    #endif

    #ifdef COST
    cout << n << " " << cycleDistance(ans,cities) << endl;
    #endif

    #ifdef TIME
    cout << n << " " << ((double)(t_after - t_before)/CLOCKS_PER_SEC) << endl;
    #endif
}
