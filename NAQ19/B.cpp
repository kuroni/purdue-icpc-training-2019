#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll m, n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    ll g = __gcd(m, n);
    if((m / g) % 2 == 0 || (n / g) % 2 == 0) {
        cout << 0 << endl;
    }else {
        cout << g << endl;
    }
}