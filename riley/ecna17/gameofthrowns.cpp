
#include <cstdlib>
#include <cstring>
#include <cstdio>

#define ll long long
using namespace std;

int n, k, num;
char p[10];
int acc[105];

int main() {
    while(scanf("%d %d", &n, &k) == 2) {
        acc[0] = 0;
        int j = 1;
        for(int i = 1; i <= k; i++, j++) {
            scanf("%s", &p);
            if(strcmp(p, "undo") == 0) {
                scanf("%d", &num);
                acc[j] = acc[j - num - 1];
                j = j - num - 1;
            }else {
                num = atoi(p);
                acc[j] = ((acc[j - 1] + num) % n + n) % n;
            }
        }
        printf("%d\n", acc[j - 1]);
    }
}