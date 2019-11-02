#include <bits/stdc++.h>
using namespace std;

const int MOD = 1E9 + 7;

int n, k;
string s;

struct matrix {
    int m, n;
    vector<vector<long long>> f;

    matrix(int _m = 0, int _n = 0, bool _id = false) : m(_m), n(_n) {
        f = vector<vector<long long>>(m);
        for (int i = 0; i < m; i++) {
            f[i] = vector<long long>(n, 0);
        }
        if (_id) {
            assert(m == n);
            for (int i = 0; i < m; i++) {
                f[i][i] = 1;
            }
        }
    }

    matrix operator*(const matrix &oth) const {
        matrix ans(m, oth.n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < oth.n; j++) {
                for (int k = 0; k < n; k++) {
                    (ans.f[i][j] += f[i][k] * oth.f[k][j]) %= MOD;
                }
            }
        }
        return ans;
    }

    matrix operator^(const int &p) const {
        matrix ans(m, n, true);
        for (int i = __lg(p); i >= 0; i--) {
            ans = ans * ans;
            if (p >> i & 1) {
                ans = ans * (*this);
            }
        }
        return ans;
    }
} zer, one, bas, ans;

matrix init(int pre) {
    matrix ans(1 << n, 1 << n);
    for (int msk = 0; msk < (1 << n); msk++) {
        for (int ch = 0; ch < (1 << n); ch++) {
            if (__builtin_popcount(ch) & 1) {
                continue;
            }
            int nxt = msk, lst = pre;
            bool chk = true;
            for (int i = 0; i < n && chk; i++) {
                int cur = (ch >> i & 1);
                if (!(msk >> i & 1)) {
                    if (cur > lst) {
                        chk = false;
                    } else if (cur < lst) {
                        nxt |= (1 << i);
                    }
                }
                lst = cur;
            }
            if (chk) {
                ans.f[msk][nxt]++;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> s;
    zer = init(0); one = init(1);
    bas = matrix(1 << n, 1 << n, true);
    ans = matrix(1, 1 << n); ans.f[0][0] = 1;
    for (char &c : s) {
        if (c == '0') {
            bas = bas * zer;
        } else {
            bas = bas * one;
        }
    }
    cout << (ans * (bas ^ k)).f[0][(1 << n) - 1];
}
