#include <bits/stdc++.h>
using namespace std;

const int N = 200;
const long long INF = 1E18 + 7;

int n, k, u, a[N], cnt[6];
long long ans = 0, tot = 0, su[N][6], dp[N][6];
char s[N];
vector<int> ve;
string t;

int convert(char u) {
    switch (u) {
        case 'A': return 1;
        case 'E': return 2;
        case 'I': return 3;
        case 'O': return 4;
        case 'U': return 5;
        default:  return 0;
    }
}

long long solve(vector<int> &ve) {
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= 5; j++) {
            dp[i][j] = -INF;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 5; j++) {
            int cur = ve[j - 1];
            if (i >= cnt[cur]) {
                dp[i][j] = dp[i - cnt[cur]][j - 1] + su[i][cur] - su[i - cnt[cur]][cur];
            }
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }
    return dp[n][5];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[convert(s[i])]++;
    }
    cin >> k;
    while (k--) {
        cin >> u;
        cnt[convert(s[u])]--;
        s[u] = 'X';
    }
    cin >> t;
    for (char &c : t) {
        cnt[convert(c)]++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 5; j++) {
            su[i][j] = su[i - 1][j];
        }
        su[i][convert(s[i])] += a[i];
        if (convert(s[i]) > 0) {
            tot += a[i];
        }
    }
    for (int i = 1; i <= 5; i++) {
        ve.push_back(i);
    }
    solve(ve);
    do {
        ans = max(ans, solve(ve));
    } while (next_permutation(ve.begin(), ve.end()));
    cout << tot - ans;
}
