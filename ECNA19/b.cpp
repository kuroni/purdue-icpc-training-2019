#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1005, INF = 1E9 + 7;

int n, m, s, alph1, alph2, u, w, a, cnt = 0;

// node (from, to)
map<pair<int, int>, int> angle, ind;
int fm[5 * N], to[5 * N], weight[5 * N];
int dst[2][5 * N];
vector<vector<tuple<int, int, int>>> v;
vector<pair<int, int>> adj[5 * N];

struct dijkstra_node {
    int nod, val;
    bool reached;
    
    inline bool operator>(const dijkstra_node &oth) const {
        return val > oth.val;
    }
    
    dijkstra_node(int _nod = 0, int _val = 0, bool _reached = false) {
        nod = _nod;
        val = _val;
        reached = _reached;
    }
};
priority_queue<dijkstra_node, vector<dijkstra_node>, greater<dijkstra_node>> pq;

// start at {1, ?}, go through {s, ?}, return to {1, ?}
void dijkstra() {
    if (s == 1) {
        return void(cout << 0);
    }
    int ans = INF;
    fill(dst[0], dst[0] + 5 * N, INF);
    fill(dst[1], dst[1] + 5 * N, INF);
    for (int i = 0; i < cnt; i++) {
        if (fm[i] == 1) {
            pq.push(dijkstra_node(i, dst[0][i] = 0, false));
        }
    }
    while (!pq.empty()) {
        dijkstra_node u = pq.top(); pq.pop();
        if (dst[u.reached][u.nod] < u.val) {
            continue;
        }
        if (to[u.nod] == 1 && u.reached) {
            ans = min(ans, u.val + weight[u.nod]    );
            continue;
        }
        for (pair<int, int> &v : adj[u.nod]) {
            int tmp = u.val + v.se, nxt = v.fi;
            bool re = (u.reached || v.fi == s);
            if (tmp < dst[re][nxt]) {
                pq.push(dijkstra_node(nxt, dst[re][nxt] = tmp, re));
            }
        }
    }
    if (ans == INF) {
        cout << "impossible\n";
    } else {
        cout << ans << '\n';
    }
}

int angnorm(int ang) {
    while(ang < 0) ang += 360;
    while(ang >= 360) ang -= 360;
    return ang;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s >> alph1 >> alph2;
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        cin >> m;
        vector<tuple<int, int, int>> vt;
        while (m--) {
            cin >> u >> w >> a;
            // node (u, i, a)
            angle[{i, u}] = 180 - a;
            ind[{i, u}] = cnt;
            fm[cnt] = i;
            weight[cnt] = w;
            to[cnt] = u;
            cnt++;
            vt.push_back({u, w, angnorm(180 - a)});
        }
        v.push_back(vt);
    }
    int nod = 0;
    for(auto &v2 : v) {
        nod++;
        for(auto &p : v2) {
            u = get<0>(p);
            w = get<1>(p);
            a = get<2>(p);
            int i = ind[{nod, u}];
            for(auto &p2 : v2) {
                // cout << p2 << '\n';
                int a2 = get<2>(p2);
                int j = ind[{get<0>(p2), nod}];
                int w = get<1>(p);
                int x = angnorm(a2 - (a - 180));
                if(x <= 180 && x <= alph1 || x >= 180 && 360 - x <= alph2) {
                    adj[j].push_back({i, weight[j]});
                }
            }
        }
    }
    dijkstra(); 
}