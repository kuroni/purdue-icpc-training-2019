#include <bits/stdc++.h>
using namespace std;
 
const int MX = 205;
 
int m, n, te = 0, pos[MX];
bool vis[MX];
string u, v;
vector<int> tpo, adj[MX];
map<string, int> ma;
vector<string> nam;
vector<pair<string, string>> ans;
 
void DFS(int u, bool so = false) {
    vis[u] = true;
    for (int &v : adj[u]) {
        if (!vis[v]) {
            DFS(v, so);
        }
    }
    if (so) {
        tpo.push_back(u);
    }
}
 
int index(string u) {
    if (!ma.count(u)) {
        ma[u] = n++;
        nam.push_back(u);
    }
    return ma[u];
}
 
void solve() {
    ma.clear(); tpo.clear(); nam.clear(); ans.clear();
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        vis[i] = false;
    }
    n = 0;
    while (m--) {
        cin >> u >> v;
        adj[index(u)].push_back(index(v));
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            DFS(i, true);
        }
    }
    reverse(tpo.begin(), tpo.end());
    for (int i = 0; i < n; i++) {
        pos[tpo[i]] = i;
    }
    for (int &u : tpo) {
        fill(vis, vis + MX, false);
        sort(adj[u].begin(), adj[u].end(), [&](const int &a, const int &b) {
            return pos[a] < pos[b];
        });
        for (int &v : adj[u]) {
            if (vis[v]) {
                ans.push_back({nam[u], nam[v]});
            } else {
                DFS(v);
            }
        }
    }
    cout << ans.size() << ' ';
    sort(ans.begin(), ans.end());
    for (pair<string, string> &v : ans) {
        cout << v.first << "," << v.second << ' ';
    }
    cout << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> m, m != 0) {
        cout << "Case " << ++te << ": ";
        solve();
    }
}
