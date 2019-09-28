
#include <bits/stdc++.h>

#define ll long long
using namespace std;

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

map<char, int> dirmap = {{'N', NORTH}, {'S', SOUTH}, {'E', EAST}, {'W', WEST}};
string str;

const int N = 105;
int n, m;

struct PT {
    int x, y;
    PT(): x(0), y(0) {}
    PT(int x, int y): x(x), y(y) {}
    bool inBounds() {
        return 0 <= x && x < n && 0 <= y && y < m;
    }
    PT move(int dir) const {
        return PT(x + dx[dir], y + dy[dir]);
    }
};

// points of lemmings attempting to go to this cell
vector<PT> adj[N][N];
bool blocked[N][N];

struct lemming {
    int agenda[4];
    int diridx;
    PT pt;
    lemming(string str, PT p) {
        pt = p;
        for(int k = 0; k < 4; k++) {
            agenda[k] = dirmap[str[k]];
        }
        diridx = 0;
    }
    PT target() {
        return pt.move(agenda[diridx]);
    }
};

vector<lemming> vlems;

// block this point and any chain of lemmas trying to reach it
void block(PT p) {
    if(blocked[p.x][p.y]) return;
    blocked[p.x][p.y] = true;
    for(PT p2 : adj[p.x][p.y]) {
        block(p2);
    }
}

void update() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            blocked[i][j] = false;
            adj[i][j].clear();
        }
    }
    for(lemming lem : vlems) {
        PT tg = lem.target();
        if(tg.inBounds()) {
            adj[tg.x][tg.y].push_back(lem.pt);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(adj[i][j].size() > 1) {
                block(PT(i, j));
            }
        }
    }
    vector<lemming> vupdate;
    for(lemming lem : vlems) {
        PT tg = lem.target();
        if(tg.inBounds()) {
            if(blocked[tg.x][tg.y]) {
                lem.diridx = (lem.diridx + 1) % 4;
            }else {
                lem.pt = tg;
            }
            vupdate.push_back(lem);
        }
    }
    vlems = vupdate;
}

bool haslem[N][N];
int dirs[N][N];
void printState() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            haslem[i][j] = false;
        }
    }
    for(lemming lem : vlems) {
        PT p = lem.pt;
        haslem[p.x][p.y] = true;
        dirs[p.x][p.y] = lem.agenda[lem.diridx];
    }
    cout << "------------------" << endl;
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < m; j++) {
            if(haslem[i][j]) {
                int d = dirs[i][j];
                if(d == NORTH) {
                    cout << "^ ";
                }else if(d == SOUTH) {
                    cout << "v ";
                }else if(d == WEST) {
                    cout << "< ";
                }else {
                    cout << "> ";
                }
            }else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    for(int te = 1; ; te++) {
        cin >> n >> m;
        if(n == 0) break;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // coordinate (i, j)
                cin >> str;
                vlems.push_back(lemming(str, PT(i, j)));
            }
        }
        int it = 0;
        for(; !vlems.empty(); it++) {
            printState();
            update();
        }
        cout << "Case " << te << ": " << it << endl;
    }
}