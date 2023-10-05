#include <iostream>
#include <cassert>
#include <climits>

const int N = 5e5 + 10;

struct Node {
    int l, r, key, val, sz;
    Node () {}
    Node (int val) : l(0), r(0), key(std::rand()), val(val), sz(1) {}
    Node (const Node &b) : l(b.l), r(b.r), key(b.key), val(b.val), sz(b.sz) {}
} tr[N * 100];

int tot, dl, dr, tmp, root[N];

int newNode(int val) {
    tr[++tot] = Node(val);
    return tot;
}
int clone(int u) {
    tr[++tot] = Node(tr[u]);
    return tot;
}

void pushup(int u) {
    tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
}

void split(int u, int x, int &l, int &r) {
    if (!u) return l = r = 0, void();
    if (tr[u].val <= x) 
        l = clone(u), split(tr[l].r, x, tr[l].r, r), pushup(l);
    else 
        r = clone(u), split(tr[r].l, x, l, tr[r].l), pushup(r);
}

int merge(int l, int r) {
    if (!l || !r) return l | r;
    int p;
    if (tr[l].key < tr[r].key) 
        p = clone(l), tr[p].r = merge(tr[p].r, r);
    else 
        p = clone(r), tr[p].l = merge(l, tr[p].l);
    pushup(p);
    return p;
}

void insert(int &rt, int x) {
    split(rt, x, dl, dr);
    rt = merge(merge(dl, newNode(x)), dr);
}

void erase(int &rt, int x) {
    split(rt, x, dl, dr);
    split(dl, x - 1, dl, tmp);
    tmp = merge(tr[tmp].l, tr[tmp].r);
    rt = merge(merge(dl, tmp), dr);
}

int getrk(int &rt, int x) {
    split(rt, x - 1, dl, dr);
    int rnk = tr[dl].sz + 1;
    rt = merge(dl, dr);
    return rnk;
}

int k_th(int u, int k) {
    while (u) {
        if (k <= tr[tr[u].l].sz) u = tr[u].l;
        else if (tr[tr[u].l].sz + 1 == k) break;
        else k -= tr[tr[u].l].sz + 1, u = tr[u].r;
    }
    return tr[u].val;
}

int pre(int &rt, int x) {
    split(rt, x - 1, dl, dr);
    if (!dl) return -INT_MAX;
    int res = k_th(dl, tr[dl].sz);
    rt = merge(dl, dr);
    return res;
}

int nxt(int &rt, int x) {
    split(rt, x, dl, dr);
    if (!dr) return +INT_MAX;
    int res = k_th(dr, 1);
    rt = merge(dl, dr);
    return res;
}

int main() {
    std::cin.tie(0) -> sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (int cur = 1; cur <= n; ++cur) {
        int ver, op, x, &rt = root[cur];
        std::cin >> ver >> op >> x;
        rt = root[ver];
        if (op == 1) insert(rt, x);
        else if (op == 2) erase(rt, x);
        else if (op == 3) std::cout << getrk(rt, x) << '\n';
        else if (op == 4) std::cout << k_th(rt, x) << '\n';
        else if (op == 5) std::cout << pre(rt, x) << '\n';
        else if (op == 6) std::cout << nxt(rt, x) << '\n';
        else assert(false);
    }
    return 0;
}
