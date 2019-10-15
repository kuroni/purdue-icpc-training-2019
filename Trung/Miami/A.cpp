#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    cin >> x;
    for (int i = 0; i < 12; i++) {
        if ((x * 12 + i) % 26 == (2018 * 12 + 3) % 26) {
            return cout << "yes", 0;
        }
    }
    cout << "no";
}
