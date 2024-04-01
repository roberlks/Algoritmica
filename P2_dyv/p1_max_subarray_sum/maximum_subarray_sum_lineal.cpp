#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll kadane(int n, ll a[]){
    ll tot_max = a[0];
    ll cur_max = a[0];
    for(int i=1; i<n; ++i){
        cur_max = max(a[i],cur_max+a[i]);
        if(cur_max > tot_max){
            tot_max = cur_max;
        }
    }
    return tot_max;
}

// Olga's algoritm
ll mss_value_lineal(int n, ll a[]){
    ll mx = a[0]; // max subarray sum
    ll ac = 0; // accumulator
    ll array_mx = a[0]; // global individual max of the array
    for(int i=0; i<n; ++i){
        ac += a[i];
        if(ac < 0) ac = 0;
        if(ac > mx) mx = ac;
        if(a[i] > array_mx) array_mx = a[i];
    }
    // If the whole array is negative
    if(!mx) mx = array_mx;
    return mx;
}

void mss_subarray_lineal(int n, ll a[], int & ini, int & fin){
    ll mx = a[0]; // max subarray sum
    ll ac = 0; // accumulator
    int array_mx = 0; // global individual max of the array (index)
    ini = fin = 0;
    int loc_ini = 0;
    for(int i=0; i<n; ++i){
        ac += a[i];
        if(ac < 0) {
            ac = 0;
            loc_ini = i;
        }
        if(ac > mx){ 
            mx = ac;
            fin = i;
            ini = loc_ini;
        }
        if(a[i] > array_mx) 
            array_mx = a[i];
    }
    // If the whole array is negative
    if(!mx) {
        mx = a[array_mx];
        ini = fin = array_mx;
    }
}

int main(){
    // Faster I/O (can be removed)
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    ll a[n];
    for(int i=0; i<n; ++i) cin >> a[i];
    
    
    // OUTPUT
    cout << kadane(n,a) << endl;
}