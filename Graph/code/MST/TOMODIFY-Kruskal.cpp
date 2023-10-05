#include <iostream>
#include <queue>

const static int N = 1e5 + 10;

struct node {
    int w, u, v;
    node(int w = 0, int u = 0, int v = 0) : w(w), u(u), v(v) {}
    bool operator < (const node & b) const {
        return w > b.w;
    }
};

int p[N];

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int kruskal(int n, std::priority_queue<node> &pque) {
    int cnt = n - 1;
    int ans = 0;
    while (!pque.empty() && cnt) {
        int w = pque.top().w, u = pque.top().u, v = pque.top().v;
        if (find(u) == find(v)) continue;
        p[u] = find(v);
        ans += w;
        --cnt;
    }
    if (cnt) return -1;
    else return ans;
}

int n;

void solve() {
    int cnt = n - 1;
    std::priority_queue<node> pque;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w;
            std::cin >> w;
            if (i == j) continue;
            pque.emplace(w, i, j);
            pque.emplace(w, j, i);
        }
    }
    int q;
    std::cin >> q;
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        pque.emplace(0, u, v);
        pque.emplace(0, v, u);
    }
    std::cout << kruskal(n, pque) << '\n';
}

int main() {
    std::cin.tie(0) -> sync_with_stdio(false);
    while (std::cin >> n) solve();
    return 0;
}
