#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>

const int maxn = 300010;
int op, n, m, u, v, c;

struct lct_chain {
    int ch[maxn][2], pa[maxn], val[maxn], sum[maxn], rev[maxn];

    void clear(int x) {
        ch[x][0] = ch[x][1] = pa[x] = val[x] = sum[x] = rev[x] = 0;
    }

    int get(int x) { return (ch[pa[x]][1] == x); }

    int isroot(int x) {
        clear(0);
        return ch[pa[x]][0] != x && ch[pa[x]][1] != x;
    }

    void maintain(int x) {
        clear(0);
        sum[x] = sum[ch[x][0]] ^ val[x] ^ sum[ch[x][1]];
    }

    void down_rev(int x) {
        if (x == 0) return;
        rev[x] ^= 1;
        std::swap(ch[x][0], ch[x][1]);
    }

    void pushdown(int x) {
        clear(0);
        if (rev[x] == 1) {
            down_rev(ch[x][0]);
            down_rev(ch[x][1]);
            rev[x] = 0;
        }
    }

    void update(int x) {
        if (!isroot(x)) update(pa[x]);
        pushdown(x);
    }

    void rotate(int x) {
        int y = pa[x], z = pa[y], chx = get(x), chy = get(y);
        pa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        pa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        pa[y] = x;
        maintain(y);
        maintain(x);
        maintain(z);
    }

    void splay(int x) {
        update(x);
        for (int f = pa[x]; f = pa[x], !isroot(x); rotate(x)) {
            if (!isroot(f)) {
                rotate(get(x) == get(f) ? f : x);
            }
        }
    }

    void access(int x) {
        for (int f = 0; x; f = x, x = pa[x]) {
            splay(x);
            ch[x][1] = f;
            maintain(x);
        }
    }

    void makeroot(int x) {
        access(x);
        splay(x);
        down_rev(x);
    }

    int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
    }

    void split(int u, int v) {
        makeroot(u); 
        access(v); 
        splay(v);
    }

    void link(int u, int v) {
        if (find(u) != find(v)) {
            makeroot(u);
            pa[u] = v;
        }
    }

    void cut(int u, int v) {
        split(u, v);
        if (ch[v][0] == u && !ch[u][1]) {
            ch[v][0] = pa[u] = 0;
        }
    }
} st;

int main() {
    std::scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        std::scanf("%d", &st.val[i]);
        st.maintain(i);
    }
    while (m--) {
        std::scanf("%d%d%d", &op, &u, &v);
        if (op == 0) {
            st.split(u, v);
            std::printf("%d\n", st.sum[v]);
        } else if (op == 1) {
            st.link(u, v);
        } else if (op == 2) {
            st.cut(u, v);
        } else if (op == 3) {
            st.splay(u);
            st.val[u] = v;
            st.maintain(u);
        } else {
            assert(false);
        }
    }
    return 0;
}

