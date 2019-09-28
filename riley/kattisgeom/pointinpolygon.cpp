
#include <bits/stdc++.h>

#define ll long long
using namespace std;

#define INPOLY 0
#define ONPOLY 1
#define OUTPOLY 2

struct PT {
    double x;
    double y;
    PT(double x, double y): x(x), y(y) {}
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
    double operator*(const PT &p) const {
        return x * p.y - y * p.x;
    }
};

const int N = 1005, M = 105;
int n, m, x, y;
vector<PT> vpoly;
string str[] = {"in", "on", "out"};
const double EPS = 1e-10;

// do line segments intersect?
// inpoly = intersect. outpoly = no intersection. onpoly = point of one segment is on the other segment
int intersecting(PT p1, PT p2, PT q1, PT q2) {
    double a = (p2 - p1) * (q1 - p1);
    double b = (p2 - p1) * (q2 - p1);
    if(fabs(a) < EPS || fabs(b) < EPS) {
        return ONPOLY;
    }else if(a * b > 0) {
        return OUTPOLY;
    }
    a = (q2 - q1) * (p1 - q1);
    b = (q2 - q1) * (p2 - q1);
    if(fabs(a) < EPS || fabs(b) < EPS) {
        return ONPOLY;
    }else if(a * b > 0) {
        return OUTPOLY;
    }
    return INPOLY;
}

// make the slope such that it won't be parallel with a polygon
// line segment, and won't have a polygon point on the line
int inPoly(PT p1) {
    PT p2 = PT(-20000, p1.y + 1);
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        PT q1 = vpoly[i];
        PT q2 = vpoly[(i + 1) % n];
        int res = intersecting(p1, p2, q1, q2);
        if(res == ONPOLY) {
            return ONPOLY;
        }else if(res == INPOLY) {
            cnt++;
        }
    }
    return (cnt % 2 == 0 ? OUTPOLY : INPOLY);
}

int main() {
    ios::sync_with_stdio(false);
    while(true) {
        cin >> n;
        if(n == 0) break;
        vpoly.clear();
        for(int i = 0; i < n; i++) {
            cin >> x >> y;
            vpoly.push_back(PT(x, y));
        }
        cin >> m;
        for(int i = 0; i < m; i++) {
            cin >> x >> y;
            cout << str[inPoly(PT(x, y))] << endl;
        }
    }
}