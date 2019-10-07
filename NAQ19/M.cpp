#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, w, g, h, r;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    cout << fixed << setprecision(8);
    for(int i = 0; i < n; i++) {
        cin >> w >> g >> h >> r;
        g -= r;
        h -= r;
        double M = hypot(w, g - h);
        double m = hypot(g + h, w);
        cout << M << " " << m << endl;
    }
}