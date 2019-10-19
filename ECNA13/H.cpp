#include <bits/stdc++.h>
using namespace std;
 
const int N = 1005;
 
int n, te = 0, a[N][3];
long long dp[N][8];
 
void solve() {
    for (int j = 0; j < 3; j++) {   
        for (int i = 1; i <= n; i++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int msk = 0; msk < 8; msk++) {
            dp[i][msk] = 0;
            for (int pre = 0; pre < 8; pre++) {
                long long cur = dp[i - 1][pre];
                for (int j = 0; j < 3; j++) {
                    if ((pre >> j & 1) && !(msk >> j & 1)) {
                        cur += a[i - 1][j] * a[i][j];
                    }
                }
                dp[i][msk] = max(dp[i][msk], cur);
            }
            if ((msk & 3) == 0) {
                for (int pre = 0; pre < 8; pre++) {
                    long long cur = dp[i - 1][pre] + a[i][0] * a[i][1];
                    for (int j = 2; j < 3; j++) {
                        if ((pre >> j & 1) && !(msk >> j & 1)) {
                            cur += a[i - 1][j] * a[i][j];
                        }
                    }
                    dp[i][msk] = max(dp[i][msk], cur);
                }
            }
            if ((msk & 6) == 0) {
                for (int pre = 0; pre < 8; pre++) {
                    long long cur = dp[i - 1][pre] + a[i][1] * a[i][2];
                    for (int j = 0; j < 1; j++) {
                        if ((pre >> j & 1) && !(msk >> j & 1)) {
                            cur += a[i - 1][j] * a[i][j];
                        }
                    }
                    dp[i][msk] = max(dp[i][msk], cur);
                }
            }
        }
    }
    cout << *max_element(dp[n], dp[n] + 8) << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n, n != 0) {
        cout << "Case " << ++te << ": ";
        solve();
    }
}
