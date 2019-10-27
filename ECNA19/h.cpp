#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll a, b, c, d, e, f, g;

ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

ll euclid(ll a, ll b, ll &x, ll &y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while(b) {
        ll q = a / b;
        ll t = b; b = a % b; a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }
    return a;
}

pair<ll, ll> crt(ll m1, ll r1, ll m2, ll r2) {
    ll s, t;
    ll g = euclid(m1, m2, s, t);
    if(r1 % g != r2 % g) return {0, -1};
    ll M = (m1 / g) * m2;
    return {mod(mod(s * r2, M) * (m1 / g) + mod(t * r1, M) * (m2 / g), M), M};
}

pair<ll, ll> crt(const vector<ll> &m, const vector<ll> &r) {
    pair<ll, ll> ret = {r[0], m[0]};
    int n = m.size();
    for(int i = 1; i < n; i++) {
        ret = crt(ret.second, ret.first, m[i], r[i]);
        if(ret.second == -1) break;
    }
    assert(ret.second != -1);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b >> c >> d >> e >> f >> g;
    ll M = min((a - 1) / 2, (b - 1) / 2);
    vector<ll> v;
    for(ll r = 1; r <= M; r++) {
        v.push_back(r * (a - 2 * r) * (b - 2 * r));
    }
    sort(v.rbegin(), v.rend());
    pair<ll, ll> p = crt({v[0], v[1], v[2]}, {c, d, e});
    ll ans = f / p.second;
    if(ans * p.second + p.first >= f) {
        cout << ans * p.second + p.first << endl;
    }else {
        cout << (ans + 1) * p.second + p.first << endl;
    }
}
