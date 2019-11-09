#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 100005, INF = 1E9 + 7;

int n, k, q, u, v, m, a[N];
vector<int> pr[N];
set<int> se[N];

pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b) {
    pair<int, int> ans = min(a, b);
    if (a.fi == b.fi) {
        ans.se = a.se + b.se;
    }
    return ans;
}

struct segment_tree {
#define m (l + r) / 2
#define lc i * 2
#define rc i * 2 + 1

    int lz[4 * N];
    pair<int, int> tr[4 * N];

    void apply(int i, int v) {
        tr[i].fi += v;
        lz[i] += v;
    }

    void down(int i) {
        apply(lc, lz[i]);
        apply(rc, lz[i]);
        lz[i] = 0;
    }

    void build(int l, int r, int i) {
        if (l == r) {
            tr[i] = {0, 1};
        } else {
            build(l, m, lc);
            build(m + 1, r, rc);
            tr[i] = tr[lc] + tr[rc];
        }
    }

    void update(int l, int r, int i, int L, int R, int v) {
        if (l > R || r < L || L > R) {
            return;
        } else if (L <= l && r <= R) {
            apply(i, v);
        } else {
            down(i);
            update(l, m, lc, L, R, v);
            update(m + 1, r, rc, L, R, v);
            tr[i] = tr[lc] + tr[rc];
        }
    }

#undef m
#undef lc
#undef rc
} seg;

void init() {
    for (int i = 2; i < N; i++) {
        if (pr[i].empty()) {
            for (int j = i; j < N; j += i) {
                pr[j].push_back(i);
            }
        }
    }
}

void add(int i) {
    for (int &p : pr[a[i]]) {
        int l = 0, r = n + 1;
        auto it = se[p].upper_bound(i);
        if (it != se[p].begin()) {
            l = *prev(it);
        }
        if (it != se[p].end()) {
            r = *it;
        }
        seg.update(1, m, 1, max(1, r - k + 1), min(m, l), -1);
        seg.update(1, m, 1, max(1, i - k + 1), min(m, l), 1);
        seg.update(1, m, 1, max(1, r - k + 1), min(m, i), 1);
        se[p].insert(i);
    }
}

void erase(int i) {
    for (int &p : pr[a[i]]) {
        int l = 0, r = n + 1;
        auto it = se[p].erase(se[p].find(i));
        if (it != se[p].begin()) {
            l = *prev(it);
        }
        if (it != se[p].end()) {
            r = *it;
        }
        seg.update(1, m, 1, max(1, i - k + 1), min(m, l), -1);
        seg.update(1, m, 1, max(1, r - k + 1), min(m, i), -1);
        seg.update(1, m, 1, max(1, r - k + 1), min(m, l), 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    cin >> n >> k >> q;
    m = n - k + 1;
    seg.build(1, m, 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(i);
    }
    cout << m - ((seg.tr[1].fi == 0) * seg.tr[1].se) << '\n';
    while (q--) {
        cin >> u >> v;
        erase(u);
        a[u] = v;
        add(u);
        cout << m - ((seg.tr[1].fi == 0) * seg.tr[1].se) << '\n';
    }
    cout << accumulate(a + 1, a + n + 1, 0LL) << '\n';
}
