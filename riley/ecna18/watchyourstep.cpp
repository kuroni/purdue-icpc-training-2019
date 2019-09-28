
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int N = 2505;
int n, a;
vector<int> adj[N], adjr[N];
stack<int> st;
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
int dfs2(int x) {
    visited[x] = true;
    int cnt = 1;
    for(int u : adjr[x]) {
        if(!visited[u]) {
            cnt += dfs2(u);
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a;
            if(a) {
                cnt--;
                adj[i].push_back(j);
                adjr[j].push_back(i);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            dfs1(i);
        }
    }
    fill(visited, visited + n, false);
    vector<int> v;
    while(!st.empty()) {
        int x = st.top();
        st.pop();
        if(!visited[x]) {
            v.push_back(dfs2(x));
        }
    }
    for(int i = 0; i < v.size(); i++) {
        cnt += v[i] * (v[i] - 1);
        for(int j = i + 1; j < v.size(); j++) {
            cnt += v[i] * v[j];
        }
    }
    cout << cnt << endl;
}