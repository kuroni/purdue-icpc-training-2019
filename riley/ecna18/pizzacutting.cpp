
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-10;
double r, dx, dy, x, y, p;
double X1, X2, Y1, Y2;
double segx[2], segy[2];

vector<double> polyx;
vector<double> polyy;
vector<int> inside;

bool inCircle(double x, double y) {
    return x * x + y * y < r * r;
}

int intersections(double _x1, double _y1, double _x2, double _y2) {
    double dx = _x2 - _x1;
    double dy = _y2 - _y1;
    double a = dx * dx + dy * dy;
    double b = 2 * _x1 * dx + 2 * _y1 * dy;
    double c = _x1 * _x1 + _y1 * _y1 - r * r;
    double disc = b * b - 4 * a * c;
    if(disc < 0) {
        return 0;
    }
    double s = sqrt(disc);
    double t1 = (-b + s) / (2 * a);
    double t2 = (-b - s) / (2 * a);
    if(t1 > t2) {
        swap(t1, t2);
    }
    int segs = 0;
    if(-EPS < t1 && t1 < 1 + EPS) {
        segx[0] = _x1 + t1 * dx;
        segy[0] = _y1 + t1 * dy;
        segs++;
    }
    if(-EPS < t2 && t2 < 1 + EPS) {
        segx[segs] = _x1 + t2 * dx;
        segy[segs] = _y1 + t2 * dy;
        segs++;
    }
    return segs;
}
double polyArea() {
    int n = polyx.size();
    double area = 0;
    for(int i = 0; i < n; i++) {
        double _x1 = polyx[i];
        double _y1 = polyy[i];
        double _x2 = polyx[(i + 1) % n];
        double _y2 = polyy[(i + 1) % n];
        area += (_x1 - _x2) * (_y1 + _y2) / 2;
    }
    return area;
}
double arcArea(double _x1, double _y1, double _x2, double _y2) {
    double theta1 = atan2(_y1, _x1);
    double theta2 = atan2(_y2, _x2);
    double dtheta = theta2 - theta1;
    if(dtheta < 0) {
        dtheta += 2 * M_PI;
    }
    double ans = (r * r / 2) * (dtheta - sin(dtheta));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> r >> dx >> dy >> x >> y >> p;
    
    // bounding box of pizza
    X1 = x - ceil((x + r) / dx) * dx;
    Y1 = y - ceil((y + r) / dy) * dy;
    X2 = x + ceil((r - x) / dx) * dx;
    Y2 = y + ceil((r - y) / dy) * dy;

    double cornersx[4], cornersy[4];
    vector<double> areas;
    double maxarea = -1;

    for(x = X1; x < X2; x += dx) {
        for(y = Y1; y < Y2; y += dy) {
            polyx.clear();
            polyy.clear();
            inside.clear();
            bool in = inCircle(x, y);

            cornersx[0] = x;        cornersy[0] = y;
            cornersx[1] = x + dx;   cornersy[1] = y;
            cornersx[2] = x + dx;   cornersy[2] = y + dy;
            cornersx[3] = x;        cornersy[3] = y + dy;
            
            for(int i = 0; i < 4; i++) {
                if(inCircle(cornersx[i], cornersy[i])) {
                    polyx.push_back(cornersx[i]);
                    polyy.push_back(cornersy[i]);
                    inside.push_back(-1);
                }
                int n = intersections(cornersx[i], cornersy[i],
                        cornersx[(i + 1) % 4], cornersy[(i + 1) % 4]);
                for(int j = 0; j < n; j++) {
                    polyx.push_back(segx[j]);
                    polyy.push_back(segy[j]);
                    inside.push_back(in ? 0 : 1);
                    in = !in;
                }
            }

            // now we have a polygon of the corners inside the circle
            // and the points intersecting the circle
            // they come already in clockwise order
            if(polyx.size() == 0) {
                continue;
            }
            double area = (polyx.size() >= 3 ? polyArea() : 0);
            int n = polyx.size();
            
            for(int i = 0; i < n; i++) {
                double px = polyx[i];
                double py = polyy[i];
                double px2 = polyx[(i + 1) % n];
                double py2 = polyy[(i + 1) % n];
                if(inside[i] == 0 && inside[(i + 1) % n] == 1) {
                    // circle intersection point
                    area += arcArea(px, py, px2, py2);
                }
            }
            areas.push_back(area);
            maxarea = max(maxarea, area);
        }
    }
    
    int cnt = 0;
    for(double area : areas) {
        if(area > EPS && area / maxarea - p < 1e-6) {
            cnt++;
        }
    }
    cout << cnt << endl;
}
