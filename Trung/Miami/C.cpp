#include <bits/stdc++.h>
using namespace std;

const int N = 105;

double d, x[N], y[N];
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> d >> n, n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }
        int a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            bool chk = true;
            for (int j = 0; j < n && chk; j++) {
                if (i != j && hypot(x[i] - x[j], y[i] - y[j]) <= d) {
                    chk = false;
                }
            }
            if (chk) {
                a++;
            } else {
                b++;
            }
        }
        cout << b << " sour, " << a << " sweet\n";
    }
}
