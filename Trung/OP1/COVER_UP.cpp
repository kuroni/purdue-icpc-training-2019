#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 5;

int n, m, l;
double p, f[N][N], dp[N + 1][1 << N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n, n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> m >> l >> p;
            pair<double, int> fi = {0.0, 0}, se = {0.0, 0};
            if (l != 0) {
                fi = {p / l, l};
            }
            if (l != m) {
                se = {(1.0 - p) / (m - l), m - l};
            }
            swap(fi, se);
            for (int j = 0; j < min(m, N); j++) {
                if (fi.se == 0) {
                    swap(fi, se);
                }
                f[i][j] = fi.fi / (fi.fi * fi.se + se.fi * se.se);
                fi.se--;
            }
        }

        fill(dp[n], dp[n] + (1 << n), 0.0);
        dp[n][(1 << n) - 1] = 1.0;
        for (int i = n - 1; i >= 0; i--) {
            fill(dp[i], dp[i] + (1 << n), 0.0);
            dp[i][(1 << n) - 1] = 1.0;
            for (int msk = 0; msk < (1 << n); msk++) {
                for (int lst = msk; lst > 0; lst = (lst - 1) & msk) {
                    double pro = dp[i + 1][msk];
                    for (int j = 0; j < n; j++) {
                        if (lst >> j & 1) {
                            pro *= f[j][i];
                        }
                    }
                    dp[i][msk ^ lst] += pro;
                }
            }
            for (int msk = 0; msk < (1 << n); msk++) {
                cout << i << " " << msk << ": " << dp[i][msk] << '\n';
            }
        }
        cout << dp[0][0] << '\n';
    }
}
