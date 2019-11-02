#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, f[N], dsu[N];
long long p[N], m[N], s[N], ans = 0;
vector<int> ve;

int trace(int u) {
    return dsu[u] < 0 ? u : dsu[u] = trace(dsu[u]);
}

bool connect(int u, int v) {
    if ((u = trace(u)) == (v = trace(v))) {
        return false;
    }
    if (dsu[u] > dsu[v]) {
        swap(u, v);
    }
    dsu[u] += dsu[v];
    dsu[v] = u;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> f[i] >> p[i] >> m[i] >> s[i];
        dsu[i] = -1;
        ve.push_back(i);
    }
    sort(ve.begin(), ve.end(), [&](const int &u, const int &v) {
        return m[f[u]] - p[u] > m[f[v]] - p[v];
    });
    for (int &u : ve) {
        if (m[f[u]] - p[u] <= 0) {
            break;
        }
        long long pro = m[f[u]] - p[u];
        if (s[f[u]] >= 1) {
            ans += pro * (s[f[u]] - 1);
            s[f[u]] = 1;
            if (u == f[u] || connect(u, f[u])) {
                ans += pro;
                s[f[u]] = 0;
            }
        }
    }
    cout << ans;
}
