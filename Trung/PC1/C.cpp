#include <bits/stdc++.h>
using namespace std;

int n, it = 0;
string s, t, ans;
vector<string> ve;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> s >> n) {
        ve.clear();
        ans = "";
        for (int i = 0; i < n; i++) {
            cin >> t;
            ve.push_back(t);
        }
        for (int i = 0; i < s.size(); ) {
            int sz = (ve.size() == 1 ? 1 : log10(ve.size() - 1) + 1);
            int cur = 0;
            while (sz--) {
                (cur *= 10) += s[i++] - '0';
            }
            ans += ve[cur];
            if (ve.size() > n && cur < ve.size() - 1) {
                ve.back().back() = ve[cur].front();
            }
            ve.push_back(ve[cur] + ve[cur].front());
        }
        cout << "Case " << ++it << ": " << ans << '\n';
    }
}
