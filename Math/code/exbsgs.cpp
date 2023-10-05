// a^x = b (mod p) => min({x}); min(\emptyset) := -inf( < 0 )

int bsgs(int a, int p, int b) {
    // if (b == 1 % p) return 0;

    int T = __builtin_sqrt(p) + 1;
    int N = p / T + 1;
    int cur = b, c = 1;
    unordered_map<int, int> mp;
    for (int i = 0; i < T; ++i) {
        mp[cur] = i;
        cur = 1LL * cur * a % p;
        c = 1LL * c * a % p;
    }

    for (int i = 1, k = c; i <= N; ++i, k = 1LL * k * c % p) 
        if (mp.count(k))
            return i * T - mp[k];

    return -100;
}

int exbsgs(int a, int p, int b) {
    int d = __gcd(a, p);

    if (b == 1 % p) 
        return 0;
    if (d == 1) 
        return bsgs(a, p, b);
    if (b % d != 0) 
        return -100;

    p /= d, b /= d;
    int invc, y;
    exgcd(a / d, p, invc, y);
    b = (1LL * b * invc % p + p) % p;

    return exbsgs(a, p, b) + 1;
}
