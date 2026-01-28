/*
    1. Rempve == No path
    -> Bridge
    2. Undirected graph
    -> Strongly connected component
    3. Pair
    -> With/without deletion disconnected pairs
*/
#include <bits/stdc++.h>

const int V = (int)1e5 + 3;
const int E = (int)1e5 + 3;

int n;
int m;
std::pair<int, int> edges[E];
long long ret[E]; // V <= 10^5

// Tarjan
std::vector<int> adj[V]; // indices of edges in original graph
bool isUsed[E];
bool isBridge[E];
int order;
int low[V];
int num[V];
void Tarjan(int u) {
    low[u] = n + 1;
    num[u] = ++order;
    for (int i : adj[u]) {
        if (isUsed[i]) {
            continue;
        }
        isUsed[i] = true;
        int v = edges[i].first ^ edges[i].second ^ u;
        if (num[v] == 0) {
            Tarjan(v);
            low[u] = std::min(low[u], low[v]);
            if (num[u] < low[v]) {
                isBridge[u] = true;
            }
        } else {
            low[u] = std::min(low[u], num[v]);
        }
    }
}

// Disjoint Set Union
int dsu[V];
void initDSU(void) {
    memset(dsu, -1, (n + 1) * sizeof(dsu[0])); // careful, -1
}

int findRoot(int u) {
    return dsu[u] < 0 ? u : dsu[u] = findRoot(dsu[u]);
}

void joinGraph(int u, int v) {
    int x = findRoot(u);
    int y = findRoot(v);
    if (x == y) {
        return;
    }

    if (dsu[x] > dsu[y]) {
        std::swap(x, y);
    }
    dsu[x] += dsu[y];
    dsu[y] = x;
}

// Compression
std::vector<int> tree[V]; // fat graph
void buildFatForest(void) {
    // build graph
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
        adj[edges[i].first].push_back(i);
        adj[edges[i].second].push_back(i);
    }

    // mark bridges
    memset(isUsed, false, (m + 1) * sizeof(isUsed[0])); // careful, 0
    memset(isBridge, false, (m + 1) * sizeof(isBridge[0])); // careful, 0
    memset(num, 0, (n + 1) * sizeof(num[0])); // careful, 0
    order = 0;
    for (int i = 1; i <= n; ++i) {
        if (num[i] == 0) {
            Tarjan(i);
        }
    }

    // compress to fat nodes
    initDSU();
    for (int i = 1; i <= m; ++i) {
        if (!isBridge[i]) {
            joinGraph(edges[i].first, edges[i].second);     
        }
    }

    // build forest
    for (int i = 1; i <= n; ++i) {
        tree[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
        if (isBridge[i]) {
            int u = findRoot(edges[i].first); // careful, new node
            int v = findRoot(edges[i].second); // careful, new node
            tree[u].push_back(v); // careful, new graph
            tree[v].push_back(u); // careful, new graph
        }
    }
}

// Calculate pairs
int f[V]; // number of nodes in sub-fat-trees
bool done[V];
void calcF(int, int);
void calcResult(void) {
    // calculate f via DFT
    memset(f, 0, (m + 1) * sizeof(f[0]));
    for (int i = 1; i <= n; ++i) {
        int v = findRoot(i); // careful, new graph
        if (f[v] == 0) {
            calcF(v, -1);
        }
    }

    // calculate number of connected pairs
    for (int i = 1; i <= m; ++i) { 
        if (isBridge[i]) {
            // store the sub-fat-tree part
            ret[i] = std::min(f[findRoot(edges[i].first)], f[findRoot(edges[i].second)]); // careful, new node
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (isBridge[i]) {
            // merge to fat trees
            joinGraph(edges[i].first, edges[i].second);
        }
    }
    for (int i = 1; i <= m; ++i) {
        // multiply the compliment
        ret[i] *= (-dsu[findRoot(edges[i].first)] - ret[i]);
    }

    // calculate number of disconnected pairs
    memset(done, false, (n + 1) * sizeof(done[0])); // careful, 0
    int cntNode = 0;
    long long nodp = 0; // V <= 10^5
    for (int i = 1; i <= n; ++i) {
        int fatTree = findRoot(i); // careful, new graph
        if (!done[fatTree]) {
            done[fatTree] = true;
            int sz = -dsu[fatTree];
            nodp += 1LL * cntNode * sz;
            cntNode += sz;
        }
    }

    // add to total
    for (int i = 1; i <= m; ++i) {
        ret[i] += nodp;
    }
}

void calcF(int u, int par) {
    f[u] = -dsu[u];
    for (int v : tree[u]) { // careful, new graph
        if (v == par) {
            continue;
        }
        calcF(v, u);
        f[u] += f[v];
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
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u;
        int v;
        std::cin >> u >> v;
        if (u > v) { // just order hobby
            std::swap(u, v);
        }
        edges[i] = std::make_pair(u, v);
    }
}

void output(void) {
    buildFatForest();
    calcResult();
    for (int i = 1; i <= m; ++i) {
        std::cout << ret[i] << '\n';
    }
}