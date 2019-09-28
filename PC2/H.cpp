#include <bits/stdc++.h>
using namespace std;

const int N = 7;
const double EPS = 1E-10;

int t;
double p;
vector<int> ve(N + 1, 0);

struct SPoint {
    double x, y;
    
    SPoint(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    
    SPoint operator-(const SPoint &b) const {
        return SPoint(x - b.x, y - b.y);
    }
    
    double operator*(const SPoint &b) const {
        return x * b.y - y * b.x;
    }
} a[N];

void solve() {
    for (int i = 0; i < N; i++) {
        ve[i] = i;
    }
    for (int i = 0; i < N; i++) {
        cin >> a[i].x >> a[i].y;
    }
    cin >> p;
    do {
        bool chk = true;
        for (int i = 0; i < N; i++) {
            for (int j = i + 2; j < N; j++) {
                if (i == 0 && j == N - 1) {
                    continue;
                }
                SPoint a1 = a[ve[i]], b1 = a[ve[i + 1]], a2 = a[ve[j]], b2 = a[ve[j + 1]];
                if (((a2 - a1) * (b1 - a1)) * ((b2 - a1) * (b1 - a1)) <= EPS
                &&  ((a1 - a2) * (b2 - a2)) * ((b1 - a2) * (b2 - a2)) <= EPS) {
                    chk = false;
                }
            }
        }
        double area = 0;
        for (int i = 0; i < N; i++) {
            area += (a[ve[i]] - a[ve[0]]) * (a[ve[i + 1]] - a[ve[0]]) / 2.0;
        }
        area = abs(area);
        area /= 4.0;
        if (abs(area * area * area - p) > 1E-5) {
            chk = false;
        }
        if (chk) {
            for (int i = 0; i < N; i++) {
                cout << ve[i] + 1 << " ";
            }
            return;
        }
    } while (next_permutation(ve.begin() + 1, ve.begin() + N));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
}
