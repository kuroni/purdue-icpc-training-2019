
#include <bits/stdc++.h>

#define ll long long
using namespace std;

struct frac {
    int p, q;
    frac(int p, int q) : p(p), q(q) {}
    bool operator<(const frac &r) const {
        return p * r.q < r.p * q;
    }
};

int n;
const double maxdist = 2e7;
const double center = 2e7;

vector<frac> rat;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    rat.push_back(frac(0, 1));
    for(int pq = 2; pq < 580; pq++) {
        for(int p = 1; p < pq; p++) {
            int q = pq - p;
            if(__gcd(p, q) == 1) {
                rat.push_back(frac(p, q));
            }
        }
    }
    sort(rat.begin(), rat.end());
    int sz = rat.size();
    int x = center, y = 0;
    cout << x << " " << y << endl;
    for(int i = 1; i < n; i++) {
        frac f = rat[i % sz];
        switch(i / sz) {
        case 0:
            x += f.q;
            y += f.p;
            break;
        case 1:
            x -= f.p;
            y += f.q;
            break;
        case 2:
            x -= f.q;
            y -= f.p;
            break;
        case 3:
            x += f.p;
            y -= f.q;
            break;
        }
        cout << x << " " << y << endl;
    }
}