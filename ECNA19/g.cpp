#include <bits/stdc++.h>
using namespace std;

const int N = 1E6 + 5;

int n, m, a, c, ans = 0;
long long x, b[N];

void solve(int l, int r, long long lb, long long rb) {
    if (l > r) {
        return;
    }
    int m = (l + r) / 2;
    ans += (b[m] >= lb && b[m] <= rb);
    solve(l, m - 1, lb, min(rb, b[m] - 1));
    solve(m + 1, r, max(lb, b[m] + 1), rb);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> a >> c >> x;
    for (int i = 1; i <= n; i++) {
        x = (a * x + c) % m;
        b[i] = x;
    }
    solve(1, n, -1, m);
    cout << ans;
}
