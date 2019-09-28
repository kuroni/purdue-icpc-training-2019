#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 105, MX = 305, INF = 1E9 + 7;

int n, m, s, t, u, v, w, y, g[N], r[N], sum[N];
int dis[N];
vector<pair<int, int>> adj[N];

struct SNode {
    int u, tim;

    SNode(int _u = 0, int _tim = 0) : u(_u), tim(_tim) {}

    inline bool operator>(const SNode &oth) const {
        return tim > oth.tim;
    }
};
priority_queue<SNode, vector<SNode>, greater<SNode>> pq;

int dijkstra(int s, int t) {
    fill(dis, dis + n, -1);
    while (!pq.empty()) {
        pq.pop();
    }

    pq.push(SNode(s, 5));
    while (!pq.empty()) {
        SNode u = pq.top(); pq.pop();
        if (u.tim == dis[u.u]) {
            continue;
        }
        dis[u.u] = u.tim;
        if (u.u == t) {
            return u.tim;
        }
        for (pair<int, int> &v : adj[u.u]) {
            int des = u.tim + v.se;
            if (des % sum[v.fi] >= g[v.fi] && v.fi != t) {
                des = des - des % sum[v.fi] + sum[v.fi] + 5;
            }
            pq.push(SNode(v.fi, des));
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m >> s >> t, n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> g[i] >> y >> r[i];
            g[i] += y;
            sum[i] = g[i] + r[i];
            adj[i].clear();
        }
        while (m--) {
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        int ans = dijkstra(s, t);
        cout << ans / 60 << ":" << setfill('0') << setw(2) << ans % 60 << '\n';
    }
}
