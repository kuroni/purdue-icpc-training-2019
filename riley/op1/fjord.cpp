
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const double EPS = 1e-10;

struct PT {
    double x, y;
    PT(): x(0), y(0) {}
    PT(double x, double y): x(x), y(y) {}
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
    double len() const {
        return hypot(x, y);
    }
    double angle() const {
        return atan2(y, x);
    }
    double operator*(const PT &p) const {
        return x * p.x + y * p.y;
    }
};

const int N = 55, M = 3005;
int n, m, x, y;
vector<PT> vpoint;
double savings[N][M];
double dp[N][M];

double angnorm(double ang) {
    while(ang < 0) ang += 2 * M_PI;
    while(ang >= 2 * M_PI) ang -= 2 * M_PI;
    return ang;
}

double roadsaved(int i, int j) {
    PT p1 = vpoint[i];
    PT p2 = vpoint[i + 1];
    PT p3 = vpoint[i + 2];

    double l1 = (p1 - p2).len();
    double l2 = (p3 - p2).len();
    double l3 = (p1 - p3).len();

    // make sure segment p1 p2 is the shortest
    if(l1 > l2) {
        swap(p1, p3);
        swap(l1, l2);
    }
    // try isosceles triangle first

    double ang1 = (p1 - p2).angle();
    double ang2 = (p3 - p2).angle();
    double theta = min(angnorm(ang1 - ang2), angnorm(ang2 - ang1));
    double costheta = cos(theta);
    double sintheta = sin(theta);
    double A = j * sin((M_PI - theta) / 2) / sintheta;
    
    double save = -j;
    if(A >= 0 && A <= l1 + EPS) {
        save = 2 * A - j;
    }

    // short foot to other leg
    A = l1;
    if(j >= A * fabs(sintheta) - EPS) {
        double disc = sqrt(max((double) 0, j * j - A * A * sintheta * sintheta));
        double B = A * costheta + disc;
        if(B >= -EPS && B <= l2 + EPS) {
            save = max(save, A + B - j);
        }
        B = A * costheta - disc;
        if(B >= -EPS && B <= l2 + EPS) {
            save = max(save, A + B - j);
        }
    }

    // long foot to other leg
    A = l2;
    if(j >= A * fabs(sintheta) - EPS) {
        double disc = sqrt(max((double) 0, j * j - A * A * sintheta * sintheta));
        double B = A * costheta + disc;
        if(B >= -EPS && B <= l1 + EPS) {
            save = max(save, A + B - j);
        }
        B = A * costheta - disc;
        if(B >= -EPS && B <= l1 + EPS) {
            save = max(save, A + B - j);
        }
    }

    return save;
}

int main() {
    ios::sync_with_stdio(false);
    for(int te = 1; ; te++) {
        cin >> n >> m;
        if(n == 0) break;
        vpoint.clear();
        for(int i = 0; i < 2 * n + 1; i++) {
            cin >> x >> y;
            vpoint.push_back(PT(x, y));
        }
        for(int i = 0; i + 2 < 2 * n + 1; i += 2) {
            for(int j = 0; j <= m; j++) {
                savings[i / 2][j] = roadsaved(i, j);
            }
        }
        for(int j = 0; j <= m; j++) {
            dp[0][j] = -j;
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                dp[i][j] = savings[i - 1][j];
                for(int k = 0; k < j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + savings[i - 1][k]);
                }
            }
        }
        double bestsavings = 0;
        int bridgeused = 0;
        for(int j = 0; j <= m; j++) {
            if(dp[n][j] > bestsavings) {
                bridgeused = j;
                bestsavings = dp[n][j];
            }
        }
        cout << fixed << setprecision(2);
        cout << "Case " << te << ": " << bridgeused << " meters used saving " << bestsavings << " meters" << endl;
    }
}
