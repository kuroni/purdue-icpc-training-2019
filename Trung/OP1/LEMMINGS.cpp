#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int M = 105, N = 105;

int m, n, te = 0, sum[M][N], ok[M][N];

struct SLemming {
    string dir;
    int it;

    pair<int, int> direction() {
        switch (dir[it]) {
            case 'E': return {0, 1};
            case 'W': return {0, -1};
            case 'N': return {1, 0};
            case 'S': return {-1, 0};
            default:  return {0, 0};
        }
    }
} a[M][N], tmp[M][N];

bool DFS(int u, int v) {
    bool chk = true;
    ok[u][v] = 2;
    pair<int, int> cur = a[u][v].direction();
    int x = u + cur.fi, y = v + cur.se;
    if (0 <= x && x < m && 0 <= y && y < n) {
        if (sum[x][y] > 1) {
            chk = false;
        } else if (a[x][y].dir != "" && (ok[x][y] == 1 || (ok[x][y] == 0 && !DFS(x, y)))) {
            chk = false;
        }
    }
    if (!chk) {
        (++a[u][v].it) %= 4;
        ok[u][v] = 1;
    }
    return chk;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> m >> n, m != 0) {
        cout << "Case " << ++te << ": ";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j].dir;
                a[i][j].it = 0;
            }
        }
        for (int ans = 0; ; ans++) {
            // initialize
            bool chk = false;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    ok[i][j] = 0;
                    sum[i][j] = 0;
                    tmp[i][j].dir = "";
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (a[i][j].dir != "") {
                        chk = true;
                        pair<int, int> cur = a[i][j].direction();
                        int x = i + cur.fi, y = j + cur.se;
                        if (0 <= x && x < m && 0 <= y && y < n) {
                            sum[x][y]++;
                        }
                    }
                }
            }
            if (!chk) {
                cout << ans << '\n';
                break;
            }

            // move
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (a[i][j].dir != "") {
                        if (ok[i][j] == 0) {
                            DFS(i, j);
                        }
                        if (ok[i][j] == 2) {
                            pair<int, int> cur = a[i][j].direction();
                            int x = i + cur.fi, y = j + cur.se;
                            if (0 <= x && x < m && 0 <= y && y < n) {
                                tmp[x][y] = a[i][j];
                            }
                        } else {
                            tmp[i][j] = a[i][j];
                        }
                    }
                }
            }

            // update
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    a[i][j] = tmp[i][j];
                }
            }
        }
    }
}
