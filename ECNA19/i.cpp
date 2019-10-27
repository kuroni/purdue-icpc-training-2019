#include <bits/stdc++.h>
using namespace std;

const int M = 105, N = 105;

bool chk[M][M][N][N];
int m, n, cnt = 0, tr[M][M][N][N], wa[M][N], st[M][N];
char s[M][N], to[128];

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

bool solve(int lr, int rr, int lc, int rc) {
    if (chk[lr][rr][lc][rc]) {
        return tr[lr][rr][lc][rc] != 0;
    }
    chk[lr][rr][lc][rc] = true;
    if (sum(wa, lr, rr, lc, rc) == (rr - lr + 1) * (rc - lc + 1)) {
        return tr[lr][rr][lc][rc] = -M, true;
    }
    if (sum(st, lr, rr, lc, rc) == 0) {
        return false;
    }
    if (sum(st, lr, rr, lc, rc) == 1) {
        if (rr - lr == rc - lc) {
            if (sum(wa, lr, rr, lc, rc) == 0) {
                return tr[lr][rr][lc][rc] = M, true;
            } else {
                return false;
            }
        } else {
            if (sum(wa, lr, rr, lc, rc) == 0) {
                return false;
            }
        }
    }
    for (int k = lr; k < rr; k++) {
        if (solve(lr, k, lc, rc) && solve(k + 1, rr, lc, rc)) {
            return tr[lr][rr][lc][rc] = k, true;
        }
    }
    for (int k = lc; k < rc; k++) {
        if (solve(lr, rr, lc, k) && solve(lr, rr, k + 1, rc)) {
            return tr[lr][rr][lc][rc] = -k, true;
        }
    }
    return false;
}

void trace(int lr, int rr, int lc, int rc) {
    if (tr[lr][rr][lc][rc] == -M) {
        return;
    } else if (tr[lr][rr][lc][rc] == M) {
        for (int i = lr; i <= rr; i++) {
            for (int j = lc; j <= rc; j++) {
                s[i][j] = convert(cnt);
            }
        }
        ++cnt;
        return;
    }
    if (tr[lr][rr][lc][rc] > 0) {
        int k = tr[lr][rr][lc][rc];
        trace(lr, k, lc, rc);
        trace(k + 1, rr, lc, rc);
    } else {
        int k = -tr[lr][rr][lc][rc];
        trace(lr, rr, lc, k);
        trace(lr, rr, k + 1, rc);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        cin >> (s[i] + 1);
        for (int j = 1; j <= n; j++) {
            wa[i][j] = wa[i][j - 1] + wa[i - 1][j] - wa[i - 1][j - 1] + (s[i][j] == '#');
            st[i][j] = st[i][j - 1] + st[i - 1][j] - st[i - 1][j - 1] + (s[i][j] == '$');
        }
    }
    if (!solve(1, m, 1, n)) {
        return cout << "elgnatcer\n", 0;
    }
    trace(1, m, 1, n);
    cnt = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i][j] != '#') {
                if (to[s[i][j]] == '\0') {
                    to[s[i][j]] = convert(cnt++);
                }
                s[i][j] = to[s[i][j]];
            }
            cout << s[i][j];
        }
        cout << '\n';
    }
}
