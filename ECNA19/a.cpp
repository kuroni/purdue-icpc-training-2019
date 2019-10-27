#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1005;

int n, m, p;

struct point {
    int x, y;
    
    double dist(const point &oth) const {
        return hypot(x - oth.x, y - oth.y);
    }
} a[N], b[N], c[N];
bool chk[2][N];
double ans = 0;
vector<pair<int, int>> ve;

void solve(point a[N], point b[N], int n, int m) {
    fill(chk[0], chk[0] + n, false);
    fill(chk[1], chk[1] + m, false);
    ve.clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ve.push_back({i, j});
        }
    }
    sort(ve.begin(), ve.end(), [&](const pair<int, int> &u, const pair<int, int> &v) {
        return a[u.fi].dist(b[u.se]) < a[v.fi].dist(b[v.se]);
    });
    for (pair<int, int> &v : ve) {
        if (!chk[0][v.fi] && !chk[1][v.se]) {
            ans += a[v.fi].dist(b[v.se]);
            chk[0][v.fi] = chk[1][v.se] = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i].x >> b[i].y;
    }
    for (int i = 0; i < p; i++) {
        cin >> c[i].x >> c[i].y;
    }
    solve(a, b, n, m);
    solve(a, c, n, p);
    cout << fixed << setprecision(6) << ans;
}
