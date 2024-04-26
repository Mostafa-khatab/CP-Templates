struct item {
    ll v;
};
 
struct segtree {
    vector<item> seg, lazy;
    item NE = {inf};
    int sz = 1;
 
    void init(int n) {
        while (sz < n)
            sz *= 2;
        seg.assign(2 * sz, {0LL});
        lazy.assign(2 * sz, {0LL}); 
    }
 
    item merge(item a, item b) {
        if (a.v <= b.v) return a;
        return b;
    }
 
    void propagate(int l, int r, int x) { 
        if (lazy[x].v == 0) return;
        if (l != r) {
            lazy[2 * x + 1].v += lazy[x].v;
            lazy[2 * x + 2].v += lazy[x].v;
        }
        seg[x].v += lazy[x].v;
        lazy[x].v = 0;
    }
 
    void update(int l, int r, int x, int lx, int rx, ll val) {
        propagate(l, r, x);
        if (l > rx || r < lx) return;
        if (l >= lx && r <= rx) {
            lazy[x].v += val;
            propagate(l, r, x);
            return;
        }
        ll mid = (l + r) / 2;
        update(l, mid, 2 * x + 1, lx, rx, val);
        update(mid + 1, r, 2 * x + 2, lx, rx, val);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }
 
    void update(int l, int r, ll val) {
        update(0, sz - 1, 0, l, r, val);
    }
 
    item calc(int l, int r, int x, int lx, int rx) {
        propagate(l, r, x);
        if (l > rx || r < lx) return NE;
        if (l >= lx && r <= rx) return seg[x];
        ll mid = (l + r) / 2;
        return merge(calc(l, mid, 2 * x + 1, lx, rx), calc(mid + 1, r, 2 * x + 2, lx, rx));
    }
 
 
    item calc(int l, int r) {
        return calc(0, sz - 1, 0, l, r);
    }
};