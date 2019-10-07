#include <cstdio>
#include <cstring>

const int MAXN = 1111, MAXD = 10;

int a[MAXN], b[MAXD][MAXD], c[MAXD][MAXD], d[MAXD][MAXD];
int cnt[MAXD][MAXD], pos[MAXD][MAXD];

int main() {
    int p;
    scanf("%d", &p);
    for (int i = 0; i < p; ++i) {
        scanf("%d", &a[i]);
    }
    int bar = p / 40 + (p % 40 != 0);
    int ans_start = p, ans_n, ans_m;
    for (int n = 1; n < p; ++n) {
        for (int m = 1; m < p; ++m) {
            memset(b, -1, sizeof b);
            memset(c, -1, sizeof c);
            memset(d, -1, sizeof d);
            for (int i = 0; i + n + m < p; ++i) {
                int x = a[i], y = a[i + n], z = a[i + n + m];
                if (b[x][y] == -1 && c[y][z] == -1 && d[x][z] == -1) {
                    b[x][y] = z, c[y][z] = x, d[x][z] = y;
                    cnt[x][y] = 1, pos[x][y] = i;
                } else if (b[x][y] == z && c[y][z] == x && d[x][z] == y) {
                    cnt[x][y]++;
                } else {
                    int tx = c[y][z], ty = d[x][z], tz = b[x][y];
                    b[x][y] = c[y][z] = d[x][z] = -2;
                    if (tx >= 0) b[tx][y] = d[tx][z] = -2;
                    if (ty >= 0) b[x][ty] = c[ty][z] = -2;
                    if (tz >= 0) c[y][tz] = d[x][tz] = -2;
                }
            }
            for (int i = 0; i < MAXD; ++i) {
                for (int j = 0; j < MAXD; ++j) {
                    if (b[i][j] >= 0 && cnt[i][j] > bar) {
                        if (pos[i][j] < ans_start) {
                            ans_start = pos[i][j], ans_n = n, ans_m = m;
                        }
                    }
                }
            }
        }
    }
    if (ans_start == p) {
        puts("random sequence");
    } else {
        printf("triple correlation %d(%d)%d(%d)%d found\n", a[ans_start],
            ans_n, a[ans_start + ans_n], ans_m, a[ans_start + ans_n + ans_m]);
    }
    return 0;
}