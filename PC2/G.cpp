#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 105;

// nodes, edges, initially infected, time
int n, m, s, t, x, y;

vector<int> adj[N];
ll state[N], state2[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    state[s] = 1;
    while(t--) {
        fill(state2, state2 + N, 0);
        for(int i = 0; i < n; i++) {
            for(int y : adj[i]) {
                state2[y] += state[i];
            }
        }
        for(int i = 0; i < n; i++) {
            state[i] = state2[i];
        }
    }
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        sum += state[i];
    }
    cout << sum << endl;
}
