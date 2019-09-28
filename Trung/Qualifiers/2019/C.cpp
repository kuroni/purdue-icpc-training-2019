#include <bits/stdc++.h>
using namespace std;

const int MX = 1E7;

int t;
long long l, r;
vector<int> fi, se;
vector<long long> ve;

bool check(long long u) {
    fi.clear(); se.clear();
    while (u > 0) {
        fi.push_back(u % 10);
        se.push_back(u % 10);
        u /= 10;
    }
    reverse(fi.begin(), fi.end());
    return fi == se;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 1; i <= MX; i++) {
        if (check(i) && check(1LL * i * i)) {
            ve.push_back(1LL * i * i);
        }
    }
    cin >> t;
    while (t--) {
        cin >> l >> r;
        cout << distance(lower_bound(ve.begin(), ve.end(), l), upper_bound(ve.begin(), ve.end(), r)) << '\n';
    }
}
