#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int t;
string s;

bool check_string(string &s) {
    for (int i = 1; i < s.size(); i++) {
        if (s.substr(0, i) >= s.substr(i, s.size() - i)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> s;
        if (s == "0") {
            cout << "1\n";
        } else if (s == "1") {
            cout << '\n';
        } else {
            int tmp = -1;
            for (int i = s.size() - 1; i > 0; i--) {
                if (s[i] == '0') {
                    tmp = i;
                    break;
                }
            }
            if (tmp == -1) {
                cout << '\n';
            } else {
                for (int i = tmp; i < s.size(); i++) {
                    s[i] = '1';
                }
                for (int i = tmp + 1; i < s.size(); i++) {
                    s[i] = '0';
                    if (!check_string(s)) {
                        s[i] = '1';
                    }
                }
                cout << s << '\n';
            }
        }
    }
}
