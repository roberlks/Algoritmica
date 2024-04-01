#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool isSubsequent(int nsub, ll * sub,int n, ll * v){
    bool is_subsequent = true;
    for(int i=0; i<n-nsub; ++i){
        is_subsequent = true;
        int k=i;
        for(int j=0; j<nsub; ++j,++k){
            if(v[k] != sub[j]){
                is_subsequent = false;
                break;
            }
        }
        if(is_subsequent)break;
    }
    return is_subsequent;
}

void readFile(ifstream &fin, int & n, ll * v){
    fin >> n;
    v = new ll[n];
    for(int i=0; i<n; ++i){
        fin >> v[i];
    }
}

int main(){
    // Read files
    ifstream fin("input_file");
    ifstream ans("myAnswer");
    ifstream cor("correctAnswer");

    int n,nans,ncor;
    ll * v, *vans, *vcor;
    readFile(fin,n,v);
    readFile(ans,nans,vans);
    //readFile(cor,ncor,vcor);

    // Check valid subsequent
    if(!isSubsequent(nans,vans,n,v)){
        cout << "WA: Not a valid subsequent" << endl;
        return -1;
    }

    // Check correct sum
    ll ans_sum = 0;
    for(int i=0; i<nans; ++i)
        ans_sum += vans[i];
    ll cor_sum = 0;
    //for(int i=0; i<ncor; ++i)
    //    cor_sum += vcor[i];
    cor >> cor_sum;
    
    if(ans_sum != cor_sum){
        cout << "WA: not the maximum sum" << endl;
        return -1;
    }
    return 0;
}
