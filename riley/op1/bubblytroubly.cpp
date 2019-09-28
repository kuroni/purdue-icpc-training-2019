
#include <bits/stdc++.h>

#define ll long long
using namespace std;

struct PT;
struct glass;

const double EPS = 1e-10;
const int N = 25;

struct PT {
    double x;
    double y;
    PT(): x(0), y(0) {}
    PT(double x, double y): x(x), y(y) {}
    PT operator-(const PT &p) const {
        return PT(x - p.x, y - p.y);
    }
    double len() {
        return hypot(x, y);
    }
    bool operator<(const PT &p) const {
        return x != p.x ? x < p.x : y < p.y;
    }
};
struct glass {
    PT center;
    // z value, radius, and volume
    int z, r, v;
    // amount of liquid in glass
    double amt;
    // rate of water pouring into glass
    double rate;
    // pair.second = index of glass this one can pour down to
    // pair.first = percentage of overflow that goes to this glass
    vector<pair<double, int> > adj;
    glass(PT center, int z, int r, int v): center(center), z(z), r(r), v(v) {
        amt = rate = 0;
    }
    bool operator<(const glass &g) const {
        return z != g.z ? z > g.z : center < g.center;
    }
};

int n, x, y, z, v, r;
vector<glass> vglasses;
pair<double, double> arcs[N][N];
bool overflow[N][N];
double overflowamt[N][N];

// put angle in [0, 2pi) range
double angnorm(double ang) {
    while(ang < 0) {
        ang += 2 * M_PI;
    }
    while(ang >= 2 * M_PI) {
        ang -= 2 * M_PI;
    }
    return ang;
}

// arc of g1 that overlaps with g2
bool computeArc(int i, int j) {
    glass g1 = vglasses[i];
    glass g2 = vglasses[j];

    double dist = (g1.center - g2.center).len();
    // little or no overlap
    if(dist < EPS || g1.z <= g2.z || dist > g1.r + g2.r - EPS ||
            dist + g2.r < g1.r + EPS || dist + g1.r < g2.r + EPS) {
        return false;
    }
    double h1 = g1.center.x, h2 = g2.center.x;
    double k1 = g1.center.y, k2 = g2.center.y;
    double dh = h1 - h2, dk = k1 - k2;
    double r1 = g1.r, r2 = g2.r;

    double A = 2 * r1 * dh;
    double B = 2 * r1 * dk;
    double C = r2 * r2 - r1 * r1 - dh * dh - dk * dk;

    double R = hypot(A, B);
    double k = atan2(A, B);
    double alpha = M_PI - asin(C / R);
    double ang1 = angnorm(alpha - k);
    double ang2 = angnorm(M_PI - alpha - k);
    while(ang1 < 0) ang1 += 2 * M_PI;
    while(ang1 >= 2 * M_PI) ang1 -= 2 * M_PI;
    while(ang2 < 0) ang2 += 2 * M_PI;
    while(ang2 >= 2 * M_PI) ang2 -= 2 * M_PI;

    arcs[i][j] = {ang1, ang2};
    return true;
}

// compute overflows from each glass g to all glasses below it
void computeOverflow() {
    for(int i = 0; i < n; i++) {
        glass g1 = vglasses[i];
        vector<double> angles = {0, 2 * M_PI};
        for(int j = i + 1; j < n; j++) {
            if(overflow[i][j] = computeArc(i, j)) {
                angles.push_back(arcs[i][j].first);
                angles.push_back(arcs[i][j].second);
            }
        }
        sort(angles.begin(), angles.end());
        // look at all subsegments on the circle
        // and assign overflows
        int nangles = angles.size();
        for(int k = 1; k < nangles; k++) {
            double ang1 = angles[k - 1];
            double ang2 = angles[k];

            double d1 = ang2 - ang1;
            for(int j = i + 1; j < n; j++) {
                glass g2 = vglasses[j];
                if(g1.z == g2.z || ((g1.center - g2.center).len() < EPS && g1.r >= g2.r)) {
                    continue;
                }else if(g1.z > g2.z && (g1.center - g2.center).len() + g1.r < g2.r + EPS) {
                    overflowamt[i][j] += d1 / (2 * M_PI);
                    break;
                }else if(overflow[i][j]) {
                    double theta1 = arcs[i][j].first;
                    double theta2 = arcs[i][j].second;
                    // check if the segment [ang1, ang2] is contained in [theta1, theta2]
                    double d2 = angnorm(ang1 - theta1);
                    double d3 = angnorm(theta2 - ang2);
                    double d4 = angnorm(theta2 - theta1);
                    if(fabs(d1 + d2 + d3 - d4) < EPS) {
                        overflowamt[i][j] += d1 / (2 * M_PI);
                        break;
                    }
                }
            }
        }
        for(int j = i + 1; j < n; j++) {
            if(overflowamt[i][j] > EPS) {
                vglasses[i].adj.push_back({overflowamt[i][j], j});
            }
        }
    }
}

void increaseRate(int idx, double drate) {
    vglasses[idx].rate += drate;
    // trickle down if full
    if(vglasses[idx].amt > vglasses[idx].v + 0.5) {
        for(pair<double, int> p : vglasses[idx].adj) {
            increaseRate(p.second, drate * p.first);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x >> y >> z >> r >> v;
        vglasses.push_back(glass(PT(x, y), z, r, v));
    }
    sort(vglasses.begin(), vglasses.end());

    computeOverflow();
    for(int i = 0; i < n; i++) {
        glass g1 = vglasses[i];
    }

    // run simulation until all glasses are full
    // glasses that are currently having liquid poured into them
    // initially, only the highest glass
    set<int> sleaf;
    sleaf.insert(0);
    vglasses[0].rate = 100; // milliliters per second
    double t = 0;
    while(sleaf.size()) {
        double mintime = DBL_MAX;
        int minidx = -1;
        for(int i : sleaf) {
            glass g = vglasses[i];
            double timetofill = max((double) 0, (g.v - g.amt) / g.rate);
            if(timetofill < mintime) {
                mintime = timetofill;
                minidx = i;
            }
        }
        if(minidx == -1) break;
        // fast forward mintime seconds
        t += mintime;
        for(int i : sleaf) {
            vglasses[i].amt += vglasses[i].rate * mintime;
        }
        vglasses[minidx].amt = vglasses[minidx].v + 1;
        sleaf.erase(minidx);
        for(pair<double, int> p : vglasses[minidx].adj) {
            double per = p.first;
            int idx = p.second;
            // don't insert if it's already full
            if(vglasses[idx].amt < vglasses[idx].v + 0.5) {
                vglasses[idx].rate += vglasses[minidx].rate * per;
                sleaf.insert(idx);
            }else {
                increaseRate(idx, vglasses[minidx].rate * per);
            }
        }
    }
    // check that all glasses are full, otherwise invalid
    for(int i = 0; i < n; i++) {
        if(vglasses[i].amt < vglasses[i].v + 0.5) {
            cout << "Invalid" << endl;
            return 0;
        }
    }

    cout << fixed << setprecision(2);
    cout << t << endl;
}
