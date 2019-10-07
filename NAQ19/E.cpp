#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int MX = 5E5 + 5, N = 5E5 + 5;

int n, m, cnt = 0, vow[MX], str[MX], ind[MX], kmp[MX], nxt[MX][26], ch[MX][26];
int dp[N], sum[N];
string s[N], t[N], z;
vector<int> ans;

void BFS() {
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
        int u = q.front();
        for (int i = 0; i < 26; i++) {
            nxt[u][i] = (ch[u][i] == 0 ? nxt[kmp[u]][i] : ch[u][i]);
            if (ch[u][i] > 0) {
                int v = ch[u][i];
                kmp[v] = nxt[u][i];
                if (kmp[v] == v) {
                    kmp[v] = nxt[kmp[u]][i];
                }
                if (kmp[v] == v) {
                    kmp[v] = 0;
                }
                if (str[v] == 0) {
                    str[v] = str[kmp[v]];
                }
                q.push(v);
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        t[i] = "";
        for (char &c : s[i]) {
            if (c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
                t[i] += c;
            } else {
                vow[i]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        int cur = 0;
        for (char &c : t[i]) {
            int nxt = c - 'A';
            if (ch[cur][nxt] == 0) {
                ch[cur][nxt] = ++cnt;
            }
            cur = ch[cur][nxt];
        }
        if (str[cur] == 0 || vow[str[cur]] < vow[i]) {
            str[cur] = i;
            ind[i] = cur;
        }
    }
    BFS();
    int cur = 0;
    cin >> z;
    m = z.size();
    for (int i = 1; i <= m; i++) {
        dp[i] = -1;
        int chr = z[i - 1] - 'A';
        cur = nxt[cur][chr];
        int can = str[cur];
        while (can > 0) {
            int pre = i - t[can].size();
            if (dp[pre] != -1 && sum[i] <= sum[pre] + vow[can]) {
                dp[i] = can;
                sum[i] = sum[pre] + vow[can];
            }
            can = str[kmp[ind[can]]];
        }
    }
    assert(dp[m] > -1);
    while (m > 0) {
        ans.push_back(dp[m]);
        m -= t[dp[m]].size();
    }
    reverse(ans.begin(), ans.end());
    for (int &v : ans) {
        cout << s[v] << " ";
    }
    cout << '\n';
}