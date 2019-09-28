
#include <bits/stdc++.h>

#define ll long long
using namespace std;

typedef double Float;

const int D = 50;
const int N = 8;
const int M = 33554432;
int d, n, x, y;
vector<pair<int, int> > v[D], vec[D][D];
Float len[D][D];
Float dp[M];
Float dp2[65536][16];

Float mydist[16][16];

Float tsp(vector<pair<int, int> > vec) {
    int n = vec.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            mydist[i][j] = hypot(vec[i].first - vec[j].first, vec[i].second - vec[j].second);
        }
    }

    // assume the n-1st element is always the last of the permutation
    // doesn't matter since it's cyclic
    for(int i = 0; i < n - 1; i++) {
        dp2[0][i] = mydist[n - 1][i];
    }
    int naman = (1 << (n - 1));
    for(int b = 1; b < naman; b++) {
        for(int k = 0; k < n; k++) {
            dp2[b][k] = DBL_MAX;
        }
    }
    for(int b = 1; b < naman; b++) {
        for(int i = 0; i < n - 1; i++) {
            if((b >> i) & 1) {
                for(int k = 0; k < n; k++) {
                    dp2[b][k] = min(dp2[b][k], dp2[b - (1 << i)][i] + mydist[i][k]);
                }
            }
        }
    }
    return dp2[naman - 1][n - 1];
}

void tsp(int i, int j) {
    vector<pair<int, int> > vec;
    for(auto p : v[i]) vec.push_back(p);
    for(auto p : v[j]) vec.push_back(p);
    len[i][j] = tsp(vec);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> d;
    for(int i = 0; i < d; i++) {
        cin >> n;
        for(int j = 0; j < n; j++) {
            cin >> x >> y;
            v[i].push_back({x, y});
        }
    }

    Float before = 0;
    for(int i = 0; i < d; i++) {
        before += tsp(v[i]);
    }

    for(int i = 0; i < d / 2; i++) {
        for(int j = d / 2; j < d; j++) {
            tsp(i, j);
        }
    }

    // cout << "got here" << endl;

    // dp with bitmasking
    int naman = 1 << (d / 2);
    // put a bitmask 1 where we're allowed to choose that element
    dp[0] = 0;
    for(int b = 1; b < naman; b++) {
        dp[b] = DBL_MAX;
        int j = 0;
        for(int i = 0; i < d / 2; i++) {
            j += ((b >> i) & 1);
        }
        j--;
        for(int i = 0; i < d / 2; i++) {
            if((b >> i) & 1) {
                dp[b] = min(dp[b], len[i][d / 2 + j] + dp[b - (1 << i)]);
            }
        }
    }
    Float after = dp[naman - 1];

    // int o;
    // for(int i = 1; i <= d / 2; i++) {
    //     o = i % 2;
    //     for(int b = 0; b < naman; b++) {
    //         dp[o][b] = FLT_MAX;
    //         for(int j = 0; j < d / 2; j++) {
    //             if((b >> j) & 1) {
    //                 dp[o][b] = min(dp[o][b], len[i - 1][d / 2 + j] + dp[!o][b - (1 << j)]);
    //             }
    //         }
    //     }
    // }
    // Float after = dp[o][naman - 1];

    cout << fixed << setprecision(4);
    cout << before << " " << after << endl;
}
