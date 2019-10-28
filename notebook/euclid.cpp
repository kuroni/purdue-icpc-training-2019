#define ll long long

ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

ll powermod(ll a, ll b, ll m) {
    ll ans = 0;
    while(b) {
        if(b & 1) ans = mod(ans * a, m);
        a = mod(a * a, m);
        b /= 2;
    }
    return ans;
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

ll modinverse(ll a, ll m) {
    ll x, y;
    ll g = euclid(a, m, x, y);
    return g > 1 ? -1 : mod(x, m);
}

pair<ll, ll> crt(ll r1, ll m1, ll r2, ll m2) {
    ll s, t;
    ll g = euclid(m1, m2, s, t);
    if(r1 % g != r2 % g) return {0, -1};
    ll M = m1 / g * m2;
    return {mod(mod(s * r2, M) * (m1 / g) + mod(t * r1, M) * (m2 / g), M), M};
}

pair<ll, ll> crt(const vector<ll> &r, const vector<ll> &m) {
    pair<ll, ll> ret = {0, 1};
    int n = m.size();
    for(int i = 0; i < n; i++) {
        ret = crt(ret.first, ret.second, r[i], m[i]);
        if(ret.second == -1) break;
    }
    return ret;
}
