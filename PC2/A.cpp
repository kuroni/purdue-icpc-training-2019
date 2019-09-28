#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;

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

// candles, lines, radius
const int N = 55, M = 20;
int n, m, r, a, b, c, x, y;
vector<PT> candles;
vector<line> lines;
vector<PT> allpoints;
int lineCount[M];
int circCount;

vector<PT> lineCircle(line l) {
    vector<PT> ret;
    PT a = l.a;
    PT b = l.b;
    b = b - a;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r * r;
    double D = B * B - A * C;
    if(D < -EPS) return ret;
    ret.push_back(a + b * (-B + sqrt(D + EPS)) / A);
    if(D > EPS) {
        ret.push_back(a + b * (-B - sqrt(D + EPS)) / A);
    }
    return ret;
}

bool parallel(line l1, line l2) {
    PT p1 = l1.a - l1.b;
    PT p2 = l2.a - l2.b;
    return fabs(p1 * p2) < EPS;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> r;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        candles.push_back(PT(x, y));
    }
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        c = -c;
        PT p1, p2;
        if(b == 0) {
            p1 = PT(((double) c) / a, 0);
            p2 = PT(((double) c) / a, 1);
        }else {
            p1 = PT(0, ((double) c) / b);
            p2 = PT(b, -a + ((double) c) / b);
        }
        lines.push_back(line(p1, p2));
    }
    // no two candles on same slice
    for(int i = 0; i < n; i++) {
        PT p1 = candles[i];
        for(int j = i + 1; j < n; j++) {
            PT p2 = candles[j];
            for(int k = 0; k < m; k++) {
                line l = lines[k];
                if(((l.a - l.b) * (p1 - l.b)) * ((l.a - l.b) * (p2 - l.b)) < 0) {
                    goto endloop;
                }
            }
            // same slice
            cout << "no" << endl;
            return 0;
            
            endloop:;
        }
    }
    
    // #slices = #candles
    // count #faces with Euler's V - E + F = 2
    // F = 2 - V + E
    
    // find all vertices
    
    // line line
    for(int i = 0; i < m; i++) {
        line l1 = lines[i];
        for(int j = i + 1; j < m; j++) {
            line l2 = lines[j];
            if(!parallel(l1, l2)) {
                PT p = lineLine(l1, l2);
                if(p.len() < r + EPS) {
                    allpoints.push_back(p);
                    lineCount[i]++;
                    lineCount[j]++;
                }
            }
        }
    }
    
    // line circle
    for(int i = 0; i < m; i++) {
        line l = lines[i];
        vector<PT> v = lineCircle(l);
        for(PT p : v) {
            lineCount[i]++;
            circCount++;
            allpoints.push_back(p);
        }
    }
    
    // remove vertices within EPS
    int V = 0;
    for(unsigned int i = 0; i < allpoints.size(); i++) {
        PT p1 = allpoints[i];
        for(unsigned int j = 0; j < i; j++) {
            PT p2 = allpoints[j];
            if((p1 - p2).len() < EPS) {
                goto endloop2;
            }
        }
        V++;
        endloop2:;
    }
    
    int E = circCount;
    for(int i = 0; i < m; i++) {
        E += lineCount[i] - 1;
    }
    int F = 1 - V + E;
    cout << (F == n ? "yes" : "no") << endl;
}


