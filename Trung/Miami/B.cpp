#include <bits/stdc++.h>
using namespace std;

char s[5][5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 5; i++) {
        cin >> s[i];
    }
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (s[i][j] == 'k') {
                cnt++;
                for (int k = 1; k <= 2; k++) {
                    for (int msk = 0; msk < 4; msk++) {
                        int x = k, y = 3 - k;
                        if (msk & 1) {
                            x = -x;
                        }
                        if (msk & 2) {
                            y = -y;
                        }
                        x += i; y += j;
                        if (x >= 0 && x < 5 && y >= 0 && y < 5 && s[x][y] == 'k') {
                            return cout << "invalid", 0;
                        }
                    }
                }
            }
        }
    }
    cout << (cnt == 9 ? "valid" : "invalid");
}
