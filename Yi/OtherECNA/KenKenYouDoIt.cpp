#include <cstdio>

const int M = 10;

bool ur[M][M], uc[M][M];
char op;
int n, m, t, ans, r[M], c[M];

void dfs(int dep, int cur) {
    int cr = r[dep], cc = c[dep];
    if (dep == m - 1) {
        int x = op == '+' ? t - cur : t % cur == 0 ? t / cur : 0;
        if (x >= 1 && x <= n && !ur[cr][x] && !uc[cc][x]) {
            ++ans;
        }
        return;
    }
    for (int x = 1; x <= n; ++x) {
        if (ur[cr][x] || uc[cc][x]) continue;
        ur[cr][x] = uc[cc][x] = true;
        if (op == '+' && t - x >= cur) dfs(dep + 1, cur + x);
        if (op == '*' && t / x >= cur) dfs(dep + 1, cur * x);
        ur[cr][x] = uc[cc][x] = false;
    }
}

int main() {
    scanf("%d%d%d %c", &n, &m, &t, &op);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &r[i], &c[i]);
    }
    if (op == '-' || op == '/') {
        for (int x = 1; x <= n; ++x) {
            for (int y = x + 1; y <= n; ++y) {
                if (op == '-' && y - x == t ||
                    op == '/' && y % x == 0 && y / x == t) {
                    ans += 2;
                }
            }
        }
    } else {
        dfs(0, op == '+' ? 0 : 1);
    }
    printf("%d\n", ans);
    return 0;
}