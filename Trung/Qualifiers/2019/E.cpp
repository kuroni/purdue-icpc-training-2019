#include <bits/stdc++.h>
using namespace std;

const int N = 35;

int n, a[N], f[N][2];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i][0] = max(f[i - 1][0], f[i - 1][1]);
        f[i][1] = f[i - 1][0] + a[i];
    }
    cout << max(f[n][0], f[n][1]);
}
