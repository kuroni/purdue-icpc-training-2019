#include <bits/stdc++.h>

using namespace std;

const int N = 105;
int n, m;
string str;
int _dx[N][N], _dy[N][N];

// cells that point to (i, j)
vector<pair<int, int> > adj[N][N];
bool visited[N][N];
int distend[N][N];

bool inbounds(int x, int y) {
    return 0 <= x && x < m && 0 <= y && y < n;  
}

void dfs(int x, int y) {
    visited[x][y] = true;
    for(auto p : adj[x][y]) {
        if(!visited[p.first][p.second]) {
            distend[p.first][p.second] = distend[x][y] + 1;
            dfs(p.first, p.second);
        }
    }
}

int minlen = 1e9;
int optx, opty;
int optdx, optdy;

void finaldfs(int x, int y, int s) {
    if(x == m - 1 && y == n - 1) return;
    visited[x][y] = true;
    int M = 1e9, Md, Mdx, Mdy;
    for(int i = x; i < m; i++) {
        if(distend[i][y] < M) {
            M = distend[i][y];
            Md = i - x;
            Mdx = i - x;
            Mdy = 0;
        }else if(distend[i][y] == M) {
            if (i - x < Md) {
                Md = i - x;
                Mdx = i - x;
                Mdy = 0;
            }
        }
    }
    for(int j = 0; j < y; j++) {
        if(distend[x][j] < M) {
            M = distend[x][j];
            Md = y - j;
            Mdx = 0;
            Mdy = j - y;
        }else if (distend[x][j] == M) {
            if (y - j < Md) {
                Md = y - j;
                Mdx = 0;
                Mdy = j - y;
            }
        }
    }
    for(int j = y; j < n; j++) {
        if(distend[x][j] < M) {
            M = distend[x][j];
            Md = j - y;
            Mdx = 0;
            Mdy = j - y;
        }else if (distend[x][j] == M) {
            if (j - y < Md) {
                Md = j - y;
                Mdx = 0;
                Mdy = j - y;
            }
        }
    }
    for(int i = 0; i < x; i++) {
        if(distend[i][y] < M) {
            M = distend[i][y];
            Md = x - i;
            Mdx = i - x;
            Mdy = 0;
        }else if(distend[i][y] == M) {
            if (x - i < Md) {
                Md = x - i;
                Mdx = i - x;
                Mdy = 0;
            }
        }
    }
    int t = M + 1 + s;
    if(t < minlen) {
        minlen = t;
        optx = x, opty = y, optdx = Mdx, optdy = Mdy;
    }else if (t == minlen) {
        if (y < opty) { optx = x, opty = y, optdx = Mdx, optdy = Mdy; }
        else if (y == opty) {
            if (x < optx) { optx = x, opty = y, optdx = Mdx, optdy = Mdy; }
        }
    }
    if(inbounds(x + _dx[x][y], y + _dy[x][y]) && !visited[x + _dx[x][y]][y + _dy[x][y]]) {
        finaldfs(x + _dx[x][y], y + _dy[x][y], s + 1);
    }
}

void clearvisited() {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }
}
void cleartest() {
    clearvisited();
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            adj[i][j].clear();
            distend[i][j] = 1e9;
            _dx[i][j] = 0;
            _dy[i][j] = 0;
            minlen = 1e9;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for(int te = 1; ; te++) {
        cin >> n >> m;
        if(n == 0) break;
        cleartest();
        for(int j = 0; j < n; j++) {
            for(int i = 0; i < m; i++) {
                if(i == m - 1 && j == n - 1) break;
                cin >> str;
                char c = str.back();
                stringstream ss;
                ss << str.substr(0, str.length() - 1);
                int len;
                ss >> len;
                _dx[i][j] = len * ((c == 'E') - (c == 'W'));
                _dy[i][j] = len * ((c == 'S') - (c == 'N'));
                int i2 = i + _dx[i][j];
                int j2 = j + _dy[i][j];
                if(inbounds(i2, j2)) {
                    adj[i2][j2].push_back({i, j});
                }
            }
        }
        distend[m - 1][n - 1] = 0;
        dfs(m - 1, n - 1);
        int len = distend[0][0];
        clearvisited();
        finaldfs(0, 0, 0);
        
        cout << "Case " << te << ": ";
        if(minlen > 1e9 - 5) {
            cout << "impossible" << endl;
            continue;
        }
        if(minlen < len) {
            cout << opty << " " << optx << " " << max(abs(optdx), abs(optdy)) << (optdx > 0 ? 'E' : optdx < 0 ? 'W' : optdy > 0 ? 'S' : 'N') << " " << minlen << endl;
        }else {
            cout << "none " << len << endl;
        }
        /*
        for(int j = 0; j < n; j++) {
            for(int i = 0; i < m; i++) {
                cout << diststart[i][j] << " ";
            }
            cout << endl;
        }
        */
    }
}