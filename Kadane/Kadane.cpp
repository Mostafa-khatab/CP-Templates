int n;
    cin >> n;
    ll mx = INT_MIN, sum = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        sum += x;
        mx = max(mx, sum);
        sum = max(sum, 0LL);
    }
    cout << mx << endl;