#include <bits/stdc++.h>
using namespace std;

const int M = 205, N = 205;
const double EPS = 1E-10, INF = 1E9;

int n, m, w, h, s = 0, t = 1, tr[M + N] = {-2};
double lst = 0, mh = 0, v[M], l[N], mi[N][M], mx[N][M], sl[N], sr[N];
double cap[M + N][M + N];

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> w >> h;
    for (int i = 1; i <= m; i++) {
        cin >> v[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> l[i];
        swap(lst, l[i]); l[i] = lst - l[i];
    }
    l[n] = w - l[n - 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mi[i][j];
            v[j] -= mi[i][j];
            sl[i] += mi[i][j];
        }
        mh = max(mh, sl[i] /= l[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mx[i][j];
            sr[i] += mx[i][j];
        }
        sr[i] /= l[i];
    }
}

bool BFS() {
    fill(tr + 1, tr + m + n + 2, -1);
    queue<int> q;
    for (q.push(s); !q.empty(); q.pop()) {
        int u = q.front();
        if (u == t) {
            return true;
        }
        for (int i = 0; i < m + n + 2; i++) {
            if (tr[i] == -1 && cap[u][i] > EPS) {
                tr[i] = u;
                q.push(i);
            }
        }
    }
    return false;
}

double trace() {
    double ret = INF;
    for (int u = t; u != s; u = tr[u]) {
        int v = tr[u];
        ret = min(ret, cap[v][u]);
    }
    for (int u = t; u != s; u = tr[u]) {
        int v = tr[u];
        cap[v][u] -= ret;
        cap[u][v] += ret;
    }
    return ret;
}

void add_edge(int u, int v, double w) {
    cap[u][v] = w;
    cap[v][u] = 0;
}

bool check(double lim) {
    lim = mh - lim;
    double ans = 0;
    for (int i = 1; i <= m; i++) {
        add_edge(s, i + 1, v[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (sr[i] < lim) {
            return false;
        } else {
            double cur = max(0.0, (lim - sl[i]) * l[i]);
            add_edge(i + m + 1, t, cur);
            ans += cur;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            add_edge(j + 1, i + m + 1, mx[i][j] - mi[i][j]);
        }
    }
    while (BFS()) {
        ans -= trace();
    }
    return ans < EPS;
}

int main() {
    input();
    double le = 0, ri = h;
    while (le <= ri) {
        if (ri - le < EPS) {
            break;
        }
        double mi = (le + ri) / 2;
        if (check(mi)) {
            ri = mi;
        } else {
            le = mi;
        }
    }
    cout << fixed << setprecision(3) << (le + ri) / 2;
}
