
#include <bits/stdc++.h>

#define ll long long
using namespace std;

// CDILMXV

int q, n;
int N = 12;
int val[] = {900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
string str[] = {"CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
string s;
vector<pair<string, int> > v1, v2;

int idx[1000];

// assume x < 1000
string roman(int x) {
    string s = "";
    for(int i = 0; i < 12; i++) {
        while(x >= val[i]) {
            s += str[i];
            x -= val[i];
        }
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    for(int i = 1; i < 1000; i++) {
        s = roman(i);
        if(s[0] < 'M') {
            v1.push_back({s, i});
        }else {
            v2.push_back({s, i});
        }
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    for(int i = 0; i < v1.size(); i++) {
        idx[v1[i].second] = i + 1;
    }
    for(int i = 0; i < v2.size(); i++) {
        idx[v2[v2.size() - i - 1].second] = -(i + 1);
    }

    cin >> q;
    while(q--) {
        cin >> n;
        int m = n % 1000;
        if(idx[m] >= 0) {
            cout << (n / 1000) * ((int) v1.size() + 1) + idx[m] << endl;
        }else {
            cout << -(n / 1000) * ((int) v2.size()) + idx[m] << endl;
        }
    }
}