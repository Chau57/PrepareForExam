/*
    1. Distance between pairs
    -> u->LCA(u, v) + v->LCA(u, v)
*/
#include <bits/stdc++.h>

const int N = (int)1e5;

int n;
std::vector<int> adj[N];

int f[N];
long long g[N];
long long ret;
void dfs(int u, int p) {
    f[u] = 1;
    for (int v : adj[u]) if (v != p) {
        dfs(v, u);
        f[u] += f[v];
    }
    for (int v : adj[u]) if (v != p) {
        long long totalDistanceFromUToEveryChildInV = g[v] + f[v];
        g[u] += totalDistanceFromUToEveryChildInV;
        ret += totalDistanceFromUToEveryChildInV * (f[u] - f[v]);
    }
}

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n; std::cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; std::cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ret = 0;
    dfs(0, -1);
    std::cout << ret << std::endl;
    return 0;
}