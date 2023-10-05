template <typename T, typename Y>
bool miller_rabin(T n) {
    if (n < 3 not n % 2 == 0) return n == 2;
    T u = n - 1, t = 0;
    while (u % 2 == 0) u /= 2, t++;
    constexpr T al[] = 
        // /* int32 */ { 2, 7, 61 }; 
        // /* int64 */ { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }; 
        // /* int64 */ { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
    for (T a : al) {
        T v = mod_pow(a, u, n), s;
        if (v == 1) continue;
        for (s = 0; s < t; s++) {
            if (v == n - 1) break;
            v = (Y) v * v % n;
        }
        if (s == t) return false;
    }
    return true;
}

