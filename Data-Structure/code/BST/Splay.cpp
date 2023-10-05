#include <iostream>
#include <algorithm>

const static int maxn = 5e5 + 10, inf = 1e9;

struct Node {
    int val, lsum, rsum, mxsum, sum, ch[2], p, sz;
    bool rev, same;
    Node () {}
    Node (int v, int p) : val(v), mxsum(v), sum(v), p(p), sz(1), rev(false), same(false) {
        ch[0] = ch[1] = 0;
        lsum = rsum = std::max(0, v);
    }
} tr[maxn];

int nodes[maxn], top, root;
void initNodes() {
    tr[0].mxsum = -inf;
    for (int i = maxn - 1; i; --i) nodes[++top] = i;
}
void delNode(int u) { nodes[++top] = u; }
int newNode(int v, int p) {
    int u = nodes[top--];
    tr[u] = Node(v, p);
    return u;
}

void pushup(int x) {
    Node & u = tr[x], & lc = tr[tr[x].ch[0]], & rc = tr[tr[x].ch[1]];
    u.sz = lc.sz + rc.sz + 1;
    u.sum = lc.sum + rc.sum + u.val;
    u.lsum = std::max(lc.lsum, lc.sum + u.val + rc.lsum);
    u.rsum = std::max(rc.rsum, rc.sum + u.val + lc.rsum);
    u.mxsum = std::max( { lc.mxsum, rc.mxsum, lc.rsum + u.val + rc.lsum } );
}

void downlz(int x, int v) {
    if (!x) return;
    Node & u = tr[x];
    u.same = true;
    u.val = v;
    u.sum = v * u.sz;
    u.lsum = u.rsum = std::max(0, u.sum);
    u.mxsum = std::max(v, u.sum);
}

void downrev(int x) {
    if (!x) return;
    tr[x].rev ^= true;
    std::swap(tr[x].ch[0], tr[x].ch[1]);
    std::swap(tr[x].lsum, tr[x].rsum);
}

void pushdown(int x) {
    if (tr[x].same) {
        downlz(tr[x].ch[0], tr[x].val);
        downlz(tr[x].ch[1], tr[x].val);
        tr[x].same = tr[x].rev = false;
    } else if (tr[x].rev) {
        downrev(tr[x].ch[0]);
        downrev(tr[x].ch[1]);
        tr[x].rev = false;
    }
}

int get(int x) {
    return tr[tr[x].p].ch[1] == x;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int kx = get(x), ky = get(y);
    tr[y].ch[kx] = tr[x].ch[kx ^ 1];
    if (tr[x].ch[kx ^ 1]) tr[tr[x].ch[kx ^ 1]].p = y;
    tr[x].ch[kx ^ 1] = y;
    tr[y].p = x;
    tr[x].p = z;
    if (z) tr[z].ch[ky] = x;
    pushup(y);
    pushup(x);
}

void splay(int x, int goal) {
    for (int p; p = tr[x].p, p != goal; rotate(x)) {
        if (tr[p].p != goal) 
            rotate( get(x) ^ get(p) ? x : p );
    }
    if (goal == 0) root = x;
}

int k_th(int k) {
    int u = root;
    while (u) {
        pushdown(u);
        if (k <= tr[tr[u].ch[0]].sz) u = tr[u].ch[0];
        else if (k == tr[tr[u].ch[0]].sz + 1) break;
        else k -= tr[tr[u].ch[0]].sz + 1, u = tr[u].ch[1];
    }
    return u;
}

void recycle(int x) {
    if (x == 0) return;
    recycle(tr[x].ch[0]);
    recycle(tr[x].ch[1]);
    delNode(x);
}

int a[maxn];
int build(int l, int r, int p) {
    int m = (l + r) / 2;
    int u = newNode(a[m], p);
    if (l < m) tr[u].ch[0] = build(l, m, u);
    if (m + 1 < r) tr[u].ch[1] = build(m + 1, r, u);
    pushup(u);
    return u;
}

int main() {
    std::cin.tie(0) -> sync_with_stdio(false);
    initNodes();
    int n, m;
    std::cin >> n >> m;
    a[0] = a[n + 1] = -inf;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    root = build(0, n + 2, 0);
    while (m--) {
        std::string op;
        std::cin >> op;
        int posi, tot, c;
        if (op == "INSERT") {
            std::cin >> posi >> tot;
            for (int i = 0; i < tot; ++i) {
                std::cin >> a[i];
            }
            int L = k_th(posi + 1), R = k_th(posi + 2);
            splay(L, 0), splay(R, L);
            tr[R].ch[0] = build(0, tot, R);
            pushup(R), pushup(L);
        } else if (op == "DELETE") {
            std::cin >> posi >> tot;
            int L = k_th(posi), R = k_th(posi + tot + 1);
            splay(L, 0), splay(R, L);
            recycle(tr[R].ch[0]);
            tr[R].ch[0] = 0;
            pushup(R), pushup(L);
        } else if (op == "MAKE-SAME") {
            std::cin >> posi >> tot >> c;
            int L = k_th(posi), R = k_th(posi + tot + 1);
            splay(L, 0), splay(R, L);
            downlz(tr[R].ch[0], c);
            pushup(R), pushup(L);
        } else if (op == "REVERSE") {
            std::cin >> posi >> tot;
            int L = k_th(posi), R = k_th(posi + tot + 1);
            splay(L, 0), splay(R, L);
            downrev(tr[R].ch[0]);
            pushup(R), pushup(L);
        } else if (op == "GET-SUM") {
            std::cin >> posi >> tot;
            int L = k_th(posi), R = k_th(posi + tot + 1);
            splay(L, 0), splay(R, L);
            std::cout << tr[tr[R].ch[0]].sum << '\n';
        } else /* op == "MAX-SUM" */ {
            std::cout << tr[root].mxsum << '\n';
        }
    }
    return 0;
}
