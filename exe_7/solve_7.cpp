#include <bits/stdc++.h>

const int N = (int)3e4;

int a[N];
int L[N];

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n; std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    L[0] = a[0];
    for (int i = 1; i < n; ++i) {
        L[i] = std::max(L[i - 1], a[i]);
    }
    int R = a[n - 1];
    int ret = 0;
    for (int i = n - 2; i > 0; --i) {
        R = std::max(R, a[i]);
        ret += std::min(L[i], R) - a[i];
    }
    std::cout << ret << '\n';
}