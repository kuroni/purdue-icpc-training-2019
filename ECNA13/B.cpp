#include <bits/stdc++.h>
using namespace std;
 
const int N = 1005;
 
int te = 0, n[2], m, u, pos[2][N];
 
void solve() {
    fill(pos[0], pos[0] + n[0], -1);
    fill(pos[1], pos[1] + n[1], -1);
    while (m--) {
        cin >> u;
        for (int i = 0; ; i ^= 1) {
            if (pos[i][u % n[i]] == -1) {
                pos[i][u % n[i]] = u;
                break;
            } else {
                swap(pos[i][u % n[i]], u);
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (*max_element(pos[i], pos[i] + n[i]) > -1) {
            cout << "Table " << i + 1 << '\n';
        }
        for (int j = 0; j < n[i]; j++) {
            if (pos[i][j] != -1) {
                cout << j << ":" << pos[i][j] << '\n';
            }
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n[0] >> n[1] >> m, m != 0) {
        cout << "Case " << ++te << ":\n";
        solve();
    }
}
