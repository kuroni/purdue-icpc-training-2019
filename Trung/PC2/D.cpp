#include <bits/stdc++.h>
using namespace std;

int x, y, t;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> x >> y >> s;
        if (s == "Vicky") {
            swap(x, y);
        }
        if (__builtin_clz(x) > __builtin_clz(y)) {
            cout << s << " can win\n";
        } else {
            cout << s << " cannot win\n";
        }
    }
}
