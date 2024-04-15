struct item {
    long long v;
};
 
struct segtree {
    vector<item> operations;
    item NO_OP = {LLONG_MAX};
    item NE = {0};
    int sz = 1;
 
    void init(int n) {
        while (sz < n)
            sz *= 2;
        operations.assign(2 * sz, {NE});
    }
 
    item single(int x) {
        return {x};
    }
 
    item operation(item a, item b) { // assign operation
        if (b.v == NO_OP.v)
            return a;
        return b;
    }
 
    void apply_operation(item &a, item b) {
        a = operation(a, b);
    }
 
    void propagte(int x, int lx, int rx) {
        if (rx - lx == 1 || operations[x].v == NO_OP.v) // leaf node
            return;
        apply_operation(operations[x * 2 + 1], operations[x]);
        apply_operation(operations[x * 2 + 2], operations[x]);
        operations[x] = NO_OP;
    }
 
    void modify(int l, int r, int v, int x, int lx, int rx) {
        propagte(x, lx, rx);
        if (rx <= l || lx >= r)
            return;
        if (lx >= l && rx <= r) {
            apply_operation(operations[x], {v});
            return;
        }
        int m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
    }
 
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, sz);
    }
 
    item get(int i, int x, int lx, int rx) {
        propagte(x, lx, rx);
        if (rx - lx == 1) {
            return operations[x];
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            return get(i, x * 2 + 1, lx, m);
        } else {
            return get(i, x * 2 + 2, m, rx);
        }
    }
 
    item get(int i) {
        return get(i, 0, 0, sz);
    }
};