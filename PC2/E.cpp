#include <bits/stdc++.h>
using namespace std;

int n;
string s;
vector<int> ve = {1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s;
    s += 'R';
    for (int i = 2; i <= n + 1; i++) {
        char c = s[i - 2];
        if (c == 'R') {
            while (!ve.empty()) {
                cout << ve.back() << '\n';
                ve.pop_back();
            }
        }
        ve.push_back(i);
    }
}
