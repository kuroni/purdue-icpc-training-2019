#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 105, INF = 1E9 + 7;

int n, u[N], v[N], w[N];
vector<pair<int, int>> adj[N];

struct SNode {
    int dis;
    vector<int> pat;

    SNode(int _dis = 0) : dis(_dis) {
        pat.clear();
    }

    inline bool operator<(const SNode &oth) const {
        if (dis != oth.dis) {
            return dis < oth.dis;
        } else if (pat.size() != oth.pat.size()) {
            return pat.size() < oth.pat.size();
        } else {
            return pat < oth.pat;
        }
    }
} dis[N];
priority_queue<pair<SNode, int>, vector<pair<SNode, int>>, greater<pair<SNode, int>>> pq;

void dijkstra() {
    fill(dis + 1, dis + N, SNode(INF));
    dis[0] = SNode(0);
    dis[0].pat = {0};
    pq.push({dis[0], 0});
    while (!pq.empty()) {
        pair<SNode, int> u = pq.top(); pq.pop();
        if (dis[u.se] < u.fi) {
            continue;
        }
        for (pair<int, int> &v : adj[u.se]) {
            SNode tmp = u.fi;
            tmp.dis += w[v.se]; tmp.pat.push_back(v.fi);
            if (tmp < dis[v.fi]) {
                pq.push({dis[v.fi] = tmp, v.fi});
            }
        }
    }
}

void solve() {
    SNode ans = SNode(INF);
    for (int i = 0; i < N; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < n; i++) {
        cin >> u[i] >> v[i] >> w[i];
        if (u[i] > v[i]) {
            swap(u[i], v[i]);
        }
        adj[u[i]].push_back({v[i], i});
        adj[v[i]].push_back({u[i], i});
    }
    for (int i = 0; i < n; i++) {
        if (u[i] == 0 && v[i] == 1) {
            SNode tmp = SNode(w[i]);
            tmp.pat = {0, 1};
            ans = min(ans, tmp);
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (u[j] == 0 && v[j] == 1) {
                continue;
            }
            if (min(u[i], u[j]) == 0 && max(u[i], u[j]) == 1 && v[i] == v[j]) {
                SNode tmp = SNode(min(w[i], w[j]));
                tmp.pat = {0, v[i], 1};
                ans = min(ans, tmp);
                continue;
            }
            int w1 = w[i], w2 = w[j];
            w[i] = w[j] = 0;
            dijkstra();
            ans = min(ans, dis[1]);
            w[i] = w1; w[j] = w2;
        }
    }
    for (int &v : ans.pat) {
        cout << v << " ";
    }
    cout << ans.dis << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n, n != 0) {
        solve();
    }
}
