#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1111;

int sa[MAXN], sb[MAXN];

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    int p, d, s = 0, swa = 0, swb = 0;
    cin >> p >> d;
    for (int i = 1; i <= p; ++i) {
        int x, a, b;
        cin >> x >> a >> b;
        sa[x] += a;
        sb[x] += b;
        s += a;
        s += b;
    }
    for (int i = 1; i <= d; ++i) {
        int t = (sa[i] + sb[i]) / 2 + 1;
        int wa, wb;
        if (sa[i] > sb[i]) {
            wa = sa[i] - t;
            wb = sb[i];
            cout << "A " << sa[i] - t << ' ' << sb[i] << endl;
        } else {
            wa = sa[i];
            wb = sb[i] - t;
            cout << "B " << sa[i] << ' ' << sb[i] - t << endl;
        }
        swa += wa;
        swb += wb;
    }
    printf("%.8f\n", fabs(swa - swb) / s);
}