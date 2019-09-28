#include <bits/stdc++.h>
using namespace std;

struct PT {
    double x, y;
    PT(): x(0), y(0) {}
    PT(double x, double y): x(x), y(y) {}
    double operator*(const PT &p) const {
        return x * p.y - y * p.x;
    }
    PT operator+(const PT &p) const {
        return PT(x + p.x, y + p.y);
    }
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
    PT operator*(const double &d) const {
        return PT(x * d, y * d);
    }
    PT operator/(const double &d) const {
        return PT(x / d, y / d);
    }
    double len() const {
        return hypot(x, y);
    }
};

double dot(const PT &p1, const PT &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

struct line {
    PT a, b;
    line(PT a, PT b): a(a), b(b) {}
};

int te, n;
double r, x, y;
vector<PT> v;
const double EPS = 1e-10;
const double INF = 1e10;
int maxcnt = 1;

bool parallel(line l1, line l2) {
    PT p1 = l1.a - l1.b;
    PT p2 = l2.a - l2.b;
    return fabs(p1 * p2) < EPS;
}

PT R90(PT p) {
    return PT(p.y, -p.x);
}

PT lineLine(line l1, line l2) {
    PT a = l1.a;
    PT b = l1.b;
    PT c = l2.a;
    PT d = l2.b;
    
    b = b - a;
    d = c - d;
    c = c - a;
    return a + b * ((c * d) / (b * d));
}

// (center, radius)
pair<PT, double> circ(PT p1, PT p2, PT p3) {
    line l1(p1, p2);
    line l2(p1, p3);
    if(parallel(l1, l2)) {
        return {PT(0, 0), INF};
    }
    PT m1 = (p1 + p2) / 2;
    PT m2 = (p1 + p3) / 2;
    
    PT vec1 = R90(p1 - p2);
    PT vec2 = R90(p1 - p3);
    
    line perp1 = line(m1, m1 + vec1);
    line perp2 = line(m2, m2 + vec2);
    PT p = lineLine(perp1, perp2);
    return {p, (p - p1).len()};
}

void circleCount(PT center, double rad) {
    int cnt = 0;
    for(int l = 0; l < n; l++) {
        if((v[l] - center).len() < r + EPS) {
            cnt++;
        }
    }
    maxcnt = max(maxcnt, cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> te;
    while(te--) {
        maxcnt = 1;
        cin >> n >> r;
        r /= 2;
        v.clear();
        for(int i = 0; i < n; i++) {
            cin >> x >> y;
            v.push_back(PT(x, y));
        }
        // circumcircle of each triplet
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                for(int k = j + 1; k < n; k++) {
                    pair<PT, double> circle = circ(v[i], v[j], v[k]);
                    PT center = circle.first;
                    if(circle.second < r + EPS) {
                        circleCount(center, r);
                    }
                }
            }
        }
        // each circle of radius r joining two points
        for(int i = 0; i < n; i++) {
            PT p1 = v[i];
            for(int j = 0; j < n; j++) {
                PT p2 = v[j];
                double len = (p2 - p1).len();
                if(len >= 2 * r + EPS) {
                    continue;
                }
                PT m = (p1 + p2) / 2;
                PT vec = R90(p2 - p1);
                vec = vec / vec.len();
                
                double dist = sqrt(r * r - len * len / 4);
                PT c1 = m + vec * dist;
                PT c2 = m - vec * dist;
                
                circleCount(c1, r);
                circleCount(c2, r);
            }
        }
        cout << maxcnt << endl;
    }
}




