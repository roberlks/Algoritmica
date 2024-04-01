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