
#include <bits/stdc++.h>

#define ll long long
using namespace std;

struct PT {
    double x, y;
    PT(): x(0), y(0) {}
    PT(double x, double y): x(x), y(y) {}
    double operator*(const PT &p) const {
        return x * p.y - y * p.x;
    }
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
    PT operator+(const PT &p) const {
        return PT(x + p.x, y + p.y);
    }
    PT operator*(const double &d) const {
        return PT(x * d, y * d);
    }
    PT operator/(const double &d) const {
        return PT(x / d, y / d);
    }
    double len2() const {
        return x * x + y * y;
    }
    double len() const {
        return hypot(x, y);
    }
};

double signedArea(vector<PT> pts) {
    int n = pts.size();
    double area = 0;
    for(int i = 0; i < n; i++) {
        area += pts[i] * pts[(i + 1) % n];
    }
    return 0.5 * area;
}

const double EPS = 1e-10;
const int N = 105, M = 25;
int n, m;
double x, y;
vector<PT> vpoly;
vector<vector<PT> > polygons;
vector<pair<PT, double> > segs[N][M];

// do line segments ab and cd intersect?
bool intersecting(PT a, PT b, PT c, PT d) {
    return ((a - d) * (c - d)) * ((b - d) * (c - d)) < 0 &&
           ((c - b) * (a - b)) * ((d - b) * (a - b)) < 0;
}

PT lineLine(PT a, PT b, PT c, PT d) {
    b = b - a;
    d = c - d;
    c = c - a;
    return a + b * (c * d) / (b * d);
}

bool cmp(const pair<PT, double> &p1, const pair<PT, double> &p2) {
    return p1.second < p2.second;
}
bool pointInPoly(PT p, int idx) {
    // is p in polygons[idx]?
    int cnt = 0;
    PT p2 = PT(-2000, p.y + EPS);
    int n = polygons[idx].size();
    for(int i = 0; i < n; i++) {
        if(intersecting(p, p2, polygons[idx][i], polygons[idx][(i + 1) % n])) {
            cnt++;
        }
    }
    return cnt % 2 == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    double area = 0;
    for(int i = 0; i < n; i++) {
        cin >> m;
        vpoly.clear();
        for(int j = 0; j < m; j++) {
            cin >> x >> y;
            vpoly.push_back(PT(x, y));
        }
        double area1 = signedArea(vpoly);
        area += fabs(area1);
        if(area1 < 0) {
            // flip polygon
            polygons.push_back(vector<PT>());
            for(int j = 0; j < m; j++) {
                polygons.back().push_back(vpoly[(int) vpoly.size() - j - 1]);
            }
        }else {
            polygons.push_back(vpoly);
        }
    }
    // find all line segment intersections
    for(int i = 0; i < n; i++) {
        for(int l1 = 0; l1 < polygons[i].size(); l1++) {
            PT a = polygons[i][l1];
            PT b = polygons[i][(l1 + 1) % polygons[i].size()];
            segs[i][l1].push_back({a, 0});
            segs[i][l1].push_back({b, (b - a).len2()});
            for(int j = i + 1; j < n; j++) {
                for(int l2 = 0; l2 < polygons[j].size(); l2++) {
                    PT c = polygons[j][l2];
                    PT d = polygons[j][(l2 + 1) % polygons[j].size()];
                    if(intersecting(a, b, c, d)) {
                        PT p = lineLine(a, b, c, d);
                        segs[i][l1].push_back({p, (p - a).len2()});
                        segs[j][l2].push_back({p, (p - c).len2()});
                    }
                }
            }
            sort(segs[i][l1].begin(), segs[i][l1].end(), cmp);
        }
    }
    // check if segment is entirely contained in another polygon
    // check if midpoint is in interior of other polygon
    // if it is not inside other polygon, add to shoelace formula
    double unionarea = 0;
    for(int i = 0; i < n; i++) {
        for(int l1 = 0; l1 < polygons[i].size(); l1++) {
            for(int j = 0; j < segs[i][l1].size() - 1; j++) {
                PT p1 = segs[i][l1][j].first;
                PT p2 = segs[i][l1][j + 1].first;
                PT mid = (p1 + p2) * 0.5;
                for(int k = 0; k < n; k++) {
                    if(i != k && pointInPoly(mid, k)) {
                        goto endloop;
                    }
                }
                // segment is outside
                unionarea += (p1 * p2);
                endloop:;
            }
        }
    }
    unionarea = unionarea * 0.5;

    cout << fixed << setprecision(8);
    cout << area << " " << unionarea << endl;
}