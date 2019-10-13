#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int te = 0, n, kmp[N], f[N][N];
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> s, s != "0") {
        n = s.size();
        for (int l = n - 1; l >= 0; l--) {
            for (int r = l; r < n; r++) {
                f[l][r] = r - l + 1;
                if (r > l) {
                    int cur = r - l + 1;
                    kmp[cur] = kmp[cur - 1];
                    while (kmp[cur] > 0 && s[r] != s[l + kmp[cur]]) {
                        kmp[cur] = kmp[kmp[cur]];
                    }
                    if (s[r] == s[l + kmp[cur]]) {
                        kmp[cur]++;
                    }
                    if (kmp[cur] > 0 && cur % (cur - kmp[cur]) == 0) {
                        int len = cur - kmp[cur];
                        // cout << l << " " << r << ": " << len << '\n';
                        int occ = cur / len;
                        int add = log10(occ) + 1;
                        len = f[l][l + len - 1];
                        if (len > 1) {
                            len += 2;
                        }
                        f[l][r] = min(f[l][r], len + add);
                    }
                }
                for (int k = l; k < r; k++) {
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
                }
            }
        }
        cout << "Case " << ++te << ": " << f[0][n - 1] << '\n';
    }
}