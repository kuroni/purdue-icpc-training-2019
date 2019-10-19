 
#include <bits/stdc++.h>
#define ll long long
 
using namespace std;
 
int n, nx, ny;
ll r, c;
vector<ll> vx, vy;
set<pair<ll, ll>> s;
 
const int N = 1e4 + 5;
// bool arr[N][N];
bitset<N> arr[N];
int minr[N], maxr[N], minc[N], maxc[N];
 
void solve() {
    queue<pair<int, int>> q;
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) {
            if(arr[i].test(j)) {
                q.push({i, j});
            }
        }
    }
    while(q.size()) {
        pair<int, int> p = q.front();
        int r = p.first, c = p.second;
        q.pop();
        // travel in 4 directions
        // left
        if(c > minr[r]) {
            for(int cc = c - 1; !arr[r].test(cc); cc--) {
                minc[cc] = min(minc[cc], r);
                maxc[cc] = max(maxc[cc], r);
                q.push({r, cc});
                arr[r].set(cc);
            }
        }
        // right
        if(c < maxr[r]) {
            for(int cc = c + 1; !arr[r].test(cc); cc++) {
                minc[cc] = min(minc[cc], r);
                maxc[cc] = max(maxc[cc], r);
                q.push({r, cc});
                arr[r].set(cc);
            }
        }
        // up
        if(r > minc[c]) {
            for(int rr = r - 1; !arr[rr].test(c); rr--) {
                minr[rr] = min(minr[rr], c);
                maxr[rr] = max(maxr[rr], c);
                q.push({rr, c});
                arr[rr].set(c);
            }
        }
        // down
        if(r < maxc[c]) {
            for(int rr = r + 1; !arr[rr].test(c); rr++) {
                minr[rr] = min(minr[rr], c);
                maxr[rr] = max(maxr[rr], c);
                q.push({rr, c});
                arr[rr].set(c);
            }
        }
    }
}
 
void output() {
    /*cout << endl;
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) {
            cout << (arr[i][j] ? 'X' : '.') << ' ';
        }
        cout << endl;
    }
    */
    vector<pair<ll, ll>> vec;
    vec.push_back({vx[0], vy[minr[0]]});
    vec.push_back({vx[0], vy[maxr[0]] + 9});
    //vec.push_back({0, minr[0]});
    //vec.push_back({0, maxr[1]});
    for(int r = 1; r < nx; r++) {
        int c = maxr[r];
        if(c > maxr[r - 1]) {
            vec.push_back({vx[r], vy[maxr[r - 1]] + 9});
            vec.push_back({vx[r], vy[c] + 9});
        }else if(c < maxr[r - 1]) {
            vec.push_back({vx[r - 1] + 9, vy[maxr[r - 1]] + 9});
            vec.push_back({vx[r - 1] + 9, vy[c] + 9});
        }
    }
    //cout << "Got here" << endl;
    vec.push_back({vx[nx - 1] + 9, vy[maxr[nx - 1]] + 9});
    vec.push_back({vx[nx - 1] + 9, vy[minr[nx - 1]]});
    //vec.push_back(nx - 1, maxr[nx - 1]});
    //vec.push_back(nx - 1, minr[nx - 1]});
    for(int r = nx - 2; r >= 0; r--) {
        int c = minr[r];
        if(c < minr[r + 1]) {
            vec.push_back({vx[r] + 9, vy[minr[r + 1]]});
            vec.push_back({vx[r] + 9, vy[c]});
        }else if(c > minr[r + 1]) {
            vec.push_back({vx[r + 1], vy[minr[r + 1]]});
            vec.push_back({vx[r + 1], vy[c]});
        }
    }
    for(pair<ll, ll> &p : vec) {
        cout << p.first << " " << p.second << " ";
    }
    cout << endl;
}
