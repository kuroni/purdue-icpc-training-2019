#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int N = 255;
const int NONE = 0, HORZ = 1, VERT = 2;
int m, n, r, c;
int a[N][N];
int state[N][N];
bool visited[N][N];
int ex, ey;
stack<int> st;
int depth[N][N];
pair<int, int> par[N][N];

bool bfs(int x, int y) {
    queue<pair<int, int> > q;
    q.push({x, y});
    visited[x][y] = true;
    while(!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        x = p.first;
        y = p.second;
        if(x == r && y == c) {
            return true;
        }

        vector<pair<int, int> > v;
        if(x + 2 < m && state[x + 1][y] == HORZ && a[x + 2][y] != -2) {
            v.push_back({a[x + 1][y], 1});
        }
        if(x - 2 >= 0 && state[x - 1][y] == HORZ && a[x - 2][y] != -2) {
            v.push_back({a[x - 1][y], 2});
        }
        if(y + 2 < n && state[x][y + 1] == VERT && a[x][y + 2] != -2) {
            v.push_back({a[x][y + 1], 3});
        }
        if(y - 2 >= 0 && state[x][y - 1] == VERT && a[x][y - 2] != -2) {
            v.push_back({a[x][y - 1], 4});
        }
        sort(v.begin(), v.end());

        for(pair<int, int> pa : v) {
            switch(pa.second) {
            case 1:
                if(!visited[x + 2][y]) {
                    depth[x + 2][y] = depth[x][y] + 1;
                    par[x + 2][y] = p;
                    visited[x + 2][y] = true;
                    q.push({x + 2, y});
                }
                break;
            case 2:
                if(!visited[x - 2][y]) {
                    depth[x - 2][y] = depth[x][y] + 1;
                    par[x - 2][y] = p;
                    visited[x - 2][y] = true;
                    q.push({x - 2, y});
                }
                break;
            case 3:
                if(!visited[x][y + 2]) {
                    depth[x][y + 2] = depth[x][y] + 1;
                    par[x][y + 2] = p;
                    visited[x][y + 2] = true;
                    q.push({x, y + 2});
                }
                break;
            case 4:
                if(!visited[x][y - 2]) {
                    depth[x][y - 2] = depth[x][y] + 1;
                    par[x][y - 2] = p;
                    visited[x][y - 2] = true;
                    q.push({x, y - 2});
                }
                break;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
            if(a[i][j] == -1) {
                ex = i, ey = j;
            }
        }
    }
    cin >> r >> c;
    r--; c--;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if((i + j + r + c) % 2 == 1 && a[i][j] >= 0) {
                if((i > 0 && a[i - 1][j] == a[i][j]) || (i < m - 1 && a[i + 1][j] == a[i][j])) {
                    state[i][j] = HORZ;
                }else {
                    state[i][j] = VERT;
                }
            }
        }
    }
    if(bfs(ex, ey)) {
        pair<int, int> p;
        while(r != ex || c != ey) {
            p = par[r][c];
            int x = (r + p.first) / 2;
            int y = (c + p.second) / 2;
            // cout << a[x][y] << " ";
            st.push(a[x][y]);
            r = p.first;
            c = p.second;
        }
        while(!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    }else {
        cout << "impossible" << endl;
    }
}