
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int DEG = 360 * 60 * 60;

int m, r, n, deg, mnt, sec;
bool arr[DEG];

double area(int r, int ang) {
    return (M_PI * r) * r * ((double) ang) / DEG;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m;
    cout << fixed << setprecision(6);
    for(int i = 0; i < m; i++) {
        cin >> r >> n >> deg >> mnt >> sec;
        int ang = 60 * 60 * deg + 60 * mnt + sec;
        if(n == 1 || ang == 0) {
            cout << area(r, DEG) << endl;
            continue;
        }
        int g = __gcd(DEG, ang);
        int period = DEG / g;
        if(n >= period) {
            n = period;
        }
        fill(arr, arr + DEG, false);
        int prev = 0;
        int maxpos = 0;
        for(int i = 0; i < n; i++) {
            maxpos = max(maxpos, prev);
            arr[prev] = true;
            prev = (prev + ang) % DEG;
        }
        prev = maxpos;
        int maxdiff = 0;
        for(int i = 0; i < DEG; i++) {
            if(arr[i]) {
                maxdiff = max(maxdiff, (i - prev + DEG) % DEG);
                prev = i;
            }
        }
        cout << area(r, maxdiff) << endl;
    }
}