#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
 
const int N = 30, MX = 630000, DX[5] = {1, 0, -1, 0, 0}, DY[5] = {0, 1, 0, -1, 0};
 
int n, m, mt, te = 0, st = 0, en = 1, tim[MX], tr[MX];
char s[N][N];
bool vis[MX];
vector<bool> w;
vector<int> val;
vector<pair<int, int>> adj[MX];
 
int node(int x, int y, int g, int t) {
    return x * n * 2 * mt + y * 2 * mt + g * mt + t + 2;
}
 
bool check(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        return false;
    }
    return s[x][y] == '.';
}
 
void add_edge(int u, int v) {
    adj[u].push_back({v, m++});
    val.push_back(u ^ v);
    w.push_back(true);
    adj[v].push_back({u, m++});
    val.push_back(u ^ v);
    w.push_back(false);
}
 
void init() {
    w.clear(); val.clear(); m = 0;
    mt = 500;
    adj[st].clear(); adj[en].clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int g = 0; g < 2; g++) {
                for (int t = 0; t < mt; t++) {
                    adj[node(i, j, g, t)].clear();
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!check(i, j)) {
                continue;
            }
            for (int t = 0; t < mt; t++) {
                add_edge(node(i, j, 0, t), node(i, j, 1, t));
                tim[node(i, j, 0, t)] = tim[node(i, j, 1, t)] = t;
                for (int k = 0; k < 5; k++) {
                    if (check(i + DX[k], j + DY[k]) && t + 1 < mt) {
                        add_edge(node(i, j, 1, t), node(i + DX[k], j + DY[k], 0, t + 1));
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        add_edge(st, node(i, 0, 0, 0));
    }
}
 
bool DFS(int u, int des, int lst = -2) {
    vis[u] = true;
    tr[u] = lst;
    if (u == en) {
        return true;
    }
    for (pair<int, int> &v : adj[u]) {
        if (tim[v.fi] <= des && !vis[v.fi] && w[v.se] && DFS(v.fi, des, v.se)) {
            return true;
        }
    }
    return false;
}
 
void trace() {
    int u = en;
    while (u != st) {
        int ind = tr[u];
        swap(w[ind], w[ind ^ 1]);
        u ^= val[ind];
    }
}
 
bool valid(int mi) {
    for (pair<int, int> &v : adj[en]) {
        m -= 2;
        val.pop_back(); val.pop_back();
        w.pop_back(); w.pop_back();
        adj[v.fi].pop_back();
    }
    adj[en].clear();
    for (int i = 0; i < m; i += 2) {
        w[i] = true; w[i ^ 1] = false;
    }
    for (int i = 0; i < n; i++) {
        add_edge(node(i, n - 1, 1, mi), en);
    }
    for (int i = 0; i < n; i++) {
        fill(vis, vis + node(n - 1, n - 1, 1, mi) + 1, false);
        if (!DFS(st, mi)) {
            return false;
        }
        trace();
    }
    return true;
}
 
void solve() {
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    init();
    int le = 0, ri = mt - 1;
    while (le <= ri) {
        int mi = (le + ri) / 2;
        if (valid(mi)) {
            ri = mi - 1;
        } else {
            le = mi + 1;
        }
    }
    cout << "Case " << ++te << ": " << le << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n, n != 0) {
        solve();
    }
}
