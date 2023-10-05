#include <cassert>
#include <iostream>

namespace Solution {
    const int N = 1010, MAX_NODE = N * N;
    int nodeCnt, root[N], idx, ch[MAX_NODE][2];
    typedef int array_type[MAX_NODE];
    array_type type, pa, sz, sum, stack, lazy, value;

    int newNode() {
        int x = nodeCnt ++;
        pa[x] = 0;
        ch[x][0] = ch[x][1] = 0;
        type[x] = 2;
        sz[x] = 1;
        sum[x] = value[x] = lazy[x] = 0;
        return x;
    }

    void build(int n) {
        nodeCnt = 1;
        for (int i = 1; i <= n; i++) {
            int last = root[i] = newNode();
            sz[last] = n + 2;
            for (int j = 1, now; j <= n + 1; last = now, j++) {
                now = newNode();
                pa[now] = last;
                type[now] = 1;
                ch[last][1] = now;
                sz[now] = sz[last] - 1;
            }
        }
    }

    void push_up(int x) {
        sz[x] = sz[ch[x][0]] + 1 + sz[ch[x][1]];
        sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + value[x] + (sz[x] % 2 == 1 ? lazy[x] : 0);
    }

    void push_down(int x) {
        if (0 == lazy[x]) return;
        lazy[ch[x][0]] += lazy[x];
        lazy[ch[x][1]] += (sz[ch[x][0]] % 2 == 1 ? +1 : -1) * lazy[x];
        value[x] += (sz[ch[x][0]] % 2 == 0 ? +1 : -1) * lazy[x];
        if (ch[x][0]) push_up(ch[x][0]);
        if (ch[x][1]) push_up(ch[x][1]);
        lazy[x] = 0;
    }

    void rotate(int x) {
        int t = type[x], y = pa[x], z = ch[x][1 - t];
        type[x] = type[y];
        pa[x] = pa[y];
        if (type[x] != 2) ch[pa[x]][type[x]] = x;
        type[y] = 1 - t;
        pa[y] = x;
        ch[x][1 - t] = y;
        if (z) {
            type[z] = t;
            pa[z] = y;
        }
        ch[y][t] = z;
        push_up(y);
    }

    void splay(int x) {
        int top = 0;
        stack[top ++] = x;
        for (int i = x; type[i] != 2; i = pa[i]) {
            stack[top ++] = pa[i];
        }
        do {
            push_down(stack[-- top]);
        } while (top);

        while (type[x] != 2) {
            int y = pa[x];
            if (type[x] == type[y]) rotate(y);
            else rotate(x);
            if (type[x] == 2) break;
            rotate(x);
        }
        push_up(x);
    }

    int find(int x, int rank) {
        while (true) {
            push_down(x);
            if (sz[ch[x][0]] + 1 == rank) break;
            if (rank <= sz[ch[x][0]]) x = ch[x][0];
            else rank -= sz[ch[x][0]] + 1, x = ch[x][1];
        }
        return x;
    }

    void split(int &x, int &y, int a) {
        y = find(x, a + 1);
        splay(y);
        x = ch[y][0];
        type[x] = 2;
        ch[y][0] = 0;
        push_up(y);
    }

    void split3(int &x, int &y, int &z, int a, int b) {
        split(x, z, b);
        split(x, y, a - 1);
    }

    void join(int &x, int y) {
        x = find(x, sz[x]);
        splay(x);
        ch[x][1] = y;
        type[y] = 1;
        pa[y] = x;
        push_up(x);
    }

    void join3(int &x, int y, int z) {
        join(y, z);
        join(x, y);
    }

    void main(int n, int m) {
        build(n);
        while (m--) {
            int op, a, s, e;
            std::cin >> op >> a >> s >> e;
            if (op == 1) {
                int y, z;
                split3(root[a], y, z, s + 1, e + 1);
                lazy[y] ++;
                push_up(y);
                join3(root[a], y, z);
                std::cout << sum[root[a]] << '\n';
            } else if (op == 2) {
                int b, y, z, t;
                std::cin >> b;
                split3(root[a], y, z, s + 1, e + 1);
                split(root[b], t, sz[root[b]] - 1);
                join(root[a], z);
                join3(root[b], y, t);
                std::cout << sum[root[a]] << ' ' << sum[root[b]] << '\n';
            } else {
                assert(false);
            }
        }
    }
};

int main() {
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    int n, m;
    while (std::cin >> n >> m) {
        Solution::main(n, m);
    }
    return 0;
}
