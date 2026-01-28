
#include <bits/stdc++.h>

const int N = (int)1e5;

int sz;
int f[N];
void update(int x) {
    for (; x <= sz; x += x & -x) ++f[x];
}

int get(int x) {
    int ret = 0;
    for (; x >= 1; x -= x & -x) ret += f[x];
    return ret;
}

int a[N];
int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n; std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::vector<int> v;
    for (int i = 0; i < n; ++i) v.push_back(a[i]);
    std::sort(v.begin(), v.end());
    v.resize(std::unique(v.begin(), v.end()) - v.begin());

    sz = v.size();
    long long ret = 0;
    for (int i = 0; i < n; ++i) {
        int x = std::upper_bound(v.begin(), v.end(), a[i]) - v.begin();
        ret += get(sz) - get(x);
        update(x);
    }
    std::cout << ret << std::endl;
}