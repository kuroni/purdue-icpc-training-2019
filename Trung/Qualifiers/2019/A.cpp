#include <bits/stdc++.h>
using namespace std;

const int N = 35;

int n, pt = 0;
char s[N][N], tmp[N * N], ans[N][N], t[N * N];

void rotate() {
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= 1; j--) {
            tmp[++cur] = s[j][i];
        }
    }
    cur = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = tmp[++cur];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
    }
    cin >> (t + 1);
    for (int k = 0; k < 4; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i][j] == '.') {
                    ++pt;
                    if (ans[i][j] != '\0' && ans[i][j] != t[pt]) {
                        return cout << "invalid grille", 0;
                    }
                    ans[i][j] = t[pt];
                }
            }
        }
        rotate();
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (ans[i][j] == '\0') {
                return cout << "invalid grille", 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j];
        }
    }
}
