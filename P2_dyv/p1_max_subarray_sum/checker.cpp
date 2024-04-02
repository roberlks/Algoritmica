#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/**
 * @brief Checks whether @p sub is in fact a subsequent of @p v
 * @param nsub size of @p sub
 * @param sub the presumptuos subsequent
 * @param n size of @p v
 * @param v the sequent
 * @return **true** if @p sub is in fact a subsequent of @p v ,**false** otherwise
*/
bool isSubsequent(int nsub, ll * sub,int n, ll * v){
    bool is_subsequent = true;
    for(int i=0; i<n-nsub; ++i){
        is_subsequent = true;
        for(int j=0,k=i; j<nsub; ++j,++k){
            if(v[k] != sub[j]){
                is_subsequent = false;
                break;
            }
        }
        if(is_subsequent)break;
    }
    return is_subsequent;
}

/**
 * @brief Reads an array (and its size) from a file
 * @param fin the file to read
 * @param n the size of the array
 * @param v the array
*/
void readArray(ifstream &fin, int & n, ll * & v){
    fin >> n;
    v = new ll[n];
    for(int i=0; i<n; ++i){
        fin >> v[i];
    }
}

/**
 * @brief Checks the solution for maximum_subarray_sum problem.
 * It checks that the solution given is in fact a subarray and
 * that its sum is the maximum one.
*/
int main(int argc, char * argv[]){
    if(argc < 4){
        cout << "Error missing arguments" << endl;
        return -1;
    }
    // Read files
    ifstream fin(argv[1]);
    ifstream ans(argv[2]);
    ifstream cor(argv[3]);

    if(!fin){
        cout << "Error opening input_file" << endl;
        cout << "ERROR: " << strerror(errno) << endl;
        return -1;
    }

    int n,nans,ncor;
    ll * v, *vans, *vcor;
    readArray(fin,n,v);
    readArray(ans,nans,vans);
    //readArray(cor,ncor,vcor);

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
    fin.close();ans.close();cor.close();
    return 0;
}
