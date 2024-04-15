struct segtree {
    vector<ll> val;
    ll NE = 0;
    ll sz = 1;

    void init(ll n) {
        while (sz < n)
            sz *= 2;
        val.assign(2 * sz, NE);
    }
    
    ll node(int v) {
        ll ret = 0;
        if (v > 0) {
            ret = v;
        }
        return ret;
    }
    ll merge(ll a, ll b){
        return a+b;
    }
    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            val[x] = node(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            set(i, v, x * 2 + 1, lx, m);
        } else
            set(i, v, x * 2 + 2, m, rx);
        val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, sz);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (rx <= l || lx >= r)
            return NE;
        if (lx >= l && rx <= r)
            return val[x];
        int m = (lx + rx) / 2;
        ll ret = merge(calc(l, r, 2 * x + 1, lx, m), calc(l, r, 2 * x + 2, m, rx));
        return ret;
    }

    ll calc(int l, int r) {
        return calc(l, r, 0, 0, sz);
    }
};
