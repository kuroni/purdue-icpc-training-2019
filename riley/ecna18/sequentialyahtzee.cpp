#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int N = 200;
int n;
int a[N];
int pts[N][14][16];
int dp[N][14];
vector<vector<int> > combs[16];

// compute the number of points for a set of five dice
int points(int cat, int arr2[]) {
    int arr[5];
    for(int i = 0; i < 5; i++) {
        arr[i] = arr2[i];
    }
    sort(arr, arr + 5);
    int dice[7];
    for(int i = 1; i <= 6; i++) {
        dice[i] = 0;
    }
    int sum = 0;
    for(int i = 0; i < 5; i++) {
        dice[arr[i]]++;
        sum += arr[i];
    }

    if(cat <= 6) {
        return cat * dice[cat];
    }else if(cat == 7) {
        // 3 of a kind, sum of dice
        if((arr[0] == arr[1] && arr[1] == arr[2]) ||
            (arr[1] == arr[2] && arr[2] == arr[3]) ||
            (arr[2] == arr[3] && arr[3] == arr[4])) {
            return sum;
        }else {
            return 0;
        }
    }else if(cat == 8) {
        // 4 of a kind, sum of dice
        if((arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3]) ||
            (arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4])) {
            return sum;
        }else {
            return 0;
        }
    }else if(cat == 9) {
        // full house, 25
        if(arr[0] != arr[4] && (arr[0] == arr[1] && arr[3] == arr[4] && (arr[2] == arr[1] || arr[2] == arr[3]))) {
            return 25;
        }else {
            return 0;
        }
    }else if(cat == 10) {
        // small straight, 30
        if((arr[1] + 1 == arr[2] && arr[2] + 1 == arr[3] && arr[3] + 1 == arr[4]) ||
            (arr[0] + 1 == arr[2] && arr[2] + 1 == arr[3] && arr[3] + 1 == arr[4]) ||
            (arr[0] + 1 == arr[1] && arr[1] + 1 == arr[3] && arr[3] + 1 == arr[4]) ||
            (arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2] && arr[2] + 1 == arr[4]) ||
            (arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2] && arr[2] + 1 == arr[3])) {
            return 30;
        }else {
            return 0;
        }
    }else if(cat == 11) {
        // large straight, 40
        if(arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2] && arr[2] + 1 == arr[3] && arr[3] + 1 == arr[4]) {
            return 40;
        }else {
            return 0;
        }
    }else if(cat == 12) {
        // chance, sum of dice
        return sum;
    }else if(cat == 13) {
        // yahtzee, 50
        return arr[0] == arr[4] ? 50 : 0;
    }
}

// generate all valid combinations of dice rolls in a range
// note: not all 5-subsets of the range are valid as new dice
// rolls must replace old ones
void genCombs() {
    vector<int> arr(5);
    for(int i = 0; i <= 5; i++) {
        vector<bool> v1(5);
        int idx = 0;
        fill(v1.end() - (5 - i), v1.end(), true);
        do {
            idx = 0;
            for(int k = 0; k < v1.size(); k++) {
                if(v1[k]) {
                    arr[idx++] = k;
                }
            }
            for(int j = 0; j <= i; j++) {
                vector<bool> v2(i);
                fill(v2.end() - (i - j), v2.end(), true);
                do {
                    for(int k = 0; k < v2.size(); k++) {
                        if(v2[k]) {
                            arr[idx++] = 5 + k;
                        }
                    }
                    for(int k = 0; k < j; k++) {
                        arr[idx++] = 5 + i + k;
                    }
                    idx -= i;
                    combs[5 + i + j].push_back(vector<int>(arr.begin(), arr.end()));
                }while(next_permutation(v2.begin(), v2.end()));
            }
        }while(next_permutation(v1.begin(), v1.end()));
    }
}

// maximum number of points in category cat obtainable in the range [l, r] of dice rolls
int maxpoints(int cat, int l, int r) {
    int M = 0;
    int arr[5];
    for(vector<int> v : combs[r - l + 1]) {
        for(int i = 0; i < 5; i++) {
            arr[i] = a[r + v[i] - v[4]];
        }
        M = max(M, points(cat, arr));
    }
    return M;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    genCombs();

    for(int i = 1; i <= n; i++) {
        for(int cat = 1; cat <= 13; cat++) {
            dp[i][cat] = INT_MIN;
            if(i >= 5 * cat && i <= 15 * cat) {
                for(int j = 5; j <= 15 && i - j + 1 > 0; j++) {
                    if(i - j >= 5 * (cat - 1) && i - j <= 15 * (cat - 1)) {
                        dp[i][cat] = max(dp[i][cat], maxpoints(cat, i - j + 1, i) + dp[i - j][cat - 1]);
                    }
                }
            }
        }
    }
    int M = 0;
    for(int i = 65; i <= n; i++) {
        M = max(M, dp[i][13]);
    }
    cout << M << endl;
}
