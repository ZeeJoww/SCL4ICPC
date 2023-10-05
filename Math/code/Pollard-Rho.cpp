#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;

int64 add(int64 a, int64 b, int64 p) {
    a += b;
    return a >= p ? a - p : a;
}
int64 sub(int64 a, int64 b, int64 p) {
    a -= b;
    return a < 0 ? a + p : a;
}
int64 mul(int64 a, int64 b, int64 p) {
    int64 r = (int128) a * b % p;
    return r - p * int(r >= p) + p * int(r < 0);
}
int64 mod_pow(int64 a, int64 b, int64 p) {
    int64 res(1);
    for (; b; b /= 2, a = mul(a, a, p)) {
        if (b & 1) {
            res = mul(res, a, p);
        }
    }
    return res;
}

constexpr int64 base[] = 
    {2, 3, 5, 7, 11, 13, 17, 19, 23}; // < 3e18 (3825123056546413051) 
    // {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; // < 2^64 
    // {2, 325, 9375, 28178, 450775, 9780504, 1795265022}; // < 2^64 

// Miller Rabin
bool is_prime(int64 n) {
    if (n <= 1) return false;
    for (int64 p : base) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    int64 m = (n - 1) >> __builtin_ctz(n - 1);
    for (int64 p : base) {
        int64 t = m, a = mod_pow(p, m, n);
        while (t != n - 1 && a != 1 && a != n - 1) {
            a = mul(a, a, n);
            t *= 2;
        }
        if (a != n - 1 && t % 2 == 0) return false;
    }
    return true;
}

int64 get_factor(int64 n) {
    for (int64 p : base) {
        if (n % p == 0) return p;
    }
    auto f = [&](int64 x) { return add(mul(x, x, n), 1, n); };
    int64 x = 0, y = 0, tot = 0, p = 1, q, g;
    for (int64 i = 0; (i & 0xff) || (g = std::gcd(p, n)) == 1; i++, x = f(x), y = f(f(y))) {
        if (x == y) x = tot++, y = f(x);
        q = mul(p, sub(x, y, n), n);
        if (q) p = q;
    }
    return g;
}

std::vector<int64> factorization(int64 n) {
    if (n == 1) return {};
    if (is_prime(n)) return {n};
    int64 d = get_factor(n);
    auto v1 = factorization(d), v2 = factorization(n / d);
    auto i1 = v1.begin(), i2 = v2.begin();
    std::vector<int64> ans;
    while (i1 != v1.end() || i2 != v2.end()) {
        if (i1 == v1.end()) {
            ans.push_back(*i2++);
        } else if (i2 == v2.end()) {
            ans.push_back(*i1++);
        } else {
            if (*i1 < *i2) {
                ans.push_back(*i1++);
            } else {
                ans.push_back(*i2++);
            }
        }
    }
    return ans;
}

