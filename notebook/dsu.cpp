const int N = 1e5 + 5;
int dsu[N]; // negative and equals to -size if root, parent if non-root

int trace(int u) {
    return dsu[u] < 0 ? u : dsu[u] = trace(dsu[u]);
}

bool connect(int u, int v) {
    if ((u = trace(u)) == (v = trace(v))) {
        return false;
    }
    if (dsu[u] > dsu[v]) {
        swap(u, v);
    }
    dsu[u] += dsu[v];
    dsu[v] = u;
    return true;
}

int main() {
    fill(dsu, dsu + N, -1);
}
