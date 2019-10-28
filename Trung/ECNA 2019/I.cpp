#include <bits/stdc++.h>
using namespace std;

const int M = 105, N = 105;

int m, n, cnt = 0, wa[M][N], st[M][N];
char s[M][N];
bool chk[M][N];

int sum(int su[M][N], int lr, int rr, int lc, int rc) {
    return su[rr][rc] - su[lr - 1][rc] - su[rr][lc - 1] + su[lr - 1][lc - 1];
}

char convert(int cnt) {
    if (cnt < 26) {
        return cnt + 'A';
    } else {
        return cnt - 26 + 'a';
    }
}

bool solve(int x, int y, int cur) {
    if (x == m + 1) {
        return true;
    }
    if (chk[x][y]) {
        if (y == n + 1) {
            return solve(x + 1, 1, cur);
        } else {
            return solve(x, y + 1, cur);
        }
    }
    for (int len = 0; ; len++) {
        if (chk[x][y + len] || chk[x + len][y]) {
            break;
        } else if (sum(wa, x, x + len, y, y + len) > 0) {
            break;
        } else if (sum(st, x, x + len, y, y + len) > 1) {
            break;
        } else if (sum(st, x, x + len, y, y + len) == 0) {
            continue;
        } else {
            for (int i = x; i <= x + len; i++) {
                for (int j = y; j <= y + len; j++) {
                    chk[i][j] = true;
                }
            }
            if (solve(x, y + 1, cur + 1)) {
                for (int i = x; i <= x + len; i++) {
                    for (int j = y; j <= y + len; j++) {
                        s[i][j] = convert(  cur);
                    }
                }
                return true;
            }
            for (int i = x; i <= x + len; i++) {
                for (int j = y; j <= y + len; j++) {
                    chk[i][j] = false;
                }
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        chk[i][n + 1] = true;
    }
    for (int i = 1; i <= n; i++) {
        chk[m + 1][i] = true;
    }
    for (int i = 1; i <= m; i++) {
        cin >> (s[i] + 1);
        for (int j = 1; j <= n; j++) {
            wa[i][j] = wa[i][j - 1] + wa[i - 1][j] - wa[i - 1][j - 1] + (s[i][j] == '#');
            st[i][j] = st[i][j - 1] + st[i - 1][j] - st[i - 1][j - 1] + (s[i][j] == '$');
            if (s[i][j] == '#') {
                chk[i][j] = true;
            }
        }
    }
    if (!solve(1, 1, 0)) {
        return cout << "elgnatcer\n", 0;
    } else {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cout << s[i][j];
            }
            cout << '\n';
        }
    }
}
