#include <vector>
#include <numeric>
#include <iostream>
#include <functional>

std::vector<int> dominator(const std::vector<std::vector<int>> &g, int s) {
    int n = (int) g.size();
    std::vector<int> pos(n, -1), p, label(n), dom(n), sdom(n), dsu(n), par(n);
    std::vector<std::vector<int>> rg(n), bucket(n);
    std::function<void(int)> dfs = [&](int u) {
        int t = (int) p.size();
        p.push_back(u);
        label[t] = sdom[t] = dsu[t] = pos[u] = t;
        for (int v : g[u]) {
            if (pos[v] == -1) {
                dfs(v);
                par[pos[v]] = t;
            }
            rg[pos[v]].push_back(t);
        }
    };
    std::function<int(int, int)> find = [&](int u, int x) {
        if (u == dsu[u]) {
            return x ? -1 : u;
        }
        int v = find(dsu[u], x + 1);
        if (v < 0) {
            return u;
        }
        if (sdom[label[dsu[u]]] < sdom[label[u]]) {
            label[u] = label[dsu[u]];
        }
        dsu[u] = v;
        return x ? v : label[u];
    };
    dfs(s);
    std::iota(dom.begin(), dom.end(), 0);
    for (int i = (int) p.size() - 1; i >= 0; i -= 1) {
        for (int j : rg[i]) {
            sdom[i] = std::min(sdom[i], sdom[find(j, 0)]);
        }
        if (i) {
            bucket[sdom[i]].push_back(i);
        }
        for (int k : bucket[i]) {
            int j = find(k, 0);
            dom[k] = sdom[j] == sdom[k] ? sdom[j] : j;
        }
        if (i > 1) {
            dsu[i] = par[i];
        }
    }
    for (int i = 1; i < (int) p.size(); i += 1) {
        if (dom[i] != sdom[i]) {
            dom[i] = dom[dom[i]];
        }
    }
    std::vector<int> res(n, -1);
    res[s] = s;
    for (int i = 1; i < (int) p.size(); i += 1) {
        res[p[i]] = p[dom[i]];
    }
    return res;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < m; i += 1) {
        std::cin >> u >> v;
        g[u - 1].push_back(v - 1);
    }
    auto p = dominator(g, 0);
    std::vector<std::vector<int>> t(n);
    for (int i = 1; i < n; i += 1) {
        t[p[i]].push_back(i);
    }
    std::vector<int> ans(n, 1);
    std::function<void(int)> dfs = [&](int u) {
        for (int v : t[u]) {
            dfs(v);
            ans[u] += ans[v];
        }
    };
    dfs(0);
    for (int x : ans) {
        std::cout << x << " ";
    }
}
