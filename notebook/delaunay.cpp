
#include <bits/stdc++.h>

using namespace std;

// A circle and triangle in the Delaunay triangulation
// p = indices of three points of the triangle
// c = circumcircle, r = radius
struct circ {
    pt c;
    double r;
    int p[3];
    circ(const array<int, 3> &i, const vector<pt> &v) {
        c = circumcenter(v[i[0]], v[i[1]], v[i[2]]);
        r = abs(v[i[0]] - c);
        copy(i.begin(), i.end(), p);
    }
};

// Delaunay triangulation of a set of points v.
// Assumes the first three points of v form a
// super-triangle containing all the other points.
// Implementation is based on Bowyer-Watson in O(n^2) time.
vector<circ> delaunay(const vector<pt> &v) {
    vector<circ> tri = {circ({0, 1, 2}, v)};
    vector<pair<int, int> > poly;
    map<pair<int, int>, int> edge;
    int n = v.size();
    for(int i = 3; i < n; i++) {
        pt p = v[i];
        int d = tri.size(), b = 0;
        edge.clear(), poly.clear();
        for(int j = 0; j < d; j++) {
            if(abs(p - tri[j].c) < tri[j].r) {
                b++;
                int *p = tri[j].p;
                edge[{p[0], p[1]}]++;
                edge[{p[0], p[2]}]++;
                edge[{p[1], p[2]}]++;
            }else {
                tri[j - b] = tri[j];
            }
        }
        for(auto &e : edge) {
            if(e.second == 1) {
                poly.push_back(e.first);
            }
        }
        tri.erase(tri.end() - b, tri.end());
        for(auto &e : poly) {
            tri.push_back(circ({e.first, e.second, i}, v));
        }
    }
    return tri;
}

// Corresponding Voronoi diagram for a Delaunay triangulation tri.
// Representation is an adjacency list of the graph of circumcenters.
// Super-triangle 
vector<vector<int> > makeVoronoi(const vector<circ> &tri) {
    int arr[6];
    int d = tri.size();
    vector<vector<int> > adj(d);
    for(int i = 0; i < d; i++) {
        circ c1 = tri[i];
        for(int j = i + 1; j < d; j++) {
            circ c2 = tri[j];
            auto it = set_intersection(c1.p, c1.p + 3, c2.p, c2.p + 3, arr);
            if(it - arr == 2) {
                adj[i].push_back(j);
            }
        }
    }
    return adj;
}

const double INF = 1e5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pt> v;
    v.push_back({-2 * INF, -INF});
    v.push_back({2 * INF, -INF});
    v.push_back({0, INF});
    for(int i = 0; i < n; i++) {
        pt p;
        cin >> p;
        v.push_back(p);
    }
    vector<circ> tri = delaunay(v);
    vector<vector<int> > adj = makeVoronoi(tri);
}
