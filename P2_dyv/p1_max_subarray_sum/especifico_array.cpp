struct index{
    ll val,ini,fin;
    index(ll val = 0, ll ini  = 0, ll fin = 0) : val(val), ini(ini), fin(fin) {}

    friend bool operator<(const index & a,const index & b){
        return a.val < b.val;
    }

    friend ostream & operator<<(ostream & os, const index & ind){
        os << ind.val << " [" << ind.ini << ", " << ind.fin << "]"; 
        return os;
    }
};

struct tupla
{
    index mcss,max_prefix,max_sufix;
    ll total;

    tupla(index mcss = index(), index p = index(), index s = index(), ll t = 0) :
     mcss(mcss), max_prefix(p), max_sufix(s), total(t) {}

    friend ostream & operator<<(ostream & os, const tupla & t){
        os << "mcss: " << t.mcss << endl;
        os << "max_prefix: " << t.max_prefix << endl;
        os << "max_sufix: " << t.max_sufix << endl;
        os << "total: " << t.total;
        return os;
    }
};

tupla lineal(int ini, int fin, ll a[]){
    tupla ans;
    // Initialise mcss and max_prefix to the first element of the array
    ans.mcss.ini = ans.max_prefix.ini = ini;
    ans.mcss.val = ans.max_prefix.val = a[ini];
    ans.mcss.fin = ans.max_prefix.fin = ini+1;
    ll ac = 0; // Accumulator
    int loc_ini = 0;
    ll max_array_ind = 0; // Index of the maximum element of the array
    for(int i=ini; i<fin; ++i){
        ac += a[i];
        if(ac < 0){ // If the accumulator is negative, we reset it (as well as the local starting position)
            ac = 0;
            loc_ini = i+1;
        }
        if(ac > ans.mcss.val){ // If the accumulator is greater than the current mcss, then it is updated
            ans.mcss.val = ac;
            ans.mcss.fin = i+1;
            ans.mcss.ini = loc_ini;
        }
        if(a[max_array_ind] < a[i]){ // Calculating index of the maximum element of the array
            max_array_ind = i;
        }
        ans.total += a[i]; // Calculating total of the array
        if(ans.total > ans.max_prefix.val){ // If the current total of the array [0,i] is greater than max_prefix, then it is updated
            ans.max_prefix.val = ans.total;
            ans.max_prefix.fin = i+1;
        }
    }

    if(!ans.mcss.val){ // If mcss is 0, then all the array is negative and mcss is the maximum element of the array
        ans.mcss.ini = max_array_ind;
        ans.mcss.fin = max_array_ind+1;
        ans.mcss.val = a[max_array_ind];
    }

    // Initialise max_sufix to the last element of the array
    ans.max_sufix.val = a[fin-1];
    ans.max_sufix.ini = fin-1;
    ans.max_sufix.fin = fin;
    ll sum = 0;
    for(int i=fin-1; i>=ini; --i){
        sum += a[i]; // Calculating sum of [i,fin)
        if(sum > ans.max_sufix.val){ // If [i,fin) is greater than max_sufix, then it is updated
            ans.max_sufix.val = sum;
            ans.max_sufix.ini = i;
        }
    }

    return ans;
}