
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int N = 26, M = 2005;
int n, m, p[M];
string s;
int pos[N][M];
bool mat[N][N];
vector<int> adj[N], adjr[N];
stack<int> st;
int par[N];

bool visited[N];
void dfs1(int x) {
    visited[x] = true;
    for(int u : adj[x]) {
        if(!visited[u]) {
            dfs1(u);
        }
    }
    st.push(x);
}

// return size of component
void dfs2(int x, int p) {
    par[x] = p;
    visited[x] = true;
    for(int u : adjr[x]) {
        if(!visited[u]) {
            dfs2(u, p);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> p[i] >> s;
        for(int j = 0; j < n; j++) {
            pos[s[j] - 'A'][i] = j;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int score = 0;
            for(int k = 0; k < m; k++) {
                if(pos[i][k] < pos[j][k]) {
                    score += p[k];
                }else {
                    score -= p[k];
                }
            }
            if(score > 0) {
                adj[i].push_back(j);
                adjr[j].push_back(i);
                // cout << i << " beats " << j << endl;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            dfs1(i);
        }
    }
    fill(visited, visited + n, false);
    int firstcomp = st.top();
    while(!st.empty()) {
        int x = st.top();
        st.pop();
        if(!visited[x]) {
            dfs2(x, x);
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ((char) ('A' + i)) << ": " << (par[i] == firstcomp ? "can win" : "can't win") << endl;
    }
}