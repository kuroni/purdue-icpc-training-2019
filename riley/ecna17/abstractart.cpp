
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int N = 105;
int n, m, x, y;
vector<pair<double, double> > points[N];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> m;
        for(int j = 0; j < m; j++) {
            cin >> x >> y;
            points[i].push_back({x, y});
        }
    }
    double paint = 0;
    for(int i = 0; i < n; i++) {
        m = points[i].size();
        double area = 0;
        for(int j = 0; j < m; j++) {
            auto p1 = points[i][j];
            auto p2 = points[i][(j + 1) % m];
            area += p1.first * p2.second - p2.first * p1.second;
        }
        paint += fabs(area) / 2;
    }
    cout << fixed << setprecision(8);
    cout << paint << endl;
}