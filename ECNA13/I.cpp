#include <bits/stdc++.h>
using namespace std;
 
const int L = 65;
 
unsigned int n, te = 0;
unsigned long long m, f[L];
 
void init() {
    f[0] = f[1] = 1;
    for (int i = 2; i < L; i++) {
        f[i] = f[i - 1] + 2 * f[i - 2];
    }
}
 
string solve(unsigned long long ind) {
    string ans = "";
    int len = 1;
    while (true) {
        if (f[len] <= ind) {
            ind -= f[len++];
        } else {
            break;
        }
    }
    for (int i = 0; i <= len; i += 2) {
        if (i + 2 > len) {
            if (i == len - 1) {
                ans += "a";
            }
            return ans;
        }
        if ((1ULL << (len - i - 1)) > ind) {
            break;
        } else {
            ind -= (1LL << (len - i - 1));
            ans += "bb";
        }
    }
    ans += "a";
    len -= ans.size();
    for (int i = len - 1; i >= 0; i--) {
        ans += (char)((ind >> i & 1) + 'a');
    }
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    while (cin >> n >> m, n != 0) {
        	
        cout << "Case " << ++te << ": " << solve((m - 1) * n) << " " << solve(m * n - 1) << '\n';
    }
}
