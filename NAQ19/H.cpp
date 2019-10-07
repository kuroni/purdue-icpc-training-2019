#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int n, chk[N][N], dp[2 * N][2 * N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> chk[i][j];
        }
    }
    for (int l = 2 * n - 1; l >= 0; l--) {
        for (int r = l; r < 2 * n; r++) {
            for (int k = l; k <= r; k++) {
                if (chk[l % n][k % n]) {
                    dp[l][r] = max(dp[l][r], dp[l + 1][k - 1] + dp[k + 1][r] + 1);
                }
                dp[l][r] = max(dp[l][r], max(dp[l + 1][r], dp[l][r - 1]));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dp[i][i + n - 1]);
    }
    cout << ans;
}