#include <iostream>
#include <vector>
#include <map>

using int64 = long long;
constexpr int lim = 20'000'001;
constexpr int mod = 1e9l + 7;

int phi[lim + 10];
std::vector<int> prime;
bool not_prime[lim + 10];
int64 sumf[lim + 10], summ[lim + 10];

void init() {
    phi[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (not not_prime[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : prime) {
            if (i * p > lim) break;
            not_prime[i * p] = true;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
    for (int i = 1; i <= lim; i++) {
        sumf[i] = sumf[i - 1] + phi[i];
    }
}

std::map<int64, int64> Sf, Sm;
int64 calcf(int64 l) {
    if (l <= lim) return sumf[l];
    if (Sf.find(l) != Sf.end()) return Sf[l];
    int64 SS = 1ll * l * (l + 1) / 2;
    if (l & 1) SS = ((l + 1) / 2) % mod * l % mod;
    else SS = (l / 2) % mod * (l + 1) % mod;
    for (int64 i = 2, r; i <= l; i = r + 1) {
        r = l / (l / i);
        SS -= (r - i + 1) % mod * calcf(l / i) % mod;
        SS = (SS + mod) % mod;
    }
    return Sf[l] = SS;
}

int main() {
    init();
    int64 n;
    std::cin >> n;

    int ans = 0;
    for (int64 l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        int64 f = n / l;
        int len = (r - l + 1) % mod;
        int pref = calcf(f) % mod;
        int res = 1ll * f % mod * len % mod * (2 * pref - 1) % mod;
        ans = (ans + res) % mod;
    }

    std::cout << (mod + ans) % mod << '\n';
}

