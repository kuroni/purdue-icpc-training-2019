#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const double EPS = 1e-6;
const int MAXN = 1111111;

int a[MAXN];
double s1[MAXN], f1[MAXN], s2[MAXN], f2[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    double l = 0, r = 1000000001;
    f1[0] = f2[n + 1] = -1e10;
    while (r - l > EPS) {
        double mid = (l + r) / 2;
        for (int i = 1; i <= n; ++i) {
            s1[i] = s1[i - 1] + a[i] - mid;
            f1[i] = max(f1[i - 1], s1[i]);
        }
        for (int i = n; i > 0; --i) {
            s2[i] = s2[i + 1] + a[i] - mid;
            f2[i] = max(f2[i + 1], s2[i]);
        }
        double ans = max(f1[n], f2[1]);
        for (int i = 1; i < n; ++i) {
            ans = max(ans, f1[i] + f2[i + 1]);
        }
        if (ans > -1e-9) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << fixed << setprecision(8) << l << endl;
}