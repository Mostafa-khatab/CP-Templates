struct item {
    long long v;
};

struct segtree {
    vector<item> val;
    item NE = {0};
    int sz = 1;

    void init(int n) {
        while (sz < n)
            sz *= 2;
        val.assign(2 * sz, NE);
    }

    item single(int x) {
        return {x};
    }

    item merge(item a, item b) {
        item ret;
        ret.v = a.v + b.v;
        return ret;
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (rx <= l || lx >= r)
            return;
        if (lx >= l && rx <= r) {
            val[x] = merge(val[x], single(v));
            return;
        }
        int m = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, m);
        add(l, r, v, 2 * x + 2, m, rx);
    }

    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, sz);
    }

    item get(int i, int x, int lx, int rx) {
        if (rx - lx == 1) {
            return val[x];
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            return merge(get(i, x * 2 + 1, lx, m), val[x]);
        }
        else{
            return merge(get(i, x * 2 + 2, m, rx), val[x]);
        }
    }

    item get(int i) {
        return get(i, 0, 0, sz);
    }
};