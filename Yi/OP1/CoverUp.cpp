#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5;

double p_known[MAXN], p_unknown[MAXN];
int m[MAXN];

double work(int round, vector<pair<int, int> > state) {
    if (state.empty()) return 1;
    double p_known_correct[MAXN], p_unknown_correct[MAXN];
    double ans = 0;
    int n = state.size();
    for (int choice = 0; choice < 1 << n; ++choice) {
        bool valid = true;
        for (int i = 0; valid && i < n; ++i) {
            int x = state[i].first;
            int num_known = state[i].second;
            int num_unknown = m[x] - round - num_known;
            int choice_x = (choice >> i) & 1;
            if ((!num_known && choice_x) || (!num_unknown && !choice_x)) {
                valid = false;
            } else {
                double sum = num_known * p_known[x] + num_unknown * p_unknown[x];
                if (sum < 1e-6) {
                    valid = false;
                } else {
                    p_known_correct[i] = p_known[x] / sum;
                    p_unknown_correct[i] = p_unknown[x] / sum;
                }
            }
        }
        if (!valid) continue;
        double prob = 0;
        for (int res = 1; res < 1 << n; ++res) {
            double p = 1;
            vector<pair<int, int> > next_state;
            for (int i = 0; i < n; ++i) {
                int choice_x = (choice >> i) & 1;
                int res_x = (res >> i) & 1;
                if (res_x) {
                    if (choice_x) p *= p_known_correct[i];
                    else p *= p_unknown_correct[i];
                } else {
                    if (choice_x) p *= 1 - p_known_correct[i];
                    else p *= 1 - p_unknown_correct[i];
                    next_state.push_back(make_pair(state[i].first, state[i].second - choice_x));
                }
            }
            prob += p * work(round + 1, next_state);
        }
        ans = max(prob, ans);
    }
    return ans;
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<pair<int, int> > init;
        for (int i = 0; i < n; ++i) {
            double p;
            int l;
            cin >> m[i] >> l >> p;
            p_known[i] = l == 0 ? 0 : p / l;
            p_unknown[i] = l == m[i] ? 0 : (1 - p) / (m[i] - l);
            init.push_back(make_pair(i, l));
        }
        cout << (int)round(work(0, init) * 1000) / 1000.0 << endl;
    }
    return 0;
}