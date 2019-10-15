#include <bits/stdc++.h>
using namespace std;

const int N = 10005, INF = 1E9 + 7;

int n, t, d, bit[N];

struct STree {
#define m (l + r) / 2
#define lc i * 2
#define rc i * 2 + 1

    int mx[4 * N], lz[4 * N];

    void apply(int i, int u) {
        lz[i] += u;
        mx[i] += u;
    }

    void down(int i) {
        apply(lc, lz[i]);
        apply(rc, lz[i]);
        lz[i] = 0;
    }

    void build(int l, int r, int i) {
        mx[i] = -INF;
        if (l == r) {
            return;
        } else {
            build(l, m, lc);
            build(m + 1, r, rc);
        }
    }

    void update_node(int l, int r, int i, int u, int v) {
        if (l == r) {
            mx[i] = v;
            return;
        }
        down(i);
        if (u <= m) {
            update_node(l, m, lc, u, v);
        } else {
            update_node(m + 1, r, rc, u, v);
        }
        mx[i] = max(mx[lc], mx[rc]);
    }

    void update_range(int l, int r, int i, int L, int R, int v) {
        if (l > R || r < L || L > R) {
            return;
        }
        if (L <= l && r <= R) {
            apply(i, v);
            return;
        }
        down(i);
        update_range(l, m, lc, L, R, v);
        update_range(m + 1, r, rc, L, R, v);
        mx[i] = max(mx[lc], mx[rc]);
    }

    int query() {
        return mx[1];
    }

#undef m
#undef lc
#undef rc
} seg;

void update(int u, int v) {
    for (; u < N; u += u & -u) {
        bit[u] += v;
    }
}

int query(int u) {
    int ret = 0;
    for (; u > 0; u -= u & -u) {
        ret += bit[u];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    seg.build(1, N - 1, 1);
    for (int i = 1; i <= n; i++) {
        cin >> d >> t;
        seg.update_range(1, N - 1, 1, d + 1, N - 1, t);
        update(d, t);
        seg.update_node(1, N - 1, 1, d, query(d) - d);
        cout << max(seg.query(), 0) << '\n';
    }
}
