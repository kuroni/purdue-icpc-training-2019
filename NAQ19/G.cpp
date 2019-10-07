#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int n;
double P[N];
double dp[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> P[i];
        P[i] *= 0.01;
    }
    sort(P, P + n, greater<double>());
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        dp[0][i] = dp[0][i - 1] * (1 - P[i - 1]);
        dp[i][i] = dp[i - 1][i - 1] * P[i - 1];
    }
    for(int s = 2; s <= n; s++) {
        for(int a = 1; a < s; a++) {
            dp[a][s] = P[s - 1] * dp[a - 1][s - 1] + (1 - P[s - 1]) * dp[a][s - 1];
        }
    }
    /*
    for(int s = 1; s <= n; s++) {
        for(int a = 0; a <= s; a++) {
            cout << dp[a][s] << " ";
        }
        cout << endl;
    }
    */
    
    double maxE = 0;
    for(int s = 1; s <= n; s++) {
        double E = 0;
        for(int a = 1; a <= s; a++) {
            E += pow(a, ((double) a) / s) * dp[a][s];
        }
        maxE = max(maxE, E);
    }
    cout << fixed << setprecision(8);
    cout << maxE << endl;
}
