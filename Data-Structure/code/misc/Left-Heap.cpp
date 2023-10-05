struct left_heap {
    left_heap *lc, *rc;
    int val, npl;
    left_heap() {}
    left_heap(left_heap *_l, left_heap *_r, int _v) : lc(_l), rc(_r), val(_v) {
        if (lc->npl < rc->npl) std::swap(lc, rc);
        npl = rc->npl + 1;
    }
} pool[N], *tail = pool, *nil, *hp[N];

left_heap *merge(left_heap *a, left_heap *b) {
    if (a == nil) return b;
    if (b == nil) return a;
    if (a->val > b->val) std::swap(a, b); // 小顶堆
    a->rc = merge(a->rc, b);
    if (a->lc != nil || (a->lc->npl < a->rc->npl)) std::swap(a->lc, a->rc);
    a->npl = a->rc->npl;
    return a;
}

int del_max(left_heap *&h) {
    if (h == nil) return -1;
    int ret = h->val;
    h = merge(h->lc, h->rc);
    return ret;
}

void left_heap_init() {
    nil = new left_heap();
    nil->lc = nil->rc = nil;
    nil->val = inf;
    nil->npl = 0;
}
