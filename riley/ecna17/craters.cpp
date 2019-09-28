
#include <bits/stdc++.h>

#define ll long long
using namespace std;

struct PT {
    double x;
    double y;
    int circ;
    PT(double x, double y, int circ): x(x), y(y), circ(circ) {}
    bool operator<(const PT &p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
    double cross(const PT &p) const {
        return x * p.y - y * p.x;
    }
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y, -1);
    }
};

const double EPS = 1e-10;
const int N = 205;
int n;
int cx[N], cy[N], cr[N];
bool useless[N];
vector<PT> v;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> cx[i] >> cy[i] >> cr[i];
        cr[i] += 10;
    }

    // this probably never happens but whatever
    if(n == 0) {
        cout << 0 << endl;
        return 0;
    }

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            double R = hypot((double) (cx[i] - cx[j]), (double) (cy[i] - cy[j]));
            // one circle is entirely contained in the other
            if(R + cr[i] < cr[j] + EPS) {
                useless[i] = true;
            }else if(R + cr[j] < cr[i] + EPS) {
                useless[j] = true;
            }
        }
    }
    // remove useless circles
    int offset = 0;
    for(int i = 0; i < n; i++) {
        cx[i - offset] = cx[i];
        cy[i - offset] = cy[i];
        cr[i - offset] = cr[i];
        offset += useless[i];
    }
    n -= offset;
    cout << fixed << setprecision(8);

    if(n == 1) {
        cout << (2 * M_PI * cr[0]) << endl;
        return 0;
    }

    // all pairs of craters, create a set of relevant points
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            double A = cx[j] - cx[i];
            double B = cy[j] - cy[i];
            double R = hypot(A, B);

            double k = atan2(A, B);
            double k2 = asin((cr[i] - cr[j]) / R);
            double ang1 = k2 - k;
            double ang2 = M_PI - k2 - k;

            v.push_back(PT(cx[i] + cr[i] * cos(ang1), cy[i] + cr[i] * sin(ang1), i));
            v.push_back(PT(cx[j] + cr[j] * cos(ang1), cy[j] + cr[j] * sin(ang1), j));
            v.push_back(PT(cx[i] + cr[i] * cos(ang2), cy[i] + cr[i] * sin(ang2), i));
            v.push_back(PT(cx[j] + cr[j] * cos(ang2), cy[j] + cr[j] * sin(ang2), j));

            v.push_back(PT(cx[i] - A * cr[i] / R, cy[i] - B * cr[i] / R, i));
            v.push_back(PT(cx[j] + A * cr[j] / R, cy[j] + B * cr[j] / R, j));
        }
    }

    // find convex hull of set, ignoring points within EPS
    sort(v.begin(), v.end());
    stack<PT> st;
    for(PT p : v) {
        while(st.size() >= 2) {
            PT p2 = st.top();
            st.pop();
            PT p3 = st.top();
            if((p2 - p3).cross(p - p3) < 0) {
                st.push(p2);
                break;
            }
        }
        st.push(p);
    }

    stack<PT> st2;
    for(int i = (int) v.size() - 1; i >= 0; i--) {
        PT p = v[i];
        while(st2.size() >= 2) {
            PT p2 = st2.top();
            st2.pop();
            PT p3 = st2.top();
            if((p2 - p3).cross(p - p3) < 0) {
                st2.push(p2);
                break;
            }
        }
        st2.push(p);
    }
    vector<PT> vec;
    while(st2.size()) {
        vec.push_back(st2.top());
        st2.pop();
    }
    for(int i = (int) vec.size() - 2; i >= 0; i--) {
        st.push(vec[i]);
    }

    // compute perimeter, taking arc lengths into account
    double len = 0;
    PT top = st.top();
    PT p = top;
    st.pop();
    while(!st.empty()) {
        p = st.top();
        st.pop();
        if(top.circ == p.circ && hypot(p.x - top.x, p.y - top.y) > EPS) {
            // add arc
            int i = p.circ;
            double ang1 = atan2(p.y - cy[i], p.x - cx[i]);
            double ang2 = atan2(top.y - cy[i], top.x - cx[i]);
            double theta = ang1 - ang2;
            while(theta < 0) theta += 2 * M_PI;
            len += theta * cr[i];
        }else {
            len += hypot(p.x - top.x, p.y - top.y);
        }
        top = p;
    }
    cout << len << endl;
}