#include <bits/stdc++.h>

const int N = (int)1e5;

int n;
int sz[2];
int a[N];
int b[N];

struct Node {
    int val;
    int idx;
    bool operator<(const Node &other) const {
        return val > other.val;
    }
};

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin >> n >> sz[0] >> sz[1];
    for (int i = 1; i <= n; ++i) std::cin >> a[i] >> b[i];

    std::priority_queue<Node> pq[2];
    bool t = false;
    for (int i = 1; i <= n; ++i) {
        if (a[i] < b[i]) {
            std::swap(a, b);
            std::swap(pq[0], pq[1]);
            std::swap(sz[0], sz[1]);
        }
        pq[0].push({a[i], i});
        if (pq[0].size() == sz[0]) {
            continue;
        }

        int idx = pq[0].top().idx;
        pq[0].pop();
        pq[1].push({b[idx], idx});
        if (pq[1].size() > sz[1]) {
            pq[1].pop();
        }
    }

    long long ret = 0;
    for (int t = 0; t < 2; ++t) {
        while (sz[t]--) {
            ret += pq[t].top().val;
            pq[t].pop();
        }
    }
    std::cout << ret << std::endl;
    return 0;
}