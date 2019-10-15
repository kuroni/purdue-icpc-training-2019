#include <bits/stdc++.h>
using namespace std;

const int MX = 1E6 + 5;

int q, u, eu[MX];
bool chk[MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 1; i < MX; i++) {
        eu[i] = i;
    }
    for (int i = 2; i < MX; i++) {
        if (eu[i] == i) {
            for (int j = i; j < MX; j += i) {
                (eu[j] /= i) *= (i - 1);
            }
        }
    }
    for (int i = 1; i < MX; i++) {
        int lg = log10(i) + 1;
        if (!chk[i - 1] || !chk[i - eu[i]] || !chk[i - lg]) {
            chk[i] = true;
        }
    }
    cin >> q;
    while (q--) {
        cin >> u;
        cout << (chk[u] ? "BACH\n" : "KHOA\n");
    }
}
