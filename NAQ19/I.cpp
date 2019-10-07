#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const long long INF = 1E18 + 7;

int n, m, t, d, w, u, v, r[N];
bool chk[N];
long long dis[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> t >> d;
    for (int i = 1; i <= t; i++) {
        cin >> r[i];
    }
    r[0] = 1; r[++t] = n;
    for (int i = 0; i <= t; i++) {
        chk[r[i]] = true;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = INF;
        }
        dis[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = w;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dis[i][j] > d || !chk[i] || !chk[j]) {
                dis[i][j] = INF;
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    if (dis[1][n] == INF) {
        cout << "stuck\n";
    } else {
        cout << dis[1][n] << '\n';
    }
}