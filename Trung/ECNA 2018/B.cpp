#include <bits/stdc++.h>
using namespace std;

const int N = 10005, MX = 2E8 + 5;

int r, m, pt;
long long a[N];
bool vis[MX];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> pt >> m;
    for (int i = 1;; i++)
    {
        a[i] = a[i - 1] + pt;
        if (i == 1)
            pt = 1;
        for (int j = 0; j < i; j++)
            vis[min(MX - 1LL, a[i] - a[j])] = true;
        if (vis[m])
            return cout << i, 0;
        while (vis[pt])
            pt++;
    }
}
