#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

constexpr int inf = 1e9;

template <typename T, typename DT> 
std::vector<DT> 
spfa(const std::vector<std::vector<std::pair<int, T> > > &edge, int n, int s) {
    std::vector<DT> dis(n, inf);
    std::vector<bool> vis(n, false);
    std::vector<int> cnt(n, 0);

    std::queue<int> que;
    que.push(s);
    vis[s] = true;
    dis[s] = 0;
    cnt[s] = 0;

    while (not que.empty()) {
        int u = que.front(); 
        que.pop();
        vis[u] = false; // * note: reset vis!
        for (auto [v, w] : edge[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (not vis[v]) {
                    cnt[v] ++;
                    que.push(v);
                    vis[v] = true;
                    if (cnt[v] > n) {
                        return {};
                    }
                }
            }
        }
    }
    return dis;
}

template <typename T, typename DT>
std::vector<DT> 
dijkstra(const std::vector<std::vector<std::pair<int, T> > > &edge, int n, int s) {
    std::vector<DT> dis(n, inf);
    std::vector<bool> vis(n, false);
    using PLI = std::pair<DT, int>;
    std::priority_queue< PLI, std::vector<PLI>, std::greater<PLI> > pque;
    pque.emplace(0, s);
    dis[s] = 0;
    while (!pque.empty()) {
        int u = pque.top().second;
        pque.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [v, w] : edge[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pque.emplace(dis[v], v);
            }
        }
    }
    return dis;
}

template <typename T, typename DT>
std::vector<std::vector<DT>> 
johnson(std::vector<std::vector<std::pair<int, T> > > edge, int n) {
    assert((int) edge.size() == n);

    edge.push_back({}); // * note 1: edge changed (1) 
    for (int i = 0; i < n; i++) {
        edge[n].emplace_back(i, 0ll);
    }
    auto dis0 = spfa<T, DT>(edge, n + 1, n);

    bool has_negative_cycle = dis0.empty();
    if (has_negative_cycle) {
        return {};
    }

    for (int u = 0; u < n; u++) {
        for (auto &[v, w] : edge[u]) {
            w += dis0[u] - dis0[v]; // * note 2: edge changed (2)
        }
    }

    std::vector<std::vector<DT>> dis;
    for (int u = 0; u < n; u++) {
        dis.emplace_back(dijkstra<T, DT>(edge, n, u));
        for (int v = 0; v < n; v++) {
            if (dis[u][v] != inf) {
                dis[u][v] -= dis0[u] - dis0[v];
            }
        }
    }

    return dis; // bool has_neg_cyc = dis.empty();
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> edge(n);
    while (m--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--; v--;
        edge[u].emplace_back(v, w);
    }

    auto dis = johnson<int, int>(edge, n);
    bool has_neg_cyc = dis.empty();
    if (has_neg_cyc) {
        std::cout << "-1\n";
        return 0;
    }

    for (int u = 0; u < n; u++) {
        long long ans = 0ll;
        for (int v = 0; v < n; v++) {
            ans += 1ll * (v + 1) * dis[u][v];
        }
        std::cout << ans << '\n';
    }

    return 0;
}

