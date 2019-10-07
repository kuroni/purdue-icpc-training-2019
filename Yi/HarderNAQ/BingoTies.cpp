#include <iostream>

using namespace std;

const int N = 100, M = 5, D = 3001;

int a[N][M][M], v[D];

int main() {
    ios::sync_with_stdio(false);
    int n, cnt = 1;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < M; ++k) {
                cin >> a[i][j][k];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = 0; k < M; ++k) {
                for (int l = 0; l < M; ++l) {
                    bool possible = false;
                    int ori = cnt;
                    for (int m = 0; m < M; ++m) {
                        v[a[i][k][m]] = cnt;
                    }
                    for (int m = 0; m < M; ++m) {
                        if (v[a[j][l][m]] == cnt) {
                            ++v[a[j][l][m]];
                            possible = true;
                        } else {
                            v[a[j][l][m]] = cnt;
                        }
                    }
                    cnt += 2;
                    if (possible) {
                        bool valid = true;
                        for (int p = 0; valid && p < n; ++p) {
                            if (p != i && p != j) {
                                for (int q = 0; valid && q < M; ++q) {
                                    valid = false;
                                    for (int m = 0; !valid && m < M; ++m) {
                                        if (v[a[p][q][m]] < ori) {
                                            valid = true;
                                        }
                                    }
                                    if (!valid) {
                                        for (int m = 0; m < M; ++m) {
                                            if (v[a[p][q][m]] == cnt - 1) {
                                                valid = true;
                                                v[a[p][q][m]] = cnt;
                                            }
                                        }
                                        ++cnt;
                                    }
                                }
                            }
                        }
                        if (valid) {
                            cout << i + 1 << ' ' << j + 1 << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    cout << "no ties" << endl;
    return 0;
}