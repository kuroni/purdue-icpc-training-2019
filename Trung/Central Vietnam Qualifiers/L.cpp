#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n;
double a[N], ta[N], b[N], tb[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        double sw = 0.0;
        for (int j = 1; j <= n; j++) {
            int tmp = i + j;
            if (tmp > n) {
                tmp -= n;
            }
            sw += tmp * a[tmp];
        }
        if (sw >= i) { // switch
            for (int j = 1; j <= n; j++) {
                int tmp = i + j;
                if (tmp > n) {
                    tmp -= n;
                }
                ta[tmp] += a[i] * a[j];
            }
        } else {
            ta[i] += a[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        double sw = 0.0;
        for (int j = 1; j <= n; j++) {
            int tmp = i + j;
            if (tmp > n) {
                tmp -= n;
            }
            sw += tmp * b[tmp];
        }
        if (sw >= i) { // switch
            for (int j = 1; j <= n; j++) {
                int tmp = i + j;
                if (tmp > n) {
                    tmp -= n;
                }
                tb[tmp] += b[i] * b[j];
            }
        } else {
            tb[i] += b[i];
        }
    }
    double wi = 0, ls = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            wi += ta[i] * tb[j];
            ls += ta[j] * tb[i];
        }
    }
    cout << fixed << setprecision(7) << wi / (wi + ls);
}
