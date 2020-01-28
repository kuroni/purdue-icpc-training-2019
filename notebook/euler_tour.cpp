void DFS(int u) {
    while (!adj[u].empty()) {
        int v = adj[u].back(); adj[u].pop_back();
        DFS(v);
    }
    eu.push_back(u);
}
