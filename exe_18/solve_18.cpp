#include <bits/stdc++.h>


int solve_bfs(std::vector<int> start) {
    int n = start.size();
    std::vector<int> target = start;
    std::sort(target.begin(), target.end());

    std::queue<std::vector<int>> q;
    std::map<std::vector<int>, int> dist;

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        std::vector<int> curr = q.front();
        q.pop();

        if (curr == target) return dist[curr];

        // Thử tất cả các cách lật tiền tố từ vị trí 2 đến n
        for (int i = 2; i <= n; i++) {
            std::vector<int> next_st = curr;
            std::reverse(next_st.begin(), next_st.begin() + i);
            
            if (dist.find(next_st) == dist.end()) {
                dist[next_st] = dist[curr] + 1;
                q.push(next_st);
            }
        }
    }
    return -1;
}

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (int &x : a) std::cin >> x;

    std::cout << solve_bfs(a) << std::endl;
    return 0;
}
