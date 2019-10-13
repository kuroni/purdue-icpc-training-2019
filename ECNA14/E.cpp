#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 305, INF = 10005;

int q, n, s, t, u, cnt, ans = 0, tr[N], dst[N], pot[N];
int co[N * N], we[N * N], xo[N * N];
vector<pair<int, int>> adj[N];
bool vis[N];

void add_edge(int u, int v, int c, int w) {
    adj[u].push_back({v, cnt});
    co[cnt] = c; we[cnt] = w; xo[cnt] = u ^ v;
    cnt++;
    adj[v].push_back({u, cnt});
    co[cnt] = -c; we[cnt] = 0; xo[cnt] = u ^ v;
    cnt++;
}

void dijkstra() {
    fill(vis, vis + t + 1, false);
    fill(dst, dst + t + 1, INF);
    dst[s] = 0;
    while (true) {
        pair<int, int> mi = {INF, -1};
        for (int i = s; i <= t; i++) {
            if (!vis[i]) {
               mi = min(mi, {dst[i], i});
            }
        }
        int u = mi.se;
        if (u == -1) {
            break;
        }
        vis[u] = true;
        for (pair<int, int> &v : adj[u]) {
            if (we[v.se] > 0) {
                int tmp = dst[u] + pot[u] + co[v.se] - pot[v.fi];
                if (tmp < dst[v.fi]) {
                    dst[v.fi] = tmp;
                    tr[v.fi] = v.se;
                }
            }
        }
    }
}

void trace() {
    int u = t;
    while (u != s) {
        int ind = tr[u];
        we[ind]--; we[ind ^ 1]++;
        u ^= xo[ind];
    }
    for (int i = s; i <= t; i++) {
        pot[i] += dst[i];
    }
}

void solve() {
    cin >> n;
    s = 0; t = 2 * n + 1; cnt = 0; ans = 0;
    for (int i = s; i <= t; i++) {
        adj[i].clear();
        pot[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        add_edge(s, i, 0, 1);
        add_edge(i + n, t, 0, 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> u;
            add_edge(i, j + n, u, 1);
            add_edge(j, i + n, u, 1);
         }
    }
    for (int i = 1; i <= n; i++) {
        dijkstra();
        trace();
        ans += pot[t];
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
}