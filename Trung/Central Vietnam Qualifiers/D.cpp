#include <bits/stdc++.h>
using namespace std;

const int N = 1E5 + 5, MX = 1E6 + 5;

int n, u, cur, bit[2 * N];
long long ans = 0;
bool pr[MX];

void update(int u) {
    for (; u <= 2 * n + 1; u += u & -u) {
        bit[u]++;
    }
}

int query(int u) {
    int ret = 0;
    for (; u > 0; u -= u & -u) {
        ret += bit[u];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(pr + 2, pr + MX, true);
    for (int i = 2; i * i < MX; i++) {
        if (pr[i]) {
            for (int j = i * i; j < MX; j += i) {
                pr[j] = false;
            }
        }
    }
    cin >> n;
    cur = n + 1;
    update(cur);
    for (int i = 1; i <= n; i++) {
        cin >> u;
        cur += (pr[u] ? 1 : -1);
        ans += query(cur);
        update(cur);
    }
    cout << ans;
}
