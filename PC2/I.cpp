#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 10;

LL u0[N], r0[N], s0[N], u[N], r[N], s[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < N; ++i) {
        cin >> u0[i] >> r0[i];
        s0[i] = 0;
    }
    for (int i = 0; i < N; ++i) {
        cin >> u[i] >> r[i] >> s[i];
    }
    for (int q = 0; q < 3; ++q) {
        for (int i = 0; i < N; ++i) {
            if (s[i] <= s0[i]) {
                LL t = (s0[i] - s[i]) / (u[i] + r[i]) + 1;
                s[i] += (u[i] + r[i]) * t;
                s0[i] = max(s0[i], s[i] - r[i]);
            }
            s0[(i + 1) % N] = s0[i] + u0[i] + r0[i];
            s[i] = max(s[i], s0[i] + u0[i]);
        }
    }
    cout << s0[0] - r0[N - 1] << endl;
}
