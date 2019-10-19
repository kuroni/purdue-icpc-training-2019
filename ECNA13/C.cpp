#include <bits/stdc++.h>
using namespace std;
 
const int N = 26, M = 5;
 
bool v[N];
char g[M][M];
int x[N], y[N];
 
string trans() {
    string s;
    getline(cin, s);
    string r;
    for (int i = 0; i < (int)s.length(); ++i) {
        if (isalpha(s[i])) {
            r += toupper(s[i]);
        }
    }
    return r;
}
 
void inc(int &x, int &y) {
    if (++y == M) {
        ++x; y = 0;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string key;
    string plain;
    getline(cin, key);
    for (int cs = 1; cs <= n; ++cs) {
        key = trans();
        plain = trans();
        memset(v, false, sizeof v);
        int i = 0, j = 0;
        for (int p = 0; p < (int)key.length(); ++p) {
            int u = key[p] - 'A';
            if (!v[u]) {
                g[i][j] = key[p];
                x[u] = i, y[u] = j;
                v[u] = true;
                if (u + 'A' == 'I') {
                    v[u + 1] = true;
                }
                inc(i, j);
            }
        }
        for (int u = 0; u < N; ++u) {
            if (!v[u]) {
                g[i][j] = u + 'A';
                x[u] = i, y[u] = j;
                v[u] = true;
                if (u + 'A' == 'I') {
                    v[u + 1] = true;
                }
                inc(i, j);
            }
        }
        cout << "Case " << cs << ": ";
        int l = (int)plain.length();
        i = 0;
        int e = 0;
        while (i < l) {
            int a = plain[i] - 'A', b;
            if (i + 1 < l && plain[i + 1] != plain[i]) {
                b = plain[i + 1] - 'A';
                ++i;
            } else {
                do {
                    b = e;
                    e = (e + 1) % N;
                    if (e + 'A' == 'J') e++;
                } while (b == a);
            }
            if (x[a] == x[b]) {
                cout << g[x[a]][(y[a] + 1) % M];
                cout << g[x[b]][(y[b] + 1) % M];
            } else if (y[a] == y[b]) {
                cout << g[(x[a] + 1) % M][y[a]];
                cout << g[(x[b] + 1) % M][y[b]];
            } else {
                cout << g[x[a]][y[b]];
                cout << g[x[b]][y[a]];
            }
            ++i;
        }
        cout << endl;
    }
}
