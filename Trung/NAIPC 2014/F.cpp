#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 40, INF = 1E9 + 7;

int n, m, u, v, ans = 0, a[N], b[N], dis[N], dst[N];
bool vis[N], chk[N];
vector<int> adj[N], tr[N];

void BFS() {
    fill(dis + 1, dis + n + 1, -1);
    dis[1] = 1;
    queue<int> q;
    for (q.push(1); !q.empty(); q.pop()) {
        int u = q.front();
        for (int &v : adj[u]) {
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
            if (dis[v] == dis[u] + 1) {
                tr[v].push_back(u);
            }
        }
    }
}

int dijkstra() {
    fill(dst + 1, dst + n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dst[1] = 0, 1});
    while (!pq.empty()) {
        pair<int, int> u = pq.top(); pq.pop();
        if (u.fi > dst[u.se]) {
            continue;
        }
        if (u.se == 2) {
            return u.fi;
        }
        for (int &v : adj[u.se]) {
            if (dst[v] > u.fi + b[v]) {
                pq.push({dst[v] = u.fi + b[v], v});
            }
        }
    }
}

void solve(int u, int cur = 0) {
    if (u == 1) {
        ans = max(ans, cur - dijkstra());
        return;
    }
    b[u] = a[u];
    for (int &v : tr[u]) {
        solve(v, cur + a[v]);
    }
    b[u] = 0;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 3; i <= n; i++) {
        cin >> a[i];
    }
    while (m--) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    BFS();
    solve(2);
    cout << ans;
}
