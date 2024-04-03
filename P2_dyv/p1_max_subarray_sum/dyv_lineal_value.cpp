#include <iostream>
using namespace std;

typedef long long ll;

const int UMBRAL = 1;

struct tupla
{
    ll mcss,max_prefix,max_sufix,total;

    tupla(ll mcss = 0, ll p = 0, ll s = 0, ll t = 0) :
     mcss(mcss), max_prefix(p), max_sufix(s), total(t) {}

    friend ostream & operator<<(ostream & os, const tupla & t){
        os << "(" << t.mcss << ", " << t.max_prefix << ", " << t.max_sufix << ", " << t.total << ")";
        return os;
    }
};

tupla dyv_value(int ini, int fin, ll a[]){
    // Base case
    if(fin - ini <= UMBRAL){
        return tupla(a[ini],a[ini],a[ini],a[ini]);
    }

    // Divide 
    int mid = (fin + ini)/2;
    tupla t1,t2;
    t1 = dyv_value(ini,mid,a);
    t2 = dyv_value(mid,fin,a);

    // Fusion
    tupla ans;
    ans.mcss = max(max(t1.mcss,t2.mcss),t1.max_sufix + t2.max_prefix);
    ans.max_prefix = max(t1.max_prefix,t1.total+t2.max_prefix);
    ans.max_sufix = max(t2.max_sufix,t2.total+t1.max_sufix);
    ans.total = t1.total + t2.total;

    return ans;
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
    // https://cses.fi/problemset/task/1643/
    cout << dyv_value(0,n,a).mcss << endl;
}