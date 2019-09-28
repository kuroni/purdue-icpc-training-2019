#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, u, v, a[N], f[N][2];
vector<int> adj[N];

void DFS(int u, int p = -1) {
    f[u][1] = a[u];
    for (int &v : adj[u]) {
        if (v != p) {
            DFS(v, u);
            f[u][0] += max(f[v][0], f[v][1]);
            f[u][1] += f[v][0];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DFS(0);
    cout << max(f[0][0], f[0][1]);
}
