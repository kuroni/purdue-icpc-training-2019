#include <bits/stdc++.h>
using namespace std;

const int N = 555;

int a[N][N], v[N][N], f[N][N][11];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, n;
    cin >> r >> c >> n;
    memset(a, -1, sizeof a);
    memset(f, -1, sizeof f);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            cin >> a[i][j];
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j) {
            if (a[i][j] != -1 &&
                a[i][j - 1] != -1 && a[i][j] > a[i][j - 1] &&
                a[i][j + 1] != -1 && a[i][j] > a[i][j + 1] &&
                a[i - 1][j] != -1 && a[i][j] < a[i - 1][j] &&
                a[i + 1][j] != -1 && a[i][j] < a[i + 1][j]) {
                    v[i][j] = 1;
            }
        }
    for (int j = 1; j <= r; ++j) {
        f[0][j][0] = 0;
    }
    for (int i = 1; i <= c; ++i) {
        for (int j = 1; j <= r; ++j) {
            for (int k = 0; k <= n; ++k) {
                if (a[j][i] != -1) {
                    int m = k - v[j][i];
                    if (m >= 0) {
                        for (int l = j - 1; l <= j + 1; ++l) {
                            if (f[i - 1][l][m] != -1) {
                                int t = f[i - 1][l][m] + a[j][i];
                                if (f[i][j][k] == -1 || t < f[i][j][k]) f[i][j][k] = t;
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = -1;
    for (int j = 1; j <= r; ++j) {
        if (f[c][j][n] != -1) {
            if (ans == -1 || f[c][j][n] < ans) ans = f[c][j][n];
        }
    }
    if (ans == -1) {
        cout << "impossible";
    } else {
        cout << ans;
    }
}
