
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int H = 32 * 33 / 2 + 5;
int n, h;
int v[H];
double p[H][5];

bool inBounds(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j <= i;
}
int idx(int i, int j) {
    return i * (i + 1) / 2 + j;
}

pair<vector<double>, double> iter(vector<double> vec) {
    vector<double> res(vec.size(), 0);
    double val = 0;
    for(int i = 0; i < h; i++) {
        val += (res[h + i] = vec[h + i] + vec[i] * p[i][4]);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            int k = idx(i, j);
            if(inBounds(i - 1, j - 1))
                res[idx(i - 1, j - 1)] += p[k][0] * vec[k];
            if(inBounds(i - 1, j))
                res[idx(i - 1, j)] += p[k][1] * vec[k];
            if(inBounds(i + 1, j))
                res[idx(i + 1, j)] += p[k][2] * vec[k];
            if(inBounds(i + 1, j + 1))
                res[idx(i + 1, j + 1)] += p[k][3] * vec[k];
        }
    }
    return {res, val};
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    h = n * (n + 1) / 2;
    for(int i = 0; i < h; i++) {
        cin >> v[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            int k = idx(i, j);
            cin >> p[k][0] >> p[k][1] >> p[k][2] >> p[k][3] >> p[k][4];
        }
    }
    vector<double> vec(2 * h, 0);
    vec[0] = 1;
    pair<vector<double>, double> pr = {vec, 0};
    do {
        pr = iter(pr.first);
    }while(pr.second < 0.999999);

    double sum = 0;
    for(int i = 0; i < h; i++) {
        sum += pr.first[h + i] * v[i];
    }
    cout << fixed << setprecision(6);
    cout << sum << endl;
}
