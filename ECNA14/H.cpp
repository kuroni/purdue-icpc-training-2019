#include <bits/stdc++.h>
using namespace std;

int ang, hr, q;
string str;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> ang >> str >> hr;
        int cur = (12 - hr) * 30;
        double tim = (hr % 12) * 3600;
        if (str == "after") {
            int des = 360 - ((cur - ang) % 360 + 360) % 360;
            tim += des * 120.0 / 11;
        } else {
            int des = 360 - ((ang - cur) % 360 + 360) % 360;
            tim -= des * 120.0 / 11;
        }
        int ans = (((int)round(tim) % 43200) + 43200) % 43200;
        int hr = ans / 3600; ans %= 3600;
        if (hr == 0) {
            hr = 12;
        }
        int mi = ans / 60; ans %= 60;
        int se = ans;
        cout << "Case " << i << ": " << hr << ":" << std::setfill('0') << std::setw(2) << mi << ":" << std::setfill('0') << std::setw(2) << se << '\n';
    }
}