
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
    PT operator*(const double &d) const {
        return PT(x * d, y * d);
    }
    PT operator/(const double &d) const {
        return PT(x / d, y / d);
    }
    double operator*(const PT &p) const {
        return x * p.y - y * p.x;
    }
};

const double INF = 1e10;
const int N = 105;
int n, k;
double x, y;
vector<PT> v;
vector<int> st;

// [#points][#segments]
double dp[N][N];
double maxdist[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while(true) {
        cin >> n >> k;
        if(n == 0) break;
        v.clear();
        for(int i = 0; i < n; i++) {
            cin >> x >> y;
            v.push_back(PT(x, y));
        }
        // convex hull
        st.clear();
        for(int i = 0; i < n; i++) {
            while(st.size() >= 2) {
                int j = st.back();
                st.pop_back();
                int k = st.back();
                if((v[j] - v[k]) * (v[i] - v[k]) < 0) {
                    st.push_back(j);
                    break;
                }
            }
            st.push_back(i);
        }
        // m = (y2 - y1) / (x2 - x1)
        // y = y1 + m(x - x1)
        int m = st.size();
        for(int i = 1; i < m; i++) {
            double m1 = (v[st[i]].y - v[st[i - 1]].y) / (v[st[i]].x - v[st[i - 1]].x);
            for(int j = i + 1; j < m; j++) {
                double m2 = (v[st[j]].y - v[st[j - 1]].y) / (v[st[j]].x - v[st[j - 1]].x);
                maxdist[i][j] = 0;
                for(int k = st[i - 1] + 1; k < st[j]; k++) {
                    maxdist[i][j] = max(maxdist[i][j],
                        min(v[st[i]].y + m1 * (v[k].x - v[st[i]].x),
                            v[st[j]].y + m2 * (v[k].x - v[st[j]].x)) - v[k].y);
                }
            }
        }

        // i = index of last point on a roofing segment
        // segs = number of roofing segments
        double M = INF;
        for(int i = 1; i < m; i++) {
            // If segs = 1, dp is just maximum distance from a point to the line
            double m1 = (v[st[i]].y - v[st[i - 1]].y) / (v[st[i]].x - v[st[i - 1]].x);
            dp[i][1] = 0;
            for(int j = 0; j < st[i]; j++) {
                dp[i][1] = max(dp[i][1], v[st[i]].y + m1 * (v[j].x - v[st[i]].x) - v[j].y);
            }
            for(int segs = 2; segs <= min(i, k); segs++) {
                dp[i][segs] = INF;
                for(int j = segs - 1; j < i; j++) {
                    dp[i][segs] = min(dp[i][segs], max(dp[j][segs - 1], maxdist[j][i]));
                }
            }
            if(k <= i) {
                double M2 = dp[i][k];
                for(int j = st[i] + 1; j < n; j++) {
                    M2 = max(M2, v[st[i]].y + m1 * (v[j].x - v[st[i]].x) - v[j].y);
                }
                M = min(M, M2);
            }
        }
        cout << fixed << setprecision(3);
        cout << M << endl;
    }
}