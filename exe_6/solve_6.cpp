
#include <bits/stdc++.h>

const int N = (int)1e4;

std::vector<int> a[N];

struct Node {
    int val;
    int i;
    int j;
    Node(int _val, int _i, int _j): val(_val), i(_i), j(_j) {}

    bool operator<(const Node &other) const {
        return val > other.val;
    }
};

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n; std::cin >> n;
    std::cin.ignore();
    for (int i = 0; i < n; ++i) {
        std::string line;
        if (std::getline(std::cin, line)) {
            std::stringstream ss(line);
            int x;
            while (ss >> x) {
                a[i].push_back(x);
            }
        }
    }

    std::priority_queue<Node> pq;
    for (int i = 0; i < n; ++i) {
        pq.push(Node(a[i][0], i, 0));
    }

    std::vector<int> ret;
    while (!pq.empty()) {
        Node x = pq.top();
        pq.pop();
        ret.push_back(x.val);
        if (x.j + 1 < a[x.i].size()) pq.push(Node(a[x.i][x.j + 1], x.i, x.j + 1));
    }
    for (int x : ret) std::cout << x << ' ';
    std::cout << std::endl;
}