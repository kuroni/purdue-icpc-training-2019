#define pt complex<double>
#define x real()
#define y imag()
#define dot(u, v) (conj(u) * (v)).x
#define cross(u, v) (conj(u) * (v)).y

const double EPS = 1e-12;
const pt I(0, 1);

istream &operator>>(istream &is, pt &p) {
    double X, Y;
    is >> X >> Y;
    p = {X, Y};
    return is;
}

// Project point p onto the line (a, b)
pt pjline(pt a, pt b, pt p) {
    b -= a, p -= a;
    return a + b * (p / b).x;
}

// Closest point in segment [a, b] to point p
pt pjseg(pt a, pt b, pt p) {
    b -= a, p -= a;
    return a + b * clamp((p / b).x, 0.0, 1.0);
}

// Reflect point p across the line (a, b)
pt reflect(pt a, pt b, pt p) {
    return 2.0 * pjline(a, b, p) - p;
}

// check if lines (a, b) and (c, d) are parallel
bool parallel(pt a, pt b, pt c, pt d) {
    return abs(cross(b - a, d - c)) < EPS;
}

// check if segments [a, b] and [c, d] intersect
// assumes they are not collinear
bool segseg(pt a, pt b, pt c, pt d) {
    return cross(b - a, d - a) * cross(b - a, c - a) < EPS &&
           cross(d - c, a - c) * cross(d - c, b - c) < EPS;
}

// intersection of lines (a, b) and (c, d)
// assumes they are not parallel
pt lineline(pt a, pt b, pt c, pt d) {
    b -= a, d -= c, c -= a;
    return a + b * cross(c, d) / cross(b, d);
}

// circumcenter of triangle (a, b, c)
pt circumcenter(pt a, pt b, pt c) {
    b = 0.5 * (a + b);
    c = 0.5 * (a + c);
    return lineline(b, b + (b - a) * I, c, c + (c - a) * I);
}

// check if point q is inside polygon v.
// does not handle boundary case, use onpoly for that
bool inpoly(const vector<pt> &v, pt q) {
    bool c = false;
    int n = v.size();
    for(int i = 0; i < n; i++) {
        pt p1 = v[i];
        pt p2 = v[(i + 1) % n];
        if(p2.y < p1.y) swap(p1, p2);
        c ^= (p1.y <= q.y && q.y < p2.y && cross(q - p1, p2 - p1) < 0);
    }
    return c;
}

// check if point q is on boundary of polygon v
bool onpoly(const vector<pt> &v, pt q) {
    int n = v.size();
    for(int i = 0; i < n; i++) {
        if(norm(q - pjseg(v[i], v[(i + 1) % n], q)) < EPS) {
            return true;
        }
    }
    return false;
}

// find intersection points of line (a, b) and circle (c, r)
// handles tangency as two very close intersection points
vector<pt> linecircle(pt a, pt b, pt c, double r) {
    pt p = pjline(a, b, c) - c;
    if(norm(p) > r * r + EPS) return {};
    pt v = sqrt(max(r * r - norm(p), 0.0)) * p * I;
    return {c + p + v, c + p - v};
}

// find intersection points of circles (a, r) and (b, R)
vector<pt> circlecircle(pt a, pt b, double r, double R) {
    double d = abs(b - a);
    if(d > r + R || d + min(r, R) < max(r, R)) return {};
    double X = (d * d - R * R + r * r) / (2 * d);
    pt p(X, sqrt(max(0.0, r * r - X * X)));
    pt v = (b - a) / d;
    return {a + v * p, a + v * conj(p)};
}

// returns signed area of polygon v.
// sign depends on orientation
double polyarea(const vector<pt> &v) {
    double area = 0;
    int n = v.size();
    for(int i = 0; i < n; i++) {
        area += cross(v[i], v[(i + 1) % n]);
    }
    return 0.5 * area;
}

// centroid of a polygon v. center of gravity
pt centroid(const vector<pt> &v) {
    pt c = 0;
    double scale = 6 * polyarea(v);
    int n = v.size();
    for(int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        c += (v[i] + v[j]) * cross(v[i], v[j]);
    }
    return c / scale;
}