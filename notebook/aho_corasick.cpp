const int N = 200005, MX = 26;

int cnt = 0, kmp[N], ch[N][MX], nxt[N][MX];

void BFS() {
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
        int u = q.front();
        for (int i = 0; i < MX; i++) {
            if (ch[u][i] == 0) {
                nxt[u][i] = nxt[kmp[u]][i];
            } else {
                int v = ch[u][i];
                nxt[u][i] = v;
                kmp[v] = nxt[kmp[u]][i];
                if (kmp[v] == v) {
                    kmp[v] = 0;
                }
                q.push(v);
            }
        }
    }
}

int add(string &s) {
    int cur = 0;
    for (char &c : s) {
        if (ch[cur][c - 'a'] == 0) {
            ch[cur][c - 'a'] = ++cnt;
        }
        cur = ch[cur][c - 'a'];
    }
    return cur;
}
