#include <bits/stdc++.h>
using namespace std;

const int N = 1E5 + 5, Q = 1E5 + 5, INF = 2E9 + 7;
const int CO[7] = {0, 1, 2, 3, 2, 1, 0};

int n, q, a[N], d[N];
int ans[Q];

struct SQuery {
    int l, r;
} que[Q];

struct SNode {
    int mi, mx, le;
    
    SNode operator+(const SNode &oth) const {
        SNode ans;
        ans.mi = min(mi, oth.mi);
        ans.mx = max(mx, oth.mx);
        ans.le = max(max(le, oth.le), oth.mx - mi);
        return ans;
    }
};

struct STree {
#define m (l + r) / 2
#define lc i * 2
#define rc i * 2 + 1

    SNode tr[4 * N];
    
    void update(int l, int r, int i, int u, int v) {
        if (l == r) {
            tr[i].mi = tr[i].mx = v;
            tr[i].le = 0;
            return;
        }
        if (u <= m) {
            update(l, m, lc, u, v);
        } else {
            update(m + 1, r, rc, u, v);
        }
        tr[i] = tr[lc] + tr[rc];
    }
    
    SNode query(int l, int r, int i, int L, int R) {
        if (L <= l && r <= R) {
            return tr[i];
        } else if (R <= m) {
            return query(l, m, lc, L, R);
        } else if (L > m) {
            return query(m + 1, r, rc, L, R);
        } else {
            return query(l, m, lc, L, m) + query(m + 1, r, rc, m + 1, R);
        }
    }

#undef m
#undef lc
#undef rc
} seg;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> d[i];
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> que[i].l >> que[i].r;
    }
    for (int st = 0; st < 7; st++) {
        for (int i = 1; i <= n; i++) {
            seg.update(1, n, 1, i, a[i] + d[i] * CO[(st + i) % 7]);
        }
        for (int i = 1; i <= q; i++) {
            if (que[i].l < que[i].r && (que[i].l + st) % 7 == 0) {
                ans[i] = seg.query(1, n, 1, que[i].l, que[i].r).le;
            }
        }
    }
    for (int i = 1; i <= n / 2; i++) {
        swap(a[i], a[n + 1 - i]);
        swap(d[i], d[n + 1 - i]);
    }
    for (int i = 1; i <= q; i++) {
        que[i].l = n + 1 - que[i].l;
        que[i].r = n + 1 - que[i].r;
    }
    for (int st = 0; st < 7; st++) {
        for (int i = 1; i <= n; i++) {
            seg.update(1, n, 1, i, a[i] + d[i] * CO[(st + i) % 7]);
        }
        for (int i = 1; i <= q; i++) {
            if (que[i].l < que[i].r && (que[i].l + st) % 7 == 0) {
                ans[i] = seg.query(1, n, 1, que[i].l, que[i].r).le;
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
}