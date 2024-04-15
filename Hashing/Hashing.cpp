pair<ll, ll> p[N], ip[N];
const int mod1 = 1e9 + 7, mod2 = 2e9 + 11;
ll base1 = 139, base2 = 277;

ll power(ll a, ll b, ll m) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}

void cal_p() {
    p[0].fs = p[0].sc = ip[0].fs = ip[0].sc = 1;
    ll invp1 = power(base1, mod1 - 2, mod1);
    ll invp2 = power(base2, mod2 - 2, mod2);
    for (int i = 1; i < N; i++) {
        p[i].fs = (ll) p[i - 1].fs * base1 % mod1;
        p[i].sc = (ll) p[i - 1].sc * base2 % mod2;
        ip[i].fs = (ll) ip[i - 1].fs * invp1 % mod1;
        ip[i].sc = (ll) ip[i - 1].sc * invp2 % mod2;
    }
}

vector<pair<ll, ll>> build(string s) {
    int n = sz(s);
    vector<pair<ll, ll>> pref(n);
    pref = vector<pair<ll, ll>>(sz(s), {0, 0});
    for (int i = 0; i < n; i++) {
        pref[i].fs = (ll) s[i] * p[i].fs % mod1;
        if (i)pref[i].fs = (pref[i].fs + pref[i - 1].fs) % mod1;
        pref[i].sc = (ll) s[i] * p[i].sc % mod2;
        if (i)pref[i].sc = (pref[i].sc + pref[i - 1].sc) % mod2;
    }
    return pref;
}

pair<ll, ll> sub_hash(int i, int j, vector<pair<ll, ll>> &pref) {
//    assert(i <= j);
    pair<ll, ll> hs({0, 0});
    hs.fs = pref[j].fs;
    if (i)hs.fs = (hs.fs - pref[i - 1].fs + mod1) % mod1;
    hs.fs = (ll) hs.fs * ip[i].fs % mod1;
    hs.sc = pref[j].sc;
    if (i) hs.sc = (hs.sc - pref[i - 1].sc + mod2) % mod2;
    hs.sc = (ll) hs.sc * ip[i].sc % mod2;
    return hs;
}

bool palindrome(int l, int r, int n, vector<pair<ll, ll>> &pre, vector<pair<ll, ll>> &suf) {
    return sub_hash(l, r, pre) == sub_hash(n - r - 1, n - l - 1, suf);
}