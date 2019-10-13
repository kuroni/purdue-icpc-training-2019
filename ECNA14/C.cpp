#include <bits/stdc++.h>

using namespace std;

const int N = 7, M = 22;

bool h[N][N], yah;
char ch[M];
int a[N][N], p[M], q[M], xx1[M], yy1[M], xx2[M], yy2[M];

int calcLine(vector<int> v) {
    sort(v.begin(), v.end());
    // yahtzee
    if (v[0] == v[1] && v[1] == v[2] && v[2] == v[3] && v[3] == v[4]) {
        if (yah) return 100;
        yah = true;
        return 50;
    }
    // large
    if (v[1] == v[0] + 1 && v[2] == v[1] + 1 && v[3] == v[2] + 1 && v[4] == v[3] + 1) return 40;
    // small
    if (v[2] == v[1] + 1 && v[3] == v[2] + 1 && v[4] == v[3] + 1) return 30; // 1,2,3,4
    if (v[2] == v[0] + 1 && v[3] == v[2] + 1 && v[4] == v[3] + 1) return 30; // 0,2,3,4
    if (v[1] == v[0] + 1 && v[3] == v[1] + 1 && v[4] == v[3] + 1) return 30; // 0,1,3,4
    if (v[1] == v[0] + 1 && v[2] == v[1] + 1 && v[4] == v[2] + 1) return 30; // 0,1,2,4
    if (v[1] == v[0] + 1 && v[2] == v[1] + 1 && v[3] == v[2] + 1) return 30; // 0,1,2,3
    // full-house
    if (v[1] == v[0] && v[3] == v[2] && v[4] == v[3]) return 25;
    if (v[1] == v[0] && v[2] == v[1] && v[4] == v[3]) return 25;
    // 4-of-a-kind
    if (v[0] == v[1] && v[1] == v[2] && v[2] == v[3]) return v[0] + v[1] + v[2] + v[3];
    if (v[1] == v[2] && v[2] == v[3] && v[3] == v[4]) return v[1] + v[2] + v[3] + v[4];
    // 3-of-a-kind
    for (int i = 0; i < 3; ++i) {
       if (v[i] == v[i + 1] && v[i + 1] == v[i + 2]) return v[i] + v[i + 1] + v[i + 2];
    }
    return 0;
}

int calcSquare() {
    int res = 0;
    yah = false;
    for (int i = 1; i <= 5; ++i) {
        vector<int> v;
        for (int j = 1; j <= 5; ++j) v.push_back(a[i][j]);
        res += calcLine(v);
    }
    for (int j = 1; j <= 5; ++j) {
        vector<int> v;
        for (int i = 1; i <= 5; ++i) v.push_back(a[i][j]);
        res += calcLine(v);
    }
    vector<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(a[i][i]);
    res += calcLine(v);
    v.clear();
    for (int i = 1; i <= 5; ++i) v.push_back(a[i][6 - i]);
    res += calcLine(v);
    return res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    memset(a, -1, sizeof a);
    for (int cs = 1; cs <= n; ++cs) {
        for (int i = 1; i <= 5; ++i) {
            for (int j = 1; j <= 5; ++j) {
                a[i][j] = 0;
            }
        }
        memset(h, false, sizeof h);
        for (int i = 0; i < 13; ++i) {
            int t;
            bool f = true;
            scanf(" %c", &ch[i]);
            if (ch[i] == 'S') {
                scanf("%d", &t);
                for (int j = 1; f && j <= 5; ++j) {
                    for (int k = 1; f && k <= 5; ++k) {
                        if (a[j][k] == 0) {
                            a[j][k] = t;
                            f = false;
                        }
                    }
                }
            } else {
                scanf("%d%d", &p[i], &q[i]);
                h[p[i]][q[i]] = h[q[i]][p[i]] = true;
                for (int j = 1; f && j <= 5; ++j) {
                    for (int k = 1; f && k <= 5; ++k) {
                        if (ch[i] == 'H' && a[j][k] == 0 && a[j][k + 1] == 0) {
                            a[xx1[i] = j][yy1[i] = k] = p[i];
                            a[xx2[i] = j][yy2[i] = k + 1] = q[i];
                            f = false;
                        }
                        if (ch[i] == 'V' && a[j][k] == 0 && a[j + 1][k] == 0) {
                            a[xx1[i] = j][yy1[i] = k] = p[i];
                            a[xx2[i] = j + 1][yy2[i] = k] = q[i];
                            f = false;
                        }
                    }
                }
            }
        }
        int ans = calcSquare();
        for (int i = 1; i <= 6; ++i) {
            for (int j = 1; j <= 6; ++j) {
                if (!h[i][j]) {
                    for (int k = 0; k < 13; ++k) {
                        if (ch[k] != 'S') {
                            a[xx1[k]][yy1[k]] = i;
                            a[xx2[k]][yy2[k]] = j;
                            ans = max(ans, calcSquare());
                            a[xx1[k]][yy1[k]] = p[k];
                            a[xx2[k]][yy2[k]] = q[k];
                        }
                    }
                }
            }
        }
        cout << "Case " << cs << ": " << ans << endl;
    }
}