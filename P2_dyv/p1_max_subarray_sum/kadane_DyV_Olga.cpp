#include <iostream>

using namespace std;

struct Solucion {
    int pos_izq;        // Inclusive
    int pos_der;        // Descartable
    int sum;

    Solucion(int pos_izq, int pos_der, int sum):
        pos_izq(pos_izq), pos_der(pos_der),sum(sum) {};
};


Solucion solucionDYV(int* v, int init, int final) {
    
    if (final- init <= 1) {
        return Solucion(init, final, v[init]);
    }
    else {

        int middle = (final + init)/2;
        
        Solucion sol_izq = solucionDYV(v, init, middle);
        Solucion sol_der = solucionDYV(v, middle, final);


        //Combinar solución

        Solucion max_sum = sol_izq;
        Solucion ac = sol_izq;

        for(int i = sol_izq.pos_der; i < sol_der.pos_izq; i ++) {
            
            if (ac.sum < 0) {
                ac.pos_izq = i;
                ac.pos_der = i+1;
                ac.sum = v[i];
            }
            else {
                ++ac.pos_der;
                ac.sum += v[i];
            }
            
            if (ac.sum > max_sum.sum) {
                max_sum = ac;
            }
        }

        if (ac.sum < 0) {
            ac = sol_der;
        }
        else {
            ac.pos_der = sol_der.pos_der;
            ac.sum += sol_der.sum;
        }
        
        if (ac.sum > max_sum.sum) {
            max_sum = ac;
        }

        return max_sum;
    }
}

int main() {
    int n;  //número de datos a meter 
    cin >> n;

    int* vector = new int[n];

    for (int i= 0; i < n; i++) {
        cin >> vector[i];
    }

    cout << solucionDYV(vector, 0, n).sum;

    delete vector;
    return 0;
}