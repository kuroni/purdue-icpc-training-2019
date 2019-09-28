#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n;
string s;
long long m, ans = 0, f[N][26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    f[0][0] = 1;
    for (char &c : s) { 
        int cur = c - 'a';
        for (int i = n; i >= 1; i--) {
            f[i][cur] = 0;
            for (int j = 0; j < 26; j++) {
                f[i][cur] = min(m, f[i][cur] + f[i - 1][j]);
            }
        }
    }
    for (int i = n; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            ans += min(m, f[i][j]) * (n - i);
            m -= min(m, f[i][j]);
        }
    }
    cout << (m > 0 ? -1 : ans);
}
