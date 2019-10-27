#include <bits/stdc++.h>
using namespace std;

const int N = 1E4 + 5;

int n, a[N];
bool chk[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cur = 0, sz = n;
    while (sz > 1) {
        int nxt = (a[cur] + sz - 1) % sz;
        while (nxt--) {
            do {
                cur = (cur + 1) % n;
            } while (chk[cur]);
        }
        chk[cur] = true;
        do {
            cur = (cur + 1) % n;
        } while (chk[cur]);
        --sz;
    }
    cout << cur + 1;
}
