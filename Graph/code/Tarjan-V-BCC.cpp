#include <iostream>
#include <vector>

struct vertex_strongly_connected_components {
    int n, now, cnt;
    std::vector<int> dfn, low, sta;
    std::vector<std::vector<int>> &edge, vbcc;
    vertex_strongly_connected_components(std::vector<std::vector<int>> &edges) 
        : n((int) edges.size()), now(0), cnt(0), dfn(n), low(n), edge(edges) {}

    void dfs(int u) {
        dfn[u] = low[u] = ++now;
        sta.push_back(u);

        for (int v : edge[u]) {
            if (dfn[v] > 0) {
                low[u] = std::min(low[u], dfn[v]);
            } else {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    int idx = vbcc.size(), x;
                    vbcc.push_back({});
                    do {
                        x = sta.back();
                        sta.pop_back();
                        vbcc[idx].push_back(x);
                    } while (x != v);
                    vbcc[idx].push_back(u);
                }
            }
        }
    }

    std::vector<std::vector<int>> operator() () {
        for (int i = 0; i < n; i++) {
            if (edge[i].size() == 0) {
                vbcc.push_back({i});
            } else if (dfn[i] == 0) {
                dfs(i);
            }
        }
        return vbcc;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> edge(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        if (u == v) continue;
        u--, v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    auto vbcc = vertex_strongly_connected_components(edge)();

    std::cout << vbcc.size() << '\n';
    for (auto &v : vbcc) {
        std::cout << v.size();
        for (int x : v) {
            std::cout << ' ' << x + 1;
        }
        std::cout << '\n';
    }
    
    return 0;
}

