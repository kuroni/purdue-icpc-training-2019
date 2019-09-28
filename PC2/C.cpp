#include <bits/stdc++.h>
using namespace std;

const int N = 15;
const double INF = 1E9;

int n;
double c, dp[1 << N][N], pw[N];

struct SMouse {
    int x, y, t;
} a[N];

double solve() {
    for (int msk = 1; msk < (1 << n); msk++) {
        fill(dp[msk], dp[msk] + n, INF);
        double v = pw[__builtin_popcount(msk) - 1];
        for (int i = 0; i < n; i++) {
            if (msk >> i & 1) {
                if (__builtin_popcount(msk) == 1) {
                    double tim = hypot(a[i].x, a[i].y) / v;
                    if (tim <= a[i].t) {
                        dp[msk][i] = tim;
                    }
                }
                else {
                    int lst = msk ^ (1 << i);
                    for (int j = 0; j < n; j++) {
                        if (lst >> j & 1) {
                            double tim = hypot(a[i].x - a[j].x, a[i].y - a[j].y) / v + dp[lst][j];
                            if (tim <= a[i].t) {
                                dp[msk][i] = min(dp[msk][i], tim);
                            }
                        }
                    }
                }
            }
        }
    }
    return *min_element(dp[(1 << n) - 1], dp[(1 << n) - 1] + n);
}

double BS() {
    double l = 0, r = INF;
    while (r - l > 1E-6) {
        double m = (l + r) / 2;
        pw[0] = m;
        for (int i = 1; i < n; i++) {
            pw[i] = pw[i - 1] * c;
        }
        if (solve() <= INF - 1) {
            r = m;
        } else {
            l = m;
        }
    }
    return (l + r) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].t;
    }
    cin >> c;
    cout << fixed << setprecision(6) << BS() << '\n';
}
