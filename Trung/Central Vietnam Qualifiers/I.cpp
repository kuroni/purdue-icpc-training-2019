#include <bits/stdc++.h>
using namespace std;

const int N = 4E5, LG = 17;

int n, q, u, a[N], rmq[N][LG];
map<int, long long> ma;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rmq[i][0] = a[i];
    }
    for (int j = 1; j < LG; j++) {
        for (int i = 1; i <= n; i++) {
            rmq[i][j] = __gcd(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int pt = i, cur = 0;
        while (pt <= n) {
            cur = __gcd(cur, a[pt]);
            ma[cur] -= pt;
            for (int j = LG - 1; j >= 0; j--) {
                if (pt + (1 << j) - 1 <= n && rmq[pt][j] % cur == 0) {
                    pt += (1 << j);
                }
            }
            ma[cur] += pt;
        }
    }
    cin >> q;
    while (q--) {
        cin >> u;
        cout << ma[u] << '\n';
    }
}
