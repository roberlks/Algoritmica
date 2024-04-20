#include <bits/stdc++.h>
#include "../../../Include/City.h"
using namespace std;

// operator << for vector<City>
ostream& operator<<(ostream& os, vector<City> v) {
    for (int i=0; i < v.size(); i++) {
        os << v[i] << endl;
    }
    return os;
}

void TSP_greedy_v2() {

}

int main(int argc, char** argv) {
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    City v[n];
    for(int i=0; i<n; ++i)
        cin >> v[i];

    // Answer
    vector<City> ans;
    ans.reserve(n);

    // TSP
    TSP_greedy_v2();

    // OUTPUT
    cout << ans << endl;
}