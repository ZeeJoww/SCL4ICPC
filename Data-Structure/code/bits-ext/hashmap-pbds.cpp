using LL = long long;
using ULL = unsigned long long;
#include <bits/extc++.h>
// or : mt19937_64(chrono::steady_clock::now().time_since_epoch().count())
const int SEED = std::chrono::steady_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
    const ULL C = LL(4e18 * acos(0)) | 71;  // large odd number
    LL operator()(LL x) const { return __builtin_bswap64((x ^ SEED) * C); }
};
using HashMap = __gnu_pbds::gp_hash_table<LL, int, chash>;

ULL splitmix64(ULL x) { // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}
int SPLITMIX32(int z) {
    z += 0x9e3779b9;
    z = (z ^ (z >> 16)) * 0x85ebca6b;
    z = (z ^ (z >> 13)) * 0xc2b2ae35;
    return z ^ (z >> 16);
}
