#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// For easy debugging
#define D(x) cerr << #x << ": " << x << endl;

const int UMBRAL = 2;

/**
 * @brief Extended version of add_slab, which not only adds 1x1 L's,
 * it also adds @p m x @p m L's, comorientationed by 4 @p m - 1 x @p m - 1 L's 
*/
void add_slab_m(vector<vector<int>> & v, int m, int i, int j, int orientation, int & slab)
{
    // Variables para calcular dónde y cómo habrá que colocar las eles en el
    // nivel actual m
    int inc_i = 1, inc_j = 1;
    if (orientation % 2 == 1)
    {
        inc_j = -1;
    }
    if (orientation / 2 == 1)
    {
        inc_i = -1;
    }

    // Caso base
    if (m == 1)
    {
        v[i][j + inc_j] = v[i + inc_i][j] = v[i + inc_i][j + inc_j] = slab;
        ++slab;
    }
    else
    {
        // Se puede hacer con un switch de orientation
        // 0 --> 1 2
        // 1 --> 0 3
        // 2 --> 3 0
        // 3 --> 2 1
        int orientation1 = orientation + inc_j;
        int orientation2 = 3 - orientation1;

        inc_i *= (m/2);
        inc_j *= (m/2);

        // Ele interior

        // Colocar en (i,j) con posición original
        add_slab_m(v, m / 2, i, j, orientation, slab);

        // Eles de los extremos

        // Colocar esquinas en posiciones calculadas, con orientation1 y orientation2, según valor de orientation
        // (i +- m/2, j -+ m/2 +- 1)
        // (i -+ m/2 +- 1, j +- m/2)
        add_slab_m(v, m / 2, i + inc_i, j - inc_j + (abs(inc_j)/inc_j), orientation1, slab);
        add_slab_m(v, m / 2, i - inc_i + (abs(inc_i)/(inc_i)), j + inc_j, orientation2, slab);

        // Colocar en (i +- m/2, j +- m/2) con posición original
        add_slab_m(v, m / 2, i + inc_i, j + inc_j, orientation, slab);
    }
}

/**
 * 2x2 e.g
 * 0 tile tile
 * r .    tile
 *   c      1
*/
void lineal(int n,int r, int c,int start_row, int start_col, vector<vector<int>> & v,int & tile){
    // for(int i=start_row; i<start_row+n; ++i){
    //     for(int j=start_col; j<start_col+n; ++j){
    //         if(i == r && j == c) continue; // Already filled
    //         v[i][j] = tile;
    //     }
    // }
    // ++tile;

    for (int m = 1; m < n; m *= 2)
    {
        // Cálculo de la orientación según dónde esté el hueco del nivel actual m
        int orientation = 2*((r/m) % 2) + ((c/m) % 2);

        // Escalar la posición del hueco
        int i = (r / m)*m; 
        int j = (c / m)*m;

        // Calcular la posición a insertar la L
        int inc_i = 0, inc_j = 0;
        if (orientation % 2 == 0)
        {
            inc_j = m - 1;
        }
        if (orientation / 2 == 0)
        {
            inc_i = m - 1;
        }
        i += inc_i;
        j += inc_j;
        
        // Insertar la L
        add_slab_m(v, m, i, j, orientation, tile); 
    }
}

const int sx[4]={1,1,0,0};
const int sy[4]={1,0,1,0};

void dyv(int n,int r, int c,int start_row, int start_col, vector<vector<int>> & v,int & tile){
    if(n <= UMBRAL){
        lineal(n,r,c,start_row,start_col,v,tile);
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
    cin >> n >> r >> c;
    r--;c--;
    vector<vector<int>> v(n,vector<int>(n));
    int start_tile = 0;
    v[r][c] = start_tile++;
    dyv(n,r,c,0,0,v,start_tile);

    // OUTPUT
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout << setw(3) << v[i][j] << " ";
        }
        cout << endl;
    }
    // Codeforces's Output (for testing)
    // https://codeforces.com/problemset/gymProblem/101845/L
    /*for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(!v[i][j]){
                cout << ".";
            }else{
                cout << (char)((v[i][j]%26) + 'A');
            }
        }
        cout << endl;
    }*/
}