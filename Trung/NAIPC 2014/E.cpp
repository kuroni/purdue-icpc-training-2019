#include <bits/stdc++.h>
using namespace std;

const int N = 100005, K = 105;

int n, cnt = 0, a[N];
long long ans[K];

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = K - 1; i >= 1; i--) {
        int cur = 0;
        for (int j = 1; j <= n; j++) {
            ans[i] += cur = (cur + 1) * (a[j] % i == 0);
        }
        for (int j = 2 * i; j < K; j += i) {
            ans[i] -= ans[j];
        }
        (cnt += ans[i] > 0);
    }
    cout << cnt;
}
