#include <iostream>
using namespace std;

typedef long long ll;

const int UMBRAL = 1;

struct index{
    ll val,ini,fin;
    index(ll val = 0, ll ini  = 0, ll fin = 0) : val(val), ini(ini), fin(fin) {}
};

struct tupla
{
    index mcss,max_prefix,max_sufix;
    ll total;

    tupla(index mcss = index(), index p = index(), index s = index(), ll t = 0) :
     mcss(mcss), max_prefix(p), max_sufix(s), total(t) {}
};

tupla lineal(int ini, int fin, ll a[]){
    tupla ans;
    for(int i=ini; i<fin; ++i){
        
        ans.total += a[i];
    }
}

tupla dyv(int ini, int fin, ll a[]){
    // Base case
    if(fin - ini <= UMBRAL){
        return tupla(index(a[ini],ini,fin),index(a[ini],ini,fin),index(a[ini],ini,fin),a[ini]);
    }

    // Divide 
    int mid = (fin + ini)/2;
    tupla t1,t2;
    t1 = dyv(ini,mid,a);
    t2 = dyv(mid,fin,a);

    // Fusion
    tupla ans;

    // mcss
    // mcss is the maximum of the solution of both sides and the sufix of the left side combined with
    // the prefix of the right side

    // ans.mcss = max(max(t1.mcss,t2.mcss),t1.max_sufix + t2.max_prefix)
    if(t1.mcss.val > t2.mcss.val){ // ans.mcss = max(t1.mcss, t2.mcss)
        ans.mcss = t1.mcss;
    }else{
        ans.mcss = t2.mcss;
    }
    if(t1.max_sufix.val + t2.max_prefix.val > ans.mcss.val){
        ans.mcss = t1.max_sufix.val + t2.max_prefix.val;
        ans.mcss.ini = t1.max_sufix.ini;
        ans.mcss.fin = t2.max_prefix.fin;
    }

    // max_prefix
    // max_prefix is the maximum between the max_prefix of the left side 
    // and the whole of the left side plus the max_prefix of the right side
    if(t1.max_prefix.val > t1.total + t2.max_prefix.val){
        ans.max_prefix = t1.max_prefix;
    }else{
        ans.max_prefix.val = t1.total + t2.max_prefix.val;
        ans.max_prefix.ini = ini;
        ans.max_prefix.fin = t2.max_prefix.fin;
    }

    // max_sufix
    // max_sufix is the maximum between the max_sufix of the right side 
    // and the whole of the right side plus the max_sufix of the left side
    if(t2.max_sufix.val > t2.total + t1.max_sufix.val){
        ans.max_sufix = t2.max_sufix;
    }else{
        ans.max_sufix.val = t2.total + t1.max_sufix.val;
        ans.max_sufix.ini = t1.max_sufix.ini;
        ans.max_sufix.fin = fin;
    }

    // total
    // total is the total sum of both sides
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

    // MCSS
    index ans = dyv(0,n,a).mcss;
    
    // OUTPUT
    cout << ans.fin-ans.ini << endl;
    for(int i=ans.ini; i<ans.fin; ++i)
        cout << a[i] << " ";
    cout << endl;
}