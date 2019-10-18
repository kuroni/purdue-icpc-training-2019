const int N = 5E5 + 5;

struct STree {
#define m (l + r) / 2
#define lc i * 2
#define rc i * 2 + 1

    long long tr[4 * N], lz[4 * N];
    
    void apply(int l, int r, int i, long long u) {
        lz[i] += u;
        tr[i] += (r - l + 1) * u;
    }
    
    void down(int l, int r, int i) {
        apply(l, m, lc, lz[i]);
        apply(m + 1, r, rc, lz[i]);
        lz[i] = 0;
    }
    
    void update(int l, int r, int i, int L, int R, long long v) {
        if (l > R || r < L || L > R) {
            return;
        } else if (L <= l && r <= R) {
            apply(l, r, i, v);
        } else {
            down(l, r, i);
            update(l, m, lc, L, R, v);
            update(m + 1, r, rc, L, R, v);
            tr[i] = tr[lc] + tr[rc];
        }
    }
    
    long long query(int l, int r, int i, int L, int R) {
        if (l > R || r < L || L > R) {
            return 0;
        } else if (L <= l && r <= R) {
            return tr[i];
        } else {
            down(l, r, i);
            return query(l, m, lc, L, R) + query(m + 1, r, rc, L, R);
            
        }
    }

#undef m
#undef lc
#undef rc
} seg;