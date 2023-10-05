#include <unordered_map>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

using int64 = long long;

int64 mod(int64 x, int64 p) {
    if (x >= p) x -= p;
    if (x <  0) x += p;
    return x;
}

int64 mod_add(int64 a, int64 b, int64 p) {
    return mod(a + b, p);
}

int64 mod_mul(int64 a, int64 b, int64 p) {
    return mod((__int128_t) a * b % p, p); // 64-bit only
    int64 res = 0;
    for (a %= p, b %= p; b; b /= 2, a = mod_add(a, a, p)) {
        if (b & 1) {
            res = mod_add(res, a, p);
        }
    }
    return mod(res, p);
}

int64 mod_pow(int64 a, int64 b, int64 p) {
    int64 res = 1;
    for (a %= p; b; b /= 2, a = mod_mul(a, a, p)) {
        if (b & 1) {
            res = mod_mul(res, a, p);
        }
    }
    return res;
}

std::vector<int64> get_prime_factor(int64 p) {
    std::vector<int64> res;
    for (int64 k = 2; k * k <= p; k++) {
        if (p % k == 0) {
            res.push_back(k);
            while (p % k == 0) {
                p /= k;
            }
        }
    }
    if (p > 1) res.push_back(p);
    return res;
}

int64 find_primitive_root(int64 p) {
    auto pf = get_prime_factor(p - 1);
    for (int i = 1; i < p; i++) {
        bool valid = true;
        for (int64 f : pf) {
            if (mod_pow(i, (p - 1) / f, p) == 1) {
                valid = false;
                break;
            }
        }
        if (valid) return i;
    }
    assert(false);
}

template <typename T>
T exgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    } else {
        T d = exgcd(b, a % b, y, x);
        // (a - (a / b) * b)x + by = d
        // ax + b(y - (a / b)x) = d
        y -= a / b * x;
        return d;
    }
}

//: accepted when T <= 200, p < 1e12, p is prime
int main() {
    int T;
    int64 p;
    std::cin >> T >> p;
    // w * T = p / w ~> w*w = p/T
    int64 w = std::max((int64) std::sqrt(p / 25), 1ll);
    int64 g = find_primitive_root(p);
    int64 invg = mod_pow(g, p - 2, p);
    std::unordered_map<int64, int64> umap;
    umap.reserve(50'000'000);
    for (int64 i = 0, val = 1, mul = mod_pow(g, w, p); i < p - 1;
            i += w, val = mod_mul(val, mul, p)) {
        umap[val] = i;
    }
    auto dlog = [&] (int64 num) -> int64 {
        for (int64 j = 0; j < w; j++, num = mod_mul(num, invg, p)) {
            // x * pow(g, j) == num -> x = num / pow(g, j)
            if (umap.count(num)) {
                return umap[num] + j;
            }
        }
        assert(false);
    };
    for (int cs = 1; cs <= T; cs ++) {
        // find minimal non-negative `x` s.t. `a^x \equiv b \pmod p`
        int64 a, b;
        std::cin >> a >> b;
        int64 ap = dlog(a), bp = dlog(b);
        // ap * x == bp (mod p - 1)
        int64 mp = p - 1, x, y;
        int64 d = exgcd(ap, mp, x, y);
        if (bp % d != 0) {
            std::cout << "-1" << std::endl;
        } else {
            ap /= d;
            mp /= d;
            bp /= d;
            x = mod_mul(x, bp, mp);
            std::cout << x << std::endl;
        }
    }
}
