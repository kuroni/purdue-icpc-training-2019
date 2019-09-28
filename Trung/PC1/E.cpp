#include <bits/stdc++.h>
using namespace std;

const int N = 15;

int n, cnt, it, te = 0, x[N], y[N], mat[N], vis[N];
bool chk[N];
vector<int> ve;

bool check(int u, int v) {
    return (x[u] == x[v]) ^ (y[u] == y[v]);
}

bool DFS(int u) {
    vis[u] = it;
    for (int i = 0; i < n; i++) {
        if (check(ve[u], ve[i]) && mat[i] == -1) {
            mat[i] = u;
            return true;
        }
    }
    for (int i = 0; i < n; i++) {
        if (check(ve[u], ve[i]) && vis[mat[i]] < it && DFS(mat[i])) {
            mat[i] = u;
            return true;
        }
    }
    return false;
}

int DFS_1(int u) {
    chk[u] = true;
    int ret = 1;
    for (int i = 0; i < n; i++) {
        if (!chk[i] && check(ve[u], ve[i])) {
            ret += DFS_1(i);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n, n != 0) {
        bool ok = true;
        ve.clear();
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i] >> cnt;
            while (cnt--) {
                ve.push_back(i);
            }
        }
        n = ve.size();
        fill(mat, mat + n, -1);
        fill(vis, vis + n, -1);
        fill(chk, chk + n, false);
        if (DFS_1(0) < n) {
            ok = false;
        }
        for (int i = 0; i < n; i++) {
            if (!DFS(i)) {
                ok = false;
                break;
            } else {
                it++;
            }
        }
        cout << "Case " << ++te << ": " << "We can";
        if (!ok) {
            cout << "not";
        }
        cout << " make a necklace from this set of beads.\n";
    }
}
