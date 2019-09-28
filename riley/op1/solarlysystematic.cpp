
#include <bits/stdc++.h>

#define ll long long
using namespace std;

struct PT;
struct PTmod;
struct planet;

const int N = 105;
int n, nx, ny, nz, m, x, y, z, vx, vy, vz;
vector<planet> vplanets;

ll mod(ll a, ll m) {
    return ((a % m) + m) % m;
}

// actual point, no modding. Needed for velocity
struct  PT {
    ll x, y, z;
    PT(): x(0), y(0), z(0) {}
    PT(ll X, ll Y, ll Z): x(X), y(Y), z(Z) {}
    PT operator+(const PT &p) const {
        return PT(x + p.x, y + p.y, z + p.z);
    }
    bool operator<(const PT &p) const {
        return x != p.x ? x < p.x : y != p.y ? y < p.y : z < p.z;
    }
    PT operator*(const int c) const {
        return PT(x * c, y * c, z * c);
    }
};

// point in space, coordinates modded by nx, ny, nz
struct PTmod {
    int x, y, z;
    PTmod(): x(0), y(0), z(0) {}
    PTmod(ll X, ll Y, ll Z) {
        x = mod(X, nx);
        y = mod(Y, ny);
        z = mod(Z, nz);
    }
    PTmod operator+(const PTmod &p) const {
        return PTmod(x + p.x, y + p.y, z + p.z);
    }
    PTmod operator+(const PT &p) const {
        return PTmod(x + p.x, y + p.y, z + p.z);
    }
    bool operator!=(const PTmod &p) const {
        return x != p.x || y != p.y || z != p.z;
    }
    bool operator<(const PTmod &p) const {
        return x != p.x ? x < p.x : y != p.y ? y < p.y : z < p.z;
    }
};

struct planet {
    PTmod pos;
    PT vel;
    int mass;
    planet(PTmod pos, PT vel, int mass): pos(pos), vel(vel), mass(mass) {}
    // ordering of planets in output
    bool operator<(const planet &p) const {
        return mass != p.mass ? mass > p.mass : pos < p.pos;
    }
    void print() {
        cout << mass << " " << pos.x << " " << pos.y << " " << pos.z << " " << vel.x << " " << vel.y << " " << vel.z;
    }
};

bool cmpByPos(const planet &p1, const planet &p2) {
    if(p1.pos < p2.pos || p2.pos < p1.pos) {
        return p1.pos < p2.pos;
    }
    return p1.vel < p2.vel;
}

// merge planets that share the same position
vector<planet> merge(vector<planet> vbefore) {
    // sort vbefore by position
    sort(vbefore.begin(), vbefore.end(), cmpByPos);
    vector<planet> vafter;
    
    int n = vbefore.size();
    PT newvel = vbefore.front().vel;
    int mass = vbefore.front().mass;
    PTmod lastpos = vbefore.front().pos;
    int numplanet = 1;
    for(int i = 1; i <= n; i++) {
        if(i == n || vbefore[i].pos != lastpos) {
            newvel = PT(newvel.x / numplanet, newvel.y / numplanet, newvel.z / numplanet);
            vafter.push_back(planet(lastpos, newvel, mass));
            numplanet = 0;
            newvel = PT();
            mass = 0;
            if(i == n) break;
        }
        numplanet++;
        mass += vbefore[i].mass;
        newvel = newvel + vbefore[i].vel;
        lastpos = vbefore[i].pos;
    }
    return vafter;
}

ll gcd(ll a, ll b) {
    while(b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
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

pair<ll, ll> CRT(ll m1, ll r1, ll m2, ll r2) {
    ll s, t;
    ll g = euclid(m1, m2, s, t);
    if(r1 % g != r2 % g) return {0, -1};
    
    ll MOD = m1 * m2;
    s = mod(s, MOD);
    r1 = mod(r1, MOD);
    t = mod(t, MOD);
    r2 = mod(r2, MOD);
    ll a1 = mod(mod(s * r2, MOD) * m1, MOD);
    ll a2 = mod(mod(t * r1, MOD) * m2, MOD);

    return {mod(a1 + a2, MOD) / g, MOD / g};
}
pair<ll, ll> CRT(const vector<ll> &m, const vector<ll> &r) {
    pair<ll, ll> ret = {r[0], m[0]};
    for(int i = 1; i < m.size(); i++) {
        ret = CRT(ret.second, ret.first, m[i], r[i]);
        if(ret.second == -1) break;
    }
    return ret;
}

ll mod_inverse(ll a, ll n) {
    ll x, y;
    ll g = euclid(a, n, x, y);
    if(g > 1) return -1;
    return mod(x, n);
}

// return next collision time of the planets, or
// LLONG_MAX if they never collide
// reduces to solving linear diophantine equation
// the collision time itself could be very large, so
// brute force won't work
ll collisiontime(planet p1, planet p2) {
    vector<ll> vm, vr;
    vector<ll> va = {p1.vel.x - p2.vel.x, p1.vel.y - p2.vel.y, p1.vel.z - p2.vel.z};
    vector<ll> vb = {p2.pos.x - p1.pos.x, p2.pos.y - p1.pos.y, p2.pos.z - p1.pos.z};
    vector<ll> vmod = {nx, ny, nz};
    for(int i = 0; i < 3; i++) {
        // va[i] * t = vb[i] (mod vmod[i])
        // convert to:
        // t = vr[i] (mod vm[i])
        va[i] = mod(va[i], vmod[i]);
        vb[i] = mod(vb[i], vmod[i]);
        if(va[i] == 0) {
            if(vb[i] == 0) {
                continue;
            }else {
                return LLONG_MAX;
            }
        }
        ll g = gcd(va[i], vmod[i]);
        if(mod(vb[i], g) != 0) {
            return LLONG_MAX;
        }
        vm.push_back(vmod[i] / g);
        vr.push_back(mod(mod_inverse(va[i] / g, vmod[i] / g) * (vb[i] / g), vmod[i] / g));
    }
    if(vm.empty()) {
        return -1;
    }
    pair<ll, ll> ans = CRT(vm, vr);
    if(ans.second == -1) return LLONG_MAX;
    
    if(p1.pos + p1.vel * ans.first != p2.pos + p2.vel * ans.first) {
        cout << "Really wrong answer" << endl;
    }

    return ans.first;
}

// find the next occuring collision and update planets
// return true if there is a collision in the future
bool update() {
    int n = vplanets.size();
    ll mintime = LLONG_MAX;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            mintime = min(mintime, collisiontime(vplanets[i], vplanets[j]));
        }
    }
    if(mintime == LLONG_MAX) {
        return false;
    }

    // go forward mintime seconds in the future and update planets
    for(int i = 0; i < n; i++) {
        vplanets[i].pos = vplanets[i].pos + vplanets[i].vel * mintime;
    }
    vplanets = merge(vplanets);

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> nx >> ny >> nz;
    for(int i = 0; i < n; i++) {
        cin >> m >> x >> y >> z >> vx >> vy >> vz;
        vplanets.push_back(planet(PTmod(x, y, z), PT(vx, vy, vz), m));
    }
    vplanets = merge(vplanets);

    while(update());

    sort(vplanets.begin(), vplanets.end());
    cout << vplanets.size() << endl;
    for(int i = 0; i < vplanets.size(); i++) {
        cout << "P" << i << ": ";
        vplanets[i].print();
        cout << endl;
    }
}
