#include <bits/stdc++.h>
using namespace std;

const int N = 1E5 + 5, MX = 26;

string s;
int n, ans = 0, nxt[N][MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    int n = s.size();
    for (int i = 0; i < MX; i++) {
        nxt[n][i] = n;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < MX; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][s[i] - 'a'] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MX; j++) {
            if (s[i] - 'a' != j) {
                int n1 = nxt[i + 1][s[i] - 'a'], n2 = nxt[i][j];
                if (n2 < n1 && n2 < n) {
                    ans++;
                }
            }
        }
    }
    cout << ans;
}