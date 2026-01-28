/*
    1. Consecutive +-1
    -> latter
    2. Minimun
    -> Up and no down-er
*/
#include <bits/stdc++.h>

const int N = (int)1e5 + 3;

int n;
long long k;
int a[N];

long long calc(void) {
    a[n + 1] = a[n]
    if (n <= 2) {
        return std::max(a[1], a[2]) - (k + n - 1) / n;
    }
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
    std::cout << calc() << '\n';
}