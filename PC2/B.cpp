#include <bits/stdc++.h>
using namespace std;

const int MAXV = 111, MAXE = 22222;

struct edge {int e, nxt;};
int V, E;
edge e[MAXE], er[MAXE];
int sp[MAXV], spr[MAXV];
int group_cnt, group_num[MAXV];
bool v[MAXV];
int stk[MAXV];
int cnt[MAXV];
int ans;
vector<string> langs[MAXV];

void fill_forward(int x) {
    int i;
    v[x] = true;
    for (i = sp[x]; i; i = e[i].nxt) if (!v[e[i].e]) fill_forward(e[i].e);
    stk[++stk[0]] = x;
}

void fill_backward(int x) {
    int i;
    v[x] = false;
    group_num[x] = group_cnt;
    cnt[group_cnt]++;
    if (cnt[group_cnt] > ans) ans = cnt[group_cnt];
    for (i = spr[x]; i; i = er[i].nxt) if (v[er[i].e]) fill_backward(er[i].e);
}

void add_edge(int v1, int v2) {
    e[++E].e = v2; e[E].nxt = sp[v1]; sp[v1] = E;
    er[E].e = v1; er[E].nxt = spr[v2]; spr[v2] = E;
}

void SCC() {
    int i;
    stk[0] = 0;
    memset(v, false, sizeof v);
    for (i = 1; i <= V; i++) if (!v[i]) fill_forward(i);
    group_cnt = 0;
    for (i = stk[0]; i >= 1; i--) if (v[stk[i]]) { group_cnt++; fill_backward(stk[i]); }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    cin >> V;
    for (int i = 1; i <= V; ++i) {
        string s;
        char c;
        cin >> s;
        c = getchar();
        //cout << s << c;
        while (c != '\n') {
            cin >> s;
            langs[i].push_back(s);
            c = getchar();
        }
    }
    for (int i = 1; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            if (i != j) {
                for (unsigned k = 0; k < langs[j].size(); ++k) {
                    if (langs[i][0] == langs[j][k]) { add_edge(i, j); break; }
                }
            }
        }
    }
    SCC();
    cout << V - ans << endl;
}
