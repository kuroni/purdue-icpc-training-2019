#include <bits/stdc++.h>
using namespace std;

const int MX = 1E6;

long long l, r, ans = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin >> l >> r;
    for (int i = 1; i <= MX; i++) {
        for (long long j = r / i * i; j >= l; j -= i) {
            if (i <= j / i) {
                ans += i;
                if (i < j / i) {
                    ans += j / i;
                }
            }
        }
    }
    cout << ans;
}
