#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

pair<LL, LL> get(int n) {
    LL a[22];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    LL x = a[n - 1], y = 1;
    for (int i = n - 2; i >= 0; --i) {
        swap(x, y);
        x += y * a[i];
        LL t = __gcd(x, y);
        x /= t;
        y /= t;
    }
    if (y < 0) x = -x, y = -y;
    return make_pair(x, y);
}

void put(LL x, LL y) {
    LL t = __gcd(x, y);
    x /= t;
    y /= t;
    if (y < 0) x = -x, y = -y;
    if (x == 0) {
        cout << '0' << endl;
        return;
    }
    vector<LL> ans;
    while (y > 1) {
        LL t = x >= 0 ? x / y : x / y - (x % y != 0);
        ans.push_back(t);
        t = x - y * t;
        x = y;
        y = t;
    }
    ans.push_back(x);
    for (int i = 0; i < (int)ans.size() - 1; ++i) {
        cout << ans[i] << ' ';
    }
    cout << ans[ans.size() - 1] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    LL n1, n2, cas = 0;
    while (cin >> n1 >> n2) {
        if (n1 == 0 && n2 == 0) break;
        auto a = get(n1);
        auto b = get(n2);
        LL lcm = a.second * b.second / __gcd(a.second, b.second);
        cout << "Case " << ++cas << ":\n";
        put(lcm / a.second * a.first + lcm / b.second * b.first, lcm);
        put(lcm / a.second * a.first - lcm / b.second * b.first, lcm);
        put(a.first * b.first, a.second * b.second);
        put(a.first * b.second, a.second * b.first);
    }
}