
#include <bits/stdc++.h>

#define ll long long
using namespace std;

struct PT {
    int x, y;
    PT(): x(0), y(0) {}
    PT(int x, int y): x(x), y(y) {}
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
    double len2() const {
        return x * x + y * y;
    }
};

struct circ {
    PT center;
    int r;
    circ(PT center, int r): center(center), r(r) {}
};

const int N = 205;
int n, x, y, r;
vector<circ> vcircs;
vector<int> adj[N];

int par[N], sz[N];

int find(int x) {
    return par[x] == -1 ? x : par[x] = find(par[x]);
}
void join(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) return;
    if(sz[a] < sz[b]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    par[b] = a;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x >> y >> r;
        vcircs.push_back(circ(PT(x, y), r));
    }
    // n =     left border
    // n + 1 = right border
    fill(par, par + N, -1);
    fill(sz, sz + N, 1);
    for(int i = 0; i < n; i++) {
        circ c1 = vcircs[i];
        for(int j = 0; j < i; j++) {
            circ c2 = vcircs[j];
            // intersecting
            if((c1.center - c2.center).len2() <= (c1.r + c2.r) * (c1.r + c2.r)) {
                join(i, j);
            }
        }
        if(c1.center.x - c1.r <= 0) {
            join(i, n);
        }
        if(c1.center.x + c1.r >= 200) {
            join(i, n + 1);
        }
        if(find(n) == find(n + 1)) {
            cout << i << endl;
            return 0;
        }
    }
    cout << n << endl;
}