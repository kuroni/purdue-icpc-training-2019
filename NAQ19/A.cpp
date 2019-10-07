#include <bits/stdc++.h>
using namespace std;

string s;
int n;
char c[26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> c[i];
        c[i] = (c[i] == 'T' ? 1 : 0);
    }
    getline(cin, s);
    getline(cin, s);
    int len = s.length();
    stack<char> st;
    for(int i = 0; i < len; i += 2) {
        if(s[i] >= 'A' && s[i] <= 'Z') {
            st.push(c[s[i] - 'A']);
            continue;
        }
        
        char a = st.top(); st.pop();
        if(s[i] == '+') {  
            char b = st.top(); st.pop();
            st.push(a || b);
        }else if(s[i] == '-') {
             st.push(!a);
        }else if(s[i] == '*') {
            char b = st.top(); st.pop();
            st.push(a && b);
        }
    }
    cout << (st.top() ? 'T' : 'F') << endl;
}