#include <bits/stdc++.h>
using namespace std;

const int N = 50005, Q = 50005, D = 250;

int n, q, cur = 0, a[N], bit[N], cnt[N], ans[Q];
map<int, int> ma;

struct SQuery {
    int l, r, x, y, ind;
} que[Q];

void update(int u, int v) {
    if (u == 0) {
        return;
    }
    for (; u <= n; u += u & -u) {
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

void update_cnt(int u, int v) {
    update(cnt[u], -1);
    cnt[u] += v;
    update(cnt[u], 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (ma[a[i]] == 0) {
            ma[a[i]] = ++cur;
        }
        a[i] = ma[a[i]];
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> que[i].l >> que[i].r >> que[i].x >> que[i].y;
        que[i].ind = i;
    }
    sort(que + 1, que + q + 1, [](const SQuery &u, const SQuery &v) {
        return u.l / D < v.l / D || (u.l / D == v.l / D && u.r < v.r);
    });
    int l = 1, r = 0;
    for (int i = 1; i <= q; i++) {
        for (; r < que[i].r; r++) {
            update_cnt(a[r + 1], 1);
        }
        for (; l > que[i].l; l--) {
            update_cnt(a[l - 1], 1);
        }
        for (; r > que[i].r; r--) {
            update_cnt(a[r], -1);
        }
        for (; l < que[i].l; l++) {
            update_cnt(a[l], -1);
        }
        ans[que[i].ind] = query(que[i].y) - query(que[i].x - 1);
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
}
