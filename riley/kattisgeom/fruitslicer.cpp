
#include <bits/stdc++.h>

#define ll long long
using namespace std;

struct PT {
    double x, y;
    PT(double x, double y): x(x), y(y) {}
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
    PT operator+(const PT &p) const {
        return PT(x + p.x, y + p.y);
    }
    PT operator*(const double d) const {
        return PT(x * d, y * d);
    }
    PT operator/(const double d) const {
        return PT(x / d, y / d);
    }
    double len() const {
        return hypot(x, y);
    }
};

double dot(const PT &p1, const PT &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

int n;
double x, y;
vector<PT> vpoint;
const double EPS = 1e-10;

int lineCount(PT a, PT b) {
    PT vec = (b - a) / (b - a).len();
    int cnt = 0;
    for(PT p : vpoint) {
        p = p - a;
        PT proj = vec * dot(p, vec);
        if((p - proj).len() < 1 + EPS) {
            cnt++;
        }
    }
    return cnt;
}

PT r90(const PT &p) {
    return PT(-p.y, p.x);
}

// line going through circles a and b.
// check all lines (at most 4) tangent to both
int solve(PT a, PT b) {
    double R = (b - a).len();
    PT vec = (b - a) / R;
    int ans = lineCount(a + r90(vec), b + r90(vec));
    ans = max(ans, lineCount(a - r90(vec), b - r90(vec)));
    if(R > 2) {
        double k = atan2(b.y - a.y, b.x - a.x);
        double theta1 = -k + asin(2 / R);
        double theta2 = -2 * k + M_PI - theta1;
        ans = max(ans, lineCount(PT(a.x + cos(theta1), a.y + sin(theta1)), PT(b.x - cos(theta1), b.y - sin(theta1))));
        ans = max(ans, lineCount(PT(a.x + cos(theta2), a.y + sin(theta2)), PT(b.x - cos(theta2), b.y - sin(theta2))));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        vpoint.push_back(PT(x, y));
    }
    int M = 1;
    for(PT p1 : vpoint) {
        int cnt = 0;
        for(PT p2 : vpoint) {
            if((p2 - p1).len() > EPS) {
                M = max(M, solve(p1, p2));
            }else {
                cnt++;
            }
        }
        M = max(M, cnt);
    }
    cout << M << endl;
}