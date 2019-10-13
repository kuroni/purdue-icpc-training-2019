#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int te = 0;
string s;
unordered_set<int> ve[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> s, s != "0") {
        int n = s.size();
        cout << "Case " << ++te << ": ";
        for (int l = n - 1; l >= 0; l--) {
            for (int r = l; r < n; r++) {
                unordered_set<int> &cur = ve[l][r];
                if (l == r) {
                    switch (s[l]) {
                        case 'I': cur.insert(1); break;
                        case 'V': cur.insert(5); break;
                        case 'X': cur.insert(10); break;
                        case 'L': cur.insert(50); break;
                        case 'C': cur.insert(100); break;
                    }
                } else {
                    for (int k = l; k < r; k++) {
                        for (int u : ve[l][k]) {
                            for (int v : ve[k + 1][r]) {
                                if (u >= v) {
                                    cur.insert(u + v);
                                } else {
                                    cur.insert(v - u);
                                }
                            }
                        }
                    }
                }
            }
        }
        vector<int> ans = {};
        for (int v : ve[0][n - 1]) {
            ans.push_back(v);
        }
        sort(ans.begin(), ans.end());
        for (int &v : ans) {
            cout << v << " ";
        }
        for (int l = n - 1; l >= 0; l--) {
            for (int r = l; r < n; r++) {
                ve[l][r].clear();
            }
        }
        cout << '\n';
    }           
}