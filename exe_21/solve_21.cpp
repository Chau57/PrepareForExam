#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

typedef long long i64;
const int MAXN = 1e5 + 5;
const i64 INF = 1e18;

// Cấu trúc cạnh đồ thị
struct Edge {
    i64 u, v, w;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

// Cấu trúc DSU dùng để nhảy nhanh trên chu trình (DSU Path Compression)
struct DSU {
    i64 parent[MAXN];
    void init(int n) {
        for (int i = 0; i <= n; i++) parent[i] = i;
    }
    i64 find(i64 x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void merge(i64 child, i64 ancestor) {
        child = find(child);
        ancestor = find(ancestor);
        if (child != ancestor) parent[child] = ancestor;
    }
} dsu_jump;

// Dữ liệu cho một ứng viên cây khung (thay thế cạnh del bằng add)
struct Candidate {
    i64 del_edge_idx, add_edge_idx, from_node_id, total_val;
    bool operator<(const Candidate& other) const {
        return total_val > other.total_val; // Priority queue ưu tiên giá trị nhỏ
    }
};

Edge all_edges[MAXN];
int n, m, k;

// Cấu trúc một trạng thái cây khung
struct MSTNode {
    i64 total_val;
    i64 dft_counter;
    vector<vector<i64>> adj;
    vector<i64> status;     // 1: trong cây, 2: cấm, 3: bắt buộc
    vector<i64> parent;     // Cha trong cây DFS
    vector<i64> dfn, siz;   // Phục vụ kiểm tra tổ tiên nhanh
    vector<i64> edge_to_p;  // ID cạnh nối node v với cha nó

    void dfs(i64 u, i64 p) {
        parent[u] = p;
        dfn[u] = ++dft_counter;
        siz[u] = 1;
        for (i64 edge_idx : adj[u]) {
            i64 v = (all_edges[edge_idx].u == u) ? all_edges[edge_idx].v : all_edges[edge_idx].u;
            if (v != p) {
                edge_to_p[v] = edge_idx;
                dfs(v, u);
                siz[u] += siz[v];
            }
        }
    }

    bool is_ancestor(i64 u, i64 v) {
        return dfn[u] <= dfn[v] && dfn[u] + siz[u] > dfn[v];
    }

    void init_tree_info() {
        parent.assign(n, 0);
        dfn.assign(n, 0);
        siz.assign(n, 0);
        edge_to_p.assign(n, -1);
        dft_counter = 0;
        dfs(0, 0);
    }

    // Hàm tìm cặp cạnh thay thế tốt nhất (suc)
    Candidate find_best_replacement() {
        dsu_jump.init(n);
        i64 best_del = -1, best_add = -1, min_delta = INF;

        for (int i = 0; i < m; i++) {
            if (status[i] != 0) continue; // Chỉ xét cạnh ngoài cây
            
            i64 u_start = all_edges[i].u;
            i64 v_start = all_edges[i].v;
            
            // Duyệt chu trình bằng cách nhảy DSU từ 2 đầu u, v lên LCA
            i64 u = u_start, v = v_start;
            for (int step = 0; step < 2; step++) {
                while (true) {
                    u = dsu_jump.find(u);
                    if (is_ancestor(u, v)) break;

                    i64 e_idx = edge_to_p[u];
                    if (status[e_idx] != 3) { // Không thay thế cạnh bắt buộc
                        i64 current_delta = all_edges[i].w - all_edges[e_idx].w;
                        if (current_delta < min_delta) {
                            min_delta = current_delta;
                            best_del = e_idx;
                            best_add = i;
                        }
                    }
                    dsu_jump.merge(u, parent[u]);
                    u = dsu_jump.find(u);
                }
                u = v_start; v = u_start; // Đảo lại để duyệt nhánh bên kia
            }
        }
        return {best_del, best_add, -1, min_delta};
    }
};



vector<MSTNode> mst_list;
MSTNode base_mst;

void get_first_mst() {
    base_mst.adj.resize(n);
    base_mst.status.assign(m, 0);
    base_mst.total_val = 0;
    
    dsu_jump.init(n);
    int count = 0;
    for (int i = 0; i < m; i++) {
        i64 u = dsu_jump.find(all_edges[i].u);
        i64 v = dsu_jump.find(all_edges[i].v);
        if (u != v) {
            base_mst.status[i] = 1;
            base_mst.total_val += all_edges[i].w;
            base_mst.adj[all_edges[i].u].push_back(i);
            base_mst.adj[all_edges[i].v].push_back(i);
            dsu_jump.merge(u, v);
            if (++count == n - 1) break;
        }
    }
}

i64 solve_kmst() {
    priority_queue<Candidate> pq;
    pq.push({-1, -1, -1, base_mst.total_val});
    
    int current_id = 0;
    while (!pq.empty()) {
        Candidate top = pq.top(); pq.pop();
        // printf("%lld\n", top.total_val);
        if (--k == 0) {
            return top.total_val;
        }

        MSTNode &node = mst_list[current_id];
        if (top.from_node_id == -1) {
            node = base_mst;
        } else {
            // Kế thừa từ cây cha và thực hiện thay thế cạnh
            node = mst_list[top.from_node_id];
            node.total_val = top.total_val;
            
            // Xóa cạnh cũ
            i64 u_del = all_edges[top.del_edge_idx].u, v_del = all_edges[top.del_edge_idx].v;
            auto it1 = find(node.adj[u_del].begin(), node.adj[u_del].end(), top.del_edge_idx);
            node.adj[u_del].erase(it1);
            auto it2 = find(node.adj[v_del].begin(), node.adj[v_del].end(), top.del_edge_idx);
            node.adj[v_del].erase(it2);

            // Thêm cạnh mới
            i64 u_add = all_edges[top.add_edge_idx].u, v_add = all_edges[top.add_edge_idx].v;
            node.adj[u_add].push_back(top.add_edge_idx);
            node.adj[v_add].push_back(top.add_edge_idx);

            // Phân hoạch (Partitioning): 
            // Cây mới: cạnh del bị loại bỏ hoàn toàn (0), cạnh add là bắt buộc (3)
            node.status[top.del_edge_idx] = 0;
            node.status[top.add_edge_idx] = 3;
            
            // Cây cha: cạnh add bị cấm (2) để tránh sinh trùng cây này lần nữa
            mst_list[top.from_node_id].status[top.add_edge_idx] = 2;
            Candidate next_from_parent = mst_list[top.from_node_id].find_best_replacement();
            if (next_from_parent.add_edge_idx != -1) {
                next_from_parent.from_node_id = top.from_node_id;
                next_from_parent.total_val = mst_list[top.from_node_id].total_val + next_from_parent.total_val;
                pq.push(next_from_parent);
            }
        }

        node.init_tree_info();
        Candidate next_from_current = node.find_best_replacement();
        if (next_from_current.add_edge_idx != -1) {
            next_from_current.from_node_id = current_id;
            next_from_current.total_val = node.total_val + next_from_current.total_val;
            pq.push(next_from_current);
        }
        current_id++;
    }
    // while (k-- > 0) printf("-1\n");
    return -1;
}

int main() {
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;
    for (int i = 0; i < m; i++) {
        scanf("%lld %lld %lld", &all_edges[i].u, &all_edges[i].v, &all_edges[i].w);
        all_edges[i].u--; all_edges[i].v--;
    }
    sort(all_edges, all_edges + m, compareEdges);
    
    mst_list.resize(k + 1);
    get_first_mst();
    printf("%lld\n", solve_kmst());
    
    return 0;
}