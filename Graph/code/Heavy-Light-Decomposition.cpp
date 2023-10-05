#include <iostream>
#include <vector>

const int N = 1'000'010;
const int T = 18;
std::vector<int> edge[N];

int size[N], heavy[N], pa[N][T], depth[N];
void pre_dfs(int u, int p, int dep) {
    size[u] = 1;
    pa[u][0] = p;
    depth[u] = dep;
    for (int t = 0; t + 1 < T; t++) {
        pa[u][t + 1] = pa[pa[u][t]][t];
    }
    for (int v : edge[u]) {
        pre_dfs(v, u, dep + 1);
        size[u] += size[v];
        if (size[v] > size[heavy[u]]) {
            heavy[u] = v;
        }
    }
}

int tin[N], tout[N], top[N], now;
void dfs(int u, int tp) {
    tin[u] = now ++;
    top[u] = tp;
    if (heavy[u]) dfs(heavy[u], tp);
    for (int v : edge[u]) {
        if (v == heavy[u]) continue;
        dfs(v, v);
    }
    tout[u] = now;
}

int a[N], val[N];
using int64 = long long;
struct node {
    int64 sum, lazy;
} tr[N * 4];

#define lc (u * 2 + 1)
#define rc (u * 2 + 2)
#define mid (l + (r - l) / 2)

void push_up(int u, int l, int r) {
    tr[u].sum = tr[lc].sum + tr[rc].sum;
    tr[u].lazy = 0ll;
}

void down(int u, int l, int r, int64 val) {
    tr[u].sum += (r - l) * val;
    tr[u].lazy += val;
}

void push_down(int u, int l, int r) {
    int64 lazy = tr[u].lazy;
    if (lazy != 0ll) {
        tr[u].lazy = 0ll;
        down(lc, l, mid, lazy);
        down(rc, mid, r, lazy);
    }
}

void build(int u, int l, int r) {
    if (l + 1 == r) {
        tr[u].sum = val[l];
        tr[u].lazy = 0ll;
    } else {
        build(lc, l, mid);
        build(rc, mid, r);
        push_up(u, l, r);
    }
}

void range_add(int u, int l, int r, int lo, int hi, int val) {
    if (lo <= l and r <= hi) {
        down(u, l, r, val);
    } else if (hi <= l or r <= lo or l + 1 == r) {
        // pass
    } else {
        push_down(u, l, r);
        range_add(lc, l, mid, lo, hi, val);
        range_add(rc, mid, r, lo, hi, val);
        push_up(u, l, r);
    }
}

int64 range_sum(int u, int l, int r, int lo, int hi) {
    if (lo <= l and r <= hi) {
        return tr[u].sum;
    } else if (hi <= l or r <= lo or l + 1 == r) {
        return 0ll;
    } else {
        push_down(u, l, r);
        int64 res = range_sum(lc, l, mid, lo, hi) + range_sum(rc, mid, r, lo, hi);
        push_up(u, l, r);
        return res;
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    for (int i = 2, p; i <= n; i++) {
        std::cin >> p;
        edge[p].push_back(i);
    }

    pre_dfs(1, 1, 0);
    dfs(1, 1);

    for (int i = 1; i <= n; i++) {
        val[tin[i]] = a[i];
    }
    build(0, 0, n);

    int root = 1;

    auto anc_of = [&] (int u, int d) {
        for (int j = 0; j < T; j++) {
            if ((d >> j) & 1) {
                u = pa[u][j];
            }
        }
        return u;
    };

    auto is_child_of = [&] (int u, int v) -> bool {
        return (tin[v] <= tin[u] and tout[u] <= tout[v]);
    };

    auto add_path = [&] (int u, int v, int k) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
            range_add(0, 0, n, tin[top[u]], tin[u] + 1, k);
            u = pa[top[u]][0];
        }
        if (depth[u] < depth[v]) std::swap(u, v);
        range_add(0, 0, n, tin[v], tin[u] + 1, k);
    };

    auto add_subtree = [&] (int u, int k) {
        if (root == u) {
            range_add(0, 0, n, tin[1], tout[1], +k);
        } else if (is_child_of(root, u)) {
            int v = anc_of(root, depth[root] - depth[u] - 1);
            range_add(0, 0, n, tin[1], tout[1], +k);
            range_add(0, 0, n, tin[v], tout[v], -k);
        } else {
            range_add(0, 0, n, tin[u], tout[u], +k);
        }
    };

    auto query_path = [&] (int u, int v) {
        int64 res = 0ll;
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
            res += range_sum(0, 0, n, tin[top[u]], tin[u] + 1);
            u = pa[top[u]][0];
        }
        if (depth[u] < depth[v]) std::swap(u, v);
        res += range_sum(0, 0, n, tin[v], tin[u] + 1);
        return res;
    };

    auto query_subtree = [&] (int u) {
        if (root == u) {
            return range_sum(0, 0, n, tin[1], tout[1]);
        } else if (is_child_of(root, u)) {
            int v = anc_of(root, depth[root] - depth[u] - 1);
            return range_sum(0, 0, n, tin[1], tout[1]) 
                 - range_sum(0, 0, n, tin[v], tout[v]);
        } else {
            return range_sum(0, 0, n, tin[u], tout[u]);
        }
    };

    int m;
    std::cin >> m;
    while (m--) {
        int op, u, v, k;
        std::cin >> op;
        switch (op) {
        case 1:
            std::cin >> u;
            root = u;
            break;
        case 2:
            std::cin >> u >> v >> k;
            add_path(u, v, k);
            break;
        case 3:
            std::cin >> u >> k;
            add_subtree(u, k);
            break;
        case 4:
            std::cin >> u >> v;
            std::cout << query_path(u, v) << '\n';
            break;
        case 5:
            std::cin >> u;
            std::cout << query_subtree(u) << '\n';
            break;
        }
    }

    return 0;
}

