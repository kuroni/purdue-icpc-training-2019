#include <bits/stdc++.h>
using namespace std;

int n, a;
bool printed = false;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int prev = 0;
    for(int i = 0; i < n; i++) {
        cin >> a;
        for(int j = prev + 1; j < a; j++) {
            cout << j << endl;
            printed = true;
        }
        prev = a;
    }
    if(!printed) {
        cout << "good job" << endl;
    }
}