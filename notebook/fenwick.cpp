const int N = 1e5 + 5;
int n, bit[N];

int getSum(int k) {
    int s = 0;
    while(k >= 1) {
        s += bit[k];
        k -= k & -k;
    }
    return s;
}
void add(int k, int x) {
    while(k <= n) {
        bit[k] += x;
        k += k & -k;
    }
}