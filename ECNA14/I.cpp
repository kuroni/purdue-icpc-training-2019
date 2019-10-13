#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;

#define pt complex<double>
#define x real()
#define y imag()
#define dot(u, v) (conj(u) * (v)).x
#define cross(u, v) (conj(u) * (v)).y

const int N = 300, INF = 1E9 + 7;
const double EPS = 1e-10;
int cnt, ans, s, t, tr[N];
int we[N * N], xo[N * N];
bool vis[N];
queue<int> q;
vector<pair<int, int>> adj[N];

istream &operator>>(istream &is, pt &p) {
    double X, Y;
    is >> X >> Y;
    p = {X, Y};
    return is;
}

void add_edge(int u, int v, int w) {
    adj[u].push_back({v, cnt});
    we[cnt] = w; xo[cnt] = u ^ v;
    cnt++;
    adj[v].push_back({u, cnt});
    we[cnt] = 0; xo[cnt] = u ^ v;
    cnt++;
}

struct arc {
    pt c;
    double r;
    double t1, t2;
};

vector<pair<pt, pt> > segs;
vector<arc> arcs;
pt art[N], guard[N];
int alevel[N], glevel[N];
int n, m, a, g;

pt segIntersection(pt a, pt b, pt c, pt d) {
    b -= a;
    d = c - d;
    c -= a;
    return a + b * cross(c, d) / cross(b, d);
}
bool segsIntersect(pt a, pt b, pt c, pt d) {
    if(cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
    if(cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
    return true;
}

vector<pt> circleLine(pt a, pt b, pt c, double r) {
    b -= a;
    a -= c;
    double A = norm(b);
    double B = dot(a, b);
    double C = norm(a) - r * r;
    double D = B * B - A * C;
    if(D < -EPS) return {};
    return {c + a + b * (-B + sqrt(D + EPS)) / A, c + a + b * (-B - sqrt(D + EPS)) / A};
}

pt getCenter(pt p1, pt p2, pt D) {
    pt a = p1;
    pt b = p1 + D * pt(0, 1);
    pt c = (p1 + p2) / 2.0;
    pt d = c + (p2 - c) * pt(0, 1);
    return segIntersection(a, b, c, d);
}
pt pj(pt a, pt b, pt c) {
    double r = dot(c - a, b - a) / norm(b - a);
    return a + (b - a) * clamp(r, 0.0, 1.0);
}

double angnorm(double t) {
    while(t < 0) t += 2 * M_PI;
    while(t >= 2 * M_PI) t -= 2 * M_PI;
    return t;
}

bool onArc(arc A, pt p) {
    double t = arg(p - A.c);
    return angnorm(A.t2 - t) + angnorm(t - A.t1) < angnorm(A.t2 - A.t1) + EPS;
}

bool BFS() {
    while (!q.empty()) {
        q.pop();
    }
    fill(vis, vis + t + 1, false);
    for (q.push(s), vis[s] = true; !q.empty(); q.pop()) {
        int u = q.front();
        for (pair<int, int> &v : adj[u]) {
            if (!vis[v.fi] && we[v.se] > 0) {
                vis[v.fi] = true;
                tr[v.fi] = v.se;
                if (v.fi == t) {
                    return true;
                }
                q.push(v.fi);
            }
        }
    }
    return false;
}

int trace() {
    int u = t, mx = INF;
    while (u > 0) {
        int ind = tr[u];
        mx = min(mx, we[ind]);
        u ^= xo[ind];
    }
    u = t;
    while (u > 0) {
        int ind = tr[u];
        we[ind] -= mx;
        we[ind ^ 1] += mx;
        u ^= xo[ind];
    }
    return mx;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for(int te = 1; ; te++) {
        cin >> n >> a >> g;
        if(n == 0) break;
        s = 0; t = a + g + 1;
        for (int i = s; i <= t; i++) {
            adj[i].clear();
        }
        cnt = ans = 0;
        arcs.clear();
        segs.clear();
        for(int i = 0; i < n; i++) {
            cin >> m;
            vector<pair<char, pt> > chars;
            vector<pt> pts;
            for(int j = 0; j < m; j++) {
                pt w;
                char c;
                cin >> w >> c;
                pt dpos;
                if(c == 'c') {
                    cin >> dpos;
                }
                pts.push_back(w);
                chars.push_back({c, dpos});
            }
            for(int i = 0; i < m; i++) {
                pt p1 = pts[i];
                pt p2 = pts[(i + 1) % m];
                if(chars[i].first == 's') {
                    segs.push_back({p1, p2});
                }else {
                    pt c = getCenter(p1, p2, chars[i].second);
                    if(cross(chars[i].second, p2 - p1) > 0) {
                        swap(p1, p2);
                    }
                    arcs.push_back({c, abs(p1 - c), arg(p2 - c), arg(p1 - c)});
                }
            }
        }
        for(int i = 0; i < a; i++) {
            cin >> art[i] >> alevel[i];
            add_edge(s, i + 1, alevel[i]);
            ans += alevel[i];
        }
        for(int i = 0; i < g; i++) {
            cin >> guard[i] >> glevel[i];
            add_edge(a + i + 1, t, glevel[i]);
        }
        for(int i = 0; i < a; i++) {
            for(int j = 0; j < g; j++) {
                for(auto seg : segs) {
                    if(segsIntersect(seg.first, seg.second, art[i], guard[j])) {
                        goto endloop;
                    }
                }
                for(auto arcc : arcs) {
                    vector<pt> p = circleLine(art[i], guard[j], arcc.c, arcc.r);
                    for(pt mypt : p) {
                        pt p2 = pj(art[i], guard[j], mypt);
                        if(norm(p2 - mypt) > EPS) {
                            continue;
                        }
                        if(onArc(arcc, mypt)) {
                            goto endloop;
                        }
                    }
                }
                add_edge(i + 1, a + j + 1, 1);
                endloop:;
            }
        }
        while (BFS()) {
            ans -= trace();
        }
        cout << "Case " << te << ": " << (ans == 0 ? "Yes\n" : "No\n");
    }
}