#include <bits/stdc++.h>
using namespace std;

const int N = 1E5 + 5, M = 10001;
const long long INF = 1E14 + 1;

int n, m;
long long a[N], d[N], f[M];
vector<long long> p[M];

bool check(long long u) {
    priority_queue<long long> q;
    long long s = 0;
    long long r = 0;
    for (int i = 1; i < M; ++i) {
        for (int j = 0; j < p[i].size(); ++j) {
            if (s + p[i][j] <= i * u) {
                s += p[i][j];
                q.push(p[i][j]);
                ++r;
            } else if (!q.empty() && p[i][j] < q.top()) {
                s = s - q.top() + p[i][j];
                q.pop();
                q.push(p[i][j]);
            } else {
                break;
            }
        }
    }
    return n - r <= m;
}

long long solve() {
    long long le = 1, ri = INF;
    while (le <= ri) {
        long long mi = (le + ri) / 2;
        if (check(mi)) {
            ri = mi - 1;
        } else {
            le = mi + 1;
        }
    }
    return le;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> d[i];
        p[d[i]].push_back(a[i]);
        // a[i] += a[i - 1];
    }
    for (int i = 1; i < M; ++i) {
        sort(p[i].begin(), p[i].end());
    }
    cout << solve();
}
