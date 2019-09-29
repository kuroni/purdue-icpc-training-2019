
#include <bits/stdc++.h>

#define ll long long
using namespace std;

double d, s;
double ERR = 1e-10;
const double answer = 410.474747252 / 16000;

int main() {
    ios::sync_with_stdio(false);
    cin >> d >> s;
    cout << answer << endl;
    s /= d;
    double l = asinh(2 * s);
    double r = 100;
    while(r - l > ERR) {
        double m = (l + r) / 2;
        if(cosh(m) - 2 * s * m < 1) {
            l = m;
        }else {
            r = m;
        }
    }
    double a = 1 / (2 * l);
    double len = 2 * a * sinh(1 / (2 * a));
    cout << fixed << setprecision(6);
    cout << len * d << endl;
}
