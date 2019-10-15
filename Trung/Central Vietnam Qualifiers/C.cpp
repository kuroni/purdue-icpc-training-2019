#include <bits/stdc++.h>
using namespace std;

int n, x, y, z, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    while (n--) {
        cin >> x >> y >> z >> t;
        cout << (__gcd(abs(x), abs(y)) == __gcd(abs(z), abs(t)) ? "YES\n" : "NO\n");
    }
}
