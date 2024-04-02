#include <bits/stdc++.h>
using namespace std;

const int sx[4] = {1,-1,0,0};
const int sy[4] = {0,0,1,-1};

bool validPos(int x, int y, int n){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool isL(int x, int y,const vector<vector<int>> & v,int n){
    if(v[x][y] < 0) return false;
    int cont = 0;
    for(int i=0; i<4; ++i){
        int nx = x + sx[i];
        int ny = y + sy[i];
        if(validPos(nx,ny,n)){
            if(v[x][y] == v[nx][ny])
                ++cont;
        }
    }
    if(!v[x][y]) return cont == 0;
    return 1 <= cont <= 2;
}

/**
 * @brief Checks the solution for L-shapes.
 * Checks that the square tile is in the correct place and the rest is fill 
 * with L.
*/
int main(int argc, char * argv[]){
    if(argc < 3){
        cout << "Error missing arguments" << endl;
        return -1;
    }
    // Read files
    ifstream fin(argv[1]);
    ifstream ans(argv[2]);
    int n,r,c;
    fin >> n >> r >> c;
    r--;c--;
    vector<vector<int>> v(n,vector<int>(n));
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            ans >> v[i][j];
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    if(v[r][c]){
        cout << "WA: square tile not found where it was supposed to be" << endl;
        return -1;
    }

    bool allL = true;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            allL = isL(i,j,v,n);
            if(!allL) break;
        }
        if(!allL) break;
    }

    if(!allL){
        cout << "WA: not all L" << endl;
        return -1;
    }

    return 0;
}