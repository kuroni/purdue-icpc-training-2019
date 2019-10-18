const int N = 1e5 + 5;
int par[N], sz[N];

int find(int x) {
    return par[x] == -1 ? x : par[x] = find(par[x]);
}
void join(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return;
    if(sz[x] < sz[y]) swap(x, y);
    sz[x] += sz[y];
    par[y] = x;
}

int main() {
    fill(par, par + N, -1);
    fill(sz, sz + N, 1);
}