#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
using namespace std;

// For easy debugging
#define D(x) cerr << #x << ": " << x << endl;

const int UMBRAL = 1;

const int sx[4]={1,1,0,0};
const int sy[4]={1,0,1,0};

void dyv(int n,int r, int c,int start_row, int start_col, vector<vector<int>> & v,int & tile){

    if(n <= UMBRAL){
        return;
    }

    // Divide in 4 (n is always a power of 2)
    int mid = n/2;
    int t = tile++;

    // Locate (r,c) square and put L-shape tile on the center (excluding (r,c) square)
    for(int i=0; i<4; ++i){
        // New starting row and col of the square (midxmid)
        int new_start_row = start_row + sx[i]*mid;
        int new_start_col = start_col + sy[i]*mid;
        // Locate (r,c) square
        if(new_start_row <= r && r < new_start_row + mid && new_start_col <= c && c < new_start_col + mid){
            dyv(mid,r,c,new_start_row,new_start_col,v,tile);
        }else{
            // Fill the center with an L-shape and set the new square tile
            int nr = start_row + mid - 1 + sx[i];
            int nc = start_col + mid -1 + sy[i];
            v[nr][nc] = t;
            dyv(mid,nr,nc,new_start_row,new_start_col,v,tile);
        }
    }
}

int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n,r,c; // n-size of the square (power of 2), (r,c) -> position of the square tile

    // Se toma r,c un valor entre [1,n]

    
    cin >> n >> r >> c;
    r--; c--;
    vector<vector<int>> v(n,vector<int>(n));
    int start_tile = 0;
    v[r][c] = start_tile++;

    // Estudio eficiencia empírica, calculo de tiempos

    chrono::high_resolution_clock::time_point t_antes, t_despues; 
    chrono::duration<double> transcurrido;

    t_antes = chrono::high_resolution_clock::now();

    dyv(n,r,c,0,0,v,start_tile);

    t_despues = chrono::high_resolution_clock::now();

    transcurrido = chrono::duration_cast<chrono::duration<double>>(t_despues-t_antes);

    cout << endl << setw(10) << left << n << " " << transcurrido.count();
    
    // OUTPUT

    /*
    cout << endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout << setw(3) << v[i][j] << " ";
        }
        cout << endl;
    }

    */

   
}