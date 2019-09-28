
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int N = 52;
int r, c;
// 0 means not the start of a clue
int clue[N][N];
// index in corresponding across/down clues
int across[N][N], down[N][N];
// length of the across/down word
int acrosslen[N][N], downlen[N][N];
string s[N];
map<int, pair<int, int> > acrossratios, downratios;
vector<pair<int, int> > cluepos;

int main() {
    ios::sync_with_stdio(false);
    cluepos.push_back({-1, -1});
    cin >> r >> c;
    for(int i = 0; i < r; i++) {
        cin >> s[i];
    }

    // generate clue numbers, find across indices
    int C = 1;
    for(int i = 0; i < r; i++) {
        int prev = -1;
        for(int j = 0; j < c; j++) {
            if(s[i][j] != '#' && (i == 0 || j == 0 || s[i - 1][j] == '#' || s[i][j - 1] == '#')) {
                clue[i][j] = C++;
                cluepos.push_back({i, j});
                if(j == 0 || s[i][j - 1] == '#') {
                    prev = j;
                    acrossratios[clue[i][j]] = {0, 0};
                }
            }
            if(s[i][j] != '#') {
                across[i][j] = j - prev;
                acrosslen[i][prev] = max(acrosslen[i][prev], j - prev + 1);
            }
        }
    }
    // find down index
    for(int j = 0; j < c; j++) {
        int prev = -1;
        for(int i = 0; i < r; i++) {
            if(s[i][j] != '#' && (i == 0 || s[i - 1][j] == '#')) {
                prev = i;
                downratios[clue[i][j]] = {0, 0};
            }
            if(s[i][j] != '#') {
                down[i][j] = i - prev;
                downlen[prev][j] = max(downlen[prev][j], i - prev + 1);
            }
        }
    }

    // compute ratios for all clues
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            int numa = 0, dena = 0, numb = 0, denb = 0;
            if(s[i][j] != '#') {
                // not a block
                dena = acrosslen[i][j - across[i][j]] - across[i][j];
                denb = downlen[i - down[i][j]][j] - down[i][j];
                pair<int, int> pa = acrossratios[clue[i][j - across[i][j]]];
                pair<int, int> pb = downratios[clue[i - down[i][j]][j]];
                if(s[i][j] != '.') {
                    // filled in
                    numa = dena;
                    numb = denb;
                }
                acrossratios[clue[i][j - across[i][j]]] = {pa.first + numa, pa.second + dena};
                downratios[clue[i - down[i][j]][j]] = {pb.first + numb, pb.second + denb};
            }
        }
    }

    // run simulation
    while(true) {
        // find maximum ratio of an uncompleted clue
        pair<int, int> maxrat = {-1, 1};
        int cluenum = -1;
        bool ac = false;
        for(auto p : acrossratios) {
            pair<int, int> rat = p.second;
            if(rat.first < rat.second && rat.first * maxrat.second > rat.second * maxrat.first) {
                maxrat = rat;
                cluenum = p.first;
                ac = true;
            }
        }
        for(auto p : downratios) {
            pair<int, int> rat = p.second;
            if(rat.first < rat.second && rat.first * maxrat.second > rat.second * maxrat.first) {
                maxrat = rat;
                cluenum = p.first;
                ac = false;
            }
        }
        if(cluenum == -1) {
            break;
        }

        (ac ? acrossratios : downratios)[cluenum] = {1, 1};

        // fill in word and update ratios
        cout << cluenum << (ac ? 'A' : 'D') << endl;
        int i = cluepos[cluenum].first;
        int j = cluepos[cluenum].second;
        int len = ac ? acrosslen[i][j] : downlen[i][j];
        for(int k = 0; k < len; k++) {
            if(s[i][j] == '.') {
                if(ac) {
                    int num = downlen[i - down[i][j]][j] - down[i][j];
                    pair<int, int> pb = downratios[clue[i - down[i][j]][j]];
                    downratios[clue[i - down[i][j]][j]] = {pb.first + num, pb.second};
                }else {
                    int num = acrosslen[i][j - across[i][j]] - across[i][j];
                    pair<int, int> pa = acrossratios[clue[i][j - across[i][j]]];
                    acrossratios[clue[i][j - across[i][j]]] = {pa.first + num, pa.second};
                }
            }
            s[i][j] = 'A';
            (ac ? j : i)++;
        }
    }
}
