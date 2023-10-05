#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>

const int P = 998'244'353;
const int N = 1e6 + 10;

int inv[N];

__attribute__((constructor))
void init_inv() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) {
        inv[i] = P - 1ll * P / i * inv[P % i] % P;
    }
}

int add(int x, int y, int p = P) {
    x += y;
    if (x >= p) x -= p;
    if (x <  0) x += p;
    return x;
}

template <typename T>
int mod_pow(int a, T b, int p = P) {
    int res = 1;
    for (; b; b /= 2, a = 1ll * a * a % p) {
        if (b & 1) {
            res = 1ll * res * a % p;
        }
    }
    return res;
}

int inv_of(int a, int p = P) {
    if (a < N) {
        return inv[a];
    } else {
        return mod_pow(a, p - 2, p);
    }
}

const int primitiveRoot = 3;
std::vector<int> Roots { 0, 1 };

struct poly : public std::vector<int> {

    poly() : std::vector<int>() {}

    poly(int n) : std::vector<int>(n) {}

    poly(const std::vector<int> &a) : std::vector<int>(a) {}

    poly(const std::initializer_list<int> &a) : std::vector<int>(a) {}

    template<class InputIt, class = std::_RequireInputIter<InputIt>>
    poly(InputIt first, InputIt last) : std::vector<int>(first, last) {}

    poly shift(int k) const {
        if (k >= 0) {
            poly f(*this);
            f.insert(f.begin(), k, 0);
            return f;
        } else if (this->size() <= -k) {
            return poly{};
        } else {
            return poly(this->begin() + (-k), this->end());
        }
    }

    poly trunc(int k) const {
        poly f(*this);
        f.resize(k);
        return f;
    }

    poly dft(int len) const {
        while (len > Roots.size()) {
            int h = Roots.size();
            int wn = mod_pow(primitiveRoot, (P - 1) / (2 * h));
            for (int i = 0, v = 1; i < h; i++, v = 1ll * v * wn % P) {
                Roots.push_back(v);
            }
        }
        poly a = this->trunc(len);
        for (int i = 0, k = 0; i < len; i++) {
            if (i < k) std::swap(a[i], a[k]);
            for (int j = len >> 1; (k ^= j) < j; j >>= 1) {}
        }
        for (int h = 1; h < len; h *= 2) {
            for (int L = 0; L < len; L += 2 * h) {
                for (int t = L; t < L + h; t++) {
                    int x = a[t], y = 1ll * a[t + h] * Roots[h + t - L] % P;
                    a[t] = add(x, y);
                    a[t + h] = add(x, -y);
                }
            }
        }
        return a;
    }

    poly idft(int len) const {
        poly a = this->dft(len);
        std::reverse(a.begin() + 1, a.end());
        // int invlen = inv_of(len);
        int invlen = P - (P - 1) / len;
        for (int i = 0; i < len; i++) {
            a[i] = 1ll * a[i] * invlen % P;
        }
        return a;
    }

    poly mul(const poly &g0) const {
        int len = 1, n = this->size() + g0.size() - 2;
        while (len <= n) {
            len *= 2;
        }
        poly f = this->dft(len);
        poly g = g0.dft(len);
        for (int i = 0; i < len; i++) {
            f[i] = 1ll * f[i] * g[i] % P;
        }
        return f.idft(len).trunc(n + 1);
    }

    friend poly operator* (poly f, int x) {
        for (int &val : f) {
            val = 1ll * val * x % P;
        }
        return f;
    }

    friend poly operator* (int x, const poly &f) {
        return f * x;
    }

    friend poly operator* (const poly &f, const poly &g) {
        return f.mul(g);
    }

    friend poly operator+ (const poly &f, const poly& g) {
        poly h(std::max(f.size(), g.size()));
        for (int i = 0; i < f.size(); i++) {
            h[i] = add(h[i], +f[i]);
        }
        for (int i = 0; i < g.size(); i++) {
            h[i] = add(h[i], +g[i]);
        }
        return h;
    }

    friend poly operator- (const poly &f, const poly& g) {
        poly h(std::max(f.size(), g.size()));
        for (int i = 0; i < f.size(); i++) {
            h[i] = add(h[i], +f[i]);
        }
        for (int i = 0; i < g.size(); i++) {
            h[i] = add(h[i], -g[i]);
        }
        return h;
    }

    poly derive() const {
        poly f(this->size() - 1);
        for (int i = 1; i < this->size(); i++) {
            f[i - 1] = 1ll * i * (*this)[i] % P;
        }
        return f;
    }

    poly integral() {
        poly f(this->size() + 1);
        for (int i = 1; i < f.size(); i++) {
            f[i] = 1ll * (*this)[i - 1] * inv_of(i) % P;
        }
        return f;
    }

    poly inv(int m) const {
        poly f {inv_of((*this)[0])};
        int k = 1;
        while (k < m) {
            k *= 2;
            f = (f * (poly{2} - f * this->trunc(k))).trunc(k);
        }
        return f;
    }

    // [q, r] = f / g  <==>  f = q · g + r
    std::pair<poly, poly> operator/ (const poly &g) const {
        int n = this->size() - 1, m = g.size() - 1;
        poly fr(this->rbegin(), this->rend());
        poly gr(g.rbegin(), g.rend());
        poly qr = (fr * gr.inv(n - m + 1)).trunc(n - m + 1);
        poly q(qr.rbegin(), qr.rend());
        poly r = ((*this) - g * q).trunc(m);
        return std::make_pair(q, r);
    }

    poly log(int m) const {
        return (this->derive() * this->inv(m)).integral().trunc(m);
    }

    poly exp(int m) const {
        poly f{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            f = (f * (poly{1} - f.log(k) + this->trunc(k))).trunc(k);
        }
        return f.trunc(m);
    }

    poly pow(int k, int m) const {
        int i = 0;
        while (i < this->size() and (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() or 1ll * i * k >= m) {
            return poly(m);
        }
        int val = (*this)[i];
        auto f = this->shift(-i) * inv_of(val);
        return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * mod_pow(val, k);
    }

    poly pow_bigint(const std::string &k, int m) const {
        int i = 0;
        while (i < this->size() and (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() or (i > 0 and (k.length() >= 8 or 1ll * i * std::stoi(k) >= m))) {
            return poly(m);
        }
        int k1 = 0, k2 = 0;
        for (char c : k) {
            k1 = (10ll * k1 + c - '0') % P;
            k2 = (10ll * k2 + c - '0') % (P - 1);
        }
        int val = (*this)[i];
        return ((this->shift(-i) * inv_of(val)).log(m - i * k1) * k1)
            .exp(m - i * k1).shift(i * k1) * mod_pow(val, k2);
    }

    poly sqrt(int m) const {
        poly f{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            f = (f + (trunc(k) * f.inv(k)).trunc(k)) * inv_of(2);
        }
        return f.trunc(m);
    }

    poly mulT(const poly &g) const {
        if (g.size() == 0) {
            return poly{};
        }
        int n = g.size();
        return ((*this) * poly(g.rbegin(), g.rend())).shift(-(n - 1));
    }

    std::vector<int> eval(std::vector<int> x) const {
        if (this->size() == 0) {
            return std::vector<int>(x.size(), 0);
        }
        const int n = std::max(x.size(), this->size());
        std::vector<poly> q(4 * n);
        std::vector<int> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const poly &)> 
        work = [&](int p, int l, int r, const poly &num) -> void {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).trunc(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).trunc(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};

