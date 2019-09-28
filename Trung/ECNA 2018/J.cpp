#include <bits/stdc++.h>
using namespace std;

const int N = 2505;

int n, cnt = 0, cur = 0, ans = 0, a[N][N], b[N][N];
int num[N], low[N], col[N], nod[N];
bool vis[N];
vector<int> ve, tpo;

void DFS(int u)
{
    num[u] = low[u] = ++cnt;
    ve.push_back(u);
    for (int i = 1; i <= n; i++)
        if (a[u][i] == 1 && col[i] == 0)
        {
            if (num[i] == 0)
            {
                DFS(i);
                low[u] = min(low[u], low[i]);
            }
            else
                low[u] = min(low[u], num[i]);
        }
    if (num[u] == low[u])
    {
        ++cur;
        while (col[u] == 0)
        {
            col[ve.back()] = cur;
            nod[cur]++;
            ve.pop_back();
        }
    }
}

void topo_sort(int u)
{
    vis[u] = true;
    for (int i = 1; i <= n; i++)
        if (b[u][i] == 1 && !vis[i])
            topo_sort(i);
    tpo.push_back(u);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            ans -= a[i][j];
        }
    for (int i = 1; i <= n; i++)
        if (num[i] == 0)
            DFS(i);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j] == 1 && col[i] != col[j])
                b[col[i]][col[j]] = 1;
    for (int i = 1; i <= cur; i++)
        if (!vis[i])
            topo_sort(i);
    int sum = 0;
    for (int &v : tpo)
    {
        sum += nod[v];
        ans += nod[v] * (sum - 1);
    }
    cout << ans;
}
