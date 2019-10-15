#include <bits/stdc++.h>
using namespace std;

const int N = 30005;
const double INF = 1E9;

int n;
double b, c, u, v;

struct SPoint {
    double x, y;

    SPoint(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    SPoint(SPoint st, SPoint en) : x(en.x - st.x), y(en.y - st.y) {}

    inline bool operator<(const SPoint &oth) const {
        return x == oth.x ? y < oth.y : x < oth.x;
    }

    inline double operator*(const SPoint &oth) const {
        return x * oth.y - y * oth.x;
    }
} a[N];
vector<SPoint> con;

double compute(SPoint cur) {
    return cur.x * cur.y / INF * b / INF * b;
}

double ternary_search(SPoint u, SPoint v) {
    double ans = max(compute(u), compute(v));
    while (v.x - u.x >= 1E-6) {
        SPoint le = SPoint((u.x + u.x + v.x) / 3, (u.y + u.y + v.y) / 3);
        SPoint ri = SPoint((u.x + v.x + v.x) / 3, (u.y + v.y + v.y) / 3);
        double v1 = compute(le), v2 = compute(ri);
        if (v1 > v2) {
            ans = max(ans, v1);
            v = ri;
        } else {
            ans = max(ans, v2);
            u = le;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> b;
    for (int i = 1; i <= n; i++) {
        cin >> c >> u >> v;
        a[i] = SPoint(u * INF / c, v * INF / c);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        while (con.size() >= 2 && SPoint(con[con.size() - 2], con.back()) * SPoint(con[con.size() - 2], a[i]) >= 0) {
            con.pop_back();
        }
        con.push_back(a[i]);
    }
    if (con.size() == 1) {
        cout << fixed << setprecision(6) << compute(con[0]) << '\n';
    } else {
        double ans = 0;
        for (int i = 1; i < con.size(); i++) {
            ans = max(ans, ternary_search(con[i - 1], con[i]));
        }
        cout << fixed << setprecision(6) << ans << '\n';
    }
}
