/*
    1. Subsequence != Subset
    -> f(l, l + k)
    2. GCD
    -> idempotent
    3. Static
    -> Sparse-able
*/
#include <bits/stdc++.h>

const int N = (int)1e5 + 3;
const int LOGN = 17 + 1;
const int LOGA = 19 + 1;

int n;
int k;
int a[N]; // a[i] <= 10^6

// Sparse Table
int GCD[LOGN][N]; // cache-friendly?
int lg2[N];

int calcGCD(int a, int b) { // no wrapper
    if (a < b) {
        std::swap(a, b);
    }
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void buildSparseTable(void) {
    lg2[0] = lg2[1] = 0;
    lg2[2] = 1;
    for (int i = 3; i <= n; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
    }
    for (int i = 1; i <= n; ++i) {
        GCD[0][i] = a[i];
    }
    for (int j = 0; j < lg2[k]; ++j) { // atmost k elements
        for (int i = n - (1 << (j + 1)) + 1; i >= 1; --i) {
            GCD[j + 1][i] = calcGCD(GCD[j][i], GCD[j][i + (1 << j)]);
        }
    }
}

int getGCD(int l, int r) {
    int j = lg2[r - l + 1];
    int* ptr = GCD[j];
    return calcGCD(ptr[l], ptr[r - (1 << j) + 1]);
}

void input(void);
void output(void);
int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    input();
    output();
    return 0;
}

void input(void) {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
}

void output(void) {
    buildSparseTable();
    int ret = getGCD(1, k);
    for (int i = k + 1; i <= n; ++i) {
        ret = std::max(ret, getGCD(i - k + 1, i));
    }
    std::cout << ret << std::endl;
}