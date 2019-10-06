
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const double EPS = 1e-10;

struct PT {
    double x, y;
    PT(double x, double y): x(x), y(y) {}
    double len3() const {
        return fabs(x * x * x) + fabs(y * y * y);
    }
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
};

struct umbra {
    ll x, y, b;
    umbra(ll x, ll y, ll b): x(x), y(y), b(b) {}
    bool inside(PT p) {
        return (PT(x, y) - p).len3() <= b;
    }
};

struct quad {
    ll x1, y1, x2, y2;
    bool uncovered;
    bool isSplit;
    quad *q[4];
    quad(ll x1, ll y1, ll x2, ll y2): x1(x1), y1(y1), x2(x2), y2(y2) {
        uncovered = true;
        isSplit = false;
        q[0] = q[1] = q[2] = q[3] = NULL;
    }
    bool shouldSplit(umbra u) {
        if(!isSplit && !uncovered) return false;
        if(x1 == x2 && y1 == y2) {
            if(u.inside(PT(x1, y1))) {
                uncovered = false;
            }
            return false;
        }
        bool b1 = u.inside(PT(x1, y1));
        bool b2 = u.inside(PT(x2, y1));
        bool b3 = u.inside(PT(x1, y2));
        bool b4 = u.inside(PT(x2, y2));
        if(b1 && b2 && b3 && b4) {
            isSplit = false;
            q[0] = q[1] = q[2] = q[3] = NULL;
            uncovered = false;
            return false;
        }
        ll x = u.x < x1 ? x1 : u.x > x2 ? x2 : u.x;
        ll y = u.y < y1 ? y1 : u.y > y2 ? y2 : u.y;
        bool b = u.inside(PT(x, y));
        if(b) {
            uncovered = false;
        }
        return b || isSplit;
    }
    void split() {
        if(isSplit || (x1 == x2 && y1 == y2)) return;
        isSplit = true;
        uncovered = false;
        ll mx = x1 + (x2 - x1) / 2;
        ll my = y1 + (y2 - y1) / 2;
        if(x1 == x2) {
            q[0] = new quad(x1, y1, x1, my);
            q[1] = new quad(x1, my + 1, x1, y2);
        }else if(y1 == y2) {
            q[0] = new quad(x1, y1, mx, y1);
            q[1] = new quad(mx + 1, y1, x2, y1);
        }else {
            q[0] = new quad(x1, y1, mx, my);
            q[1] = new quad(mx + 1, y1, x2, my);
            q[2] = new quad(x1, my + 1, mx, y2);
            q[3] = new quad(mx + 1, my + 1, x2, y2);
        }
    }
    ll getSum() {
        if(isSplit) {
            ll sum = 0;
            for(int i = 0; i < 4; i++) {
                if(q[i] != NULL) {
                    sum += q[i]->getSum();
                }
            }
            return sum;
        }else if(uncovered) {
            return (x2 - x1 + 1) * (y2 - y1 + 1);
        }
        return 0;
    }
};

ll n, k, x, y, b;
quad *head;

void addUmbra(umbra u, quad *q) {
    if(q == NULL) return;
    if(q->shouldSplit(u)) {
        q->split();
        for(int i = 0; i < 4; i++)
            addUmbra(u, q->q[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    head = new quad(0, 0, n, n);
    for(int i = 0; i < k; i++) {
        cin >> x >> y >> b;
        addUmbra(umbra(x, y, b), head);
    }
    cout << head->getSum() << endl;
}
