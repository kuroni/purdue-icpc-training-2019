#include <bits/stdc++.h>
using namespace std;

const int N = 9;

int n, m, te = 0;
double dp[1 << N];

struct SPoint {
    int x, y;

    SPoint(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    SPoint(SPoint a, SPoint b) {
        *this = SPoint(a.x - b.x, a.y - b.y);
    }

    inline bool operator<(const SPoint &oth) const {
        return x != oth.x ? x < oth.x : y < oth.y;
    }

    inline long long operator*(const SPoint &oth) const {
        return 1LL * x * oth.y - 1LL * y * oth.x;
    }
} a[N];

double calc(int msk) {
    vector<SPoint> ve, hi, lo;
    for (int i = 0; i < n; i++) {
        if (msk >> i & 1) {
            ve.push_back(a[i]);
        }
    }
    sort(ve.begin(), ve.end());
    for (SPoint &v : ve) {
        while (hi.size() >= 2 && SPoint(hi[hi.size() - 2], v) * SPoint(hi[hi.size() - 2], hi.back()) <= 0) {
            hi.pop_back();
        }
        hi.push_back(v);
        while (lo.size() >= 2 && SPoint(lo[lo.size() - 2], v) * SPoint(lo[lo.size() - 2], lo.back()) >= 0) {
            lo.pop_back();
        }
        lo.push_back(v);
    }
    double ret = 0;
    for (int i = 1; i < hi.size(); i++) {
        ret += hypot(hi[i].x - hi[i - 1].x, hi[i].y - hi[i - 1].y);
    }
    for (int i = 1; i < lo.size(); i++) {
        ret += hypot(lo[i].x - lo[i - 1].x, lo[i].y - lo[i - 1].y);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);
    while (cin >> n >> m, n != 0 && m != 0) {
        for (int i = 0; i < n; i++) {
            cin >> a[i].x >> a[i].y;
        }
        for (int msk = 1; msk < (1 << n); msk++) {
            dp[msk] = calc(msk) + 2 * M_PI * m;
            for (int lst = msk; lst > 0; lst = (lst - 1) & msk) {
                dp[msk] = min(dp[msk], dp[lst] + dp[msk ^ lst]);
            }
        }
        cout << "Case " << ++te << ": length = " << dp[(1 << n) - 1] << '\n';
    }
}
