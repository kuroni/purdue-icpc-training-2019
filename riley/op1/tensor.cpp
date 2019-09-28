
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int N = 505;
int r, c;
int a[N][N];
int dpgcd[N][N];
// divisors of r and c, and of g = gcd of all entries in A
vector<int> divr, divc, divg;

void calcDivisors(int num, vector<int> &v) {
    v.clear();
    for(int i = 1; i * i <= num; i++) {
        if(num % i == 0) {
            v.push_back(i);
            if(i * i < num) {
                v.push_back(num / i);
            }
        }
    }
    sort(v.begin(), v.end());
}

int checkPQ(int p, int q) {
    int g = dpgcd[p - 1][q - 1] / dpgcd[r - 1][c - 1];
    for(int n = 0; n * p < r; n++) {
        for(int m = 0; m * q < c; m++) {
            if(a[n * p][m * q] % (a[0][0] / g) != 0) {
                return 0;
            }
            int val = a[n * p][m * q] / (a[0][0] / g);
            for(int i = 0; i < p; i++) {
                for(int j = 0; j < q; j++) {
                    if(a[n * p + i][m * q + j] % (a[i][j] / g) != 0 ||
                            a[n * p + i][m * q + j] / (a[i][j] / g) != val) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    while(true) {
        cin >> r >> c;
        if(r == 0) break;
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                cin >> a[i][j];
            }
        }
        // find gcd of all matrix entries
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                dpgcd[i][j] = a[i][j];
                if(i > 0) {
                    dpgcd[i][j] = __gcd(dpgcd[i][j], dpgcd[i - 1][j]);
                }
                if(j > 0) {
                    dpgcd[i][j] = __gcd(dpgcd[i][j], dpgcd[i][j - 1]);
                }
            }
        }
        int g = dpgcd[r - 1][c - 1];
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                a[i][j] /= g;
            }
        }
        calcDivisors(r, divr);
        calcDivisors(c, divc);
        calcDivisors(g, divg);
        int cnt = 0;
        for(int p : divr) {
            for(int q : divc) {
                if((p == 1 && q == 1) || (p == r && q == c)) {
                    continue;
                }
                cnt += checkPQ(p, q);
            }
        }
        cout << divg.size() * cnt << endl;
    }
}
