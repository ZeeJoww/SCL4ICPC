#include <algorithm>
#include <iostream>
#include <vector>

constexpr int N = 2'000'000 + 10;
constexpr int T = 30;
int trie[N * T][2], now = 1;

void insert(int x, int u = 0, int t = T - 1) {
    for (int j = t; j >= 0; j--) {
        int c = ((x >> j) & 1);
        if (not trie[u][c]) {
            trie[u][c] = now ++;
        }
        u = trie[u][c];
    }
}

int minxor(int x, int u = 0, int t = T - 1) {
    int res = 0;
    for (int j = t; j >= 0; j--) {
        int c = ((x >> j) & 1);
        if (not trie[u][c]) {
            res |= (1 << j);
            c ^= 1;
        }
        u = trie[u][c];
    }
    return res;
}

long long dfs(const std::vector<int> &a, int l, int r, int u, int t) {
    if (r - l == 1 or t == -1) {
        return 0ll;
    }
    if (trie[u][0] == 0 or trie[u][1] == 0) {
        return dfs(a, l, r, trie[u][0] | trie[u][1], t - 1);
    }

    int val = a[r - 1] & (~((1 << t) - 1));
    int m = std::lower_bound(a.begin() + l, a.begin() + r, val) - a.begin();

    int res = 1 << t;
    if (m - l <= r - m) {
        for (int i = l; i < m; i++) {
            res = std::min(res, minxor(a[i], trie[u][1], t - 1));
        }
    } else {
        for (int i = m; i < r; i++) {
            res = std::min(res, minxor(a[i], trie[u][0], t - 1));
        }
    }

    return (1 << t) + res + dfs(a, l, m, trie[u][0], t - 1) + dfs(a, m, r, trie[u][1], t - 1);
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        insert(a[i]);
    }
    std::sort(a.begin(), a.end());

    long long ans = dfs(a, 0, n, 0, T - 1);
    std::cout << ans << std::endl;

    return 0;
}

