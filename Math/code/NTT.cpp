const int P = 998244353;

void ntt(int a[], int len, int f) {
    for (int i = 0, k = 0; i < len; i++) {
        if (i < k) std::swap(a[i], a[k]);
        for (int j = len >> 1; (k ^= j) < j; j >>= 1) {}
    }
    for (int h = 1; h < len; h *= 2) {
        const int g = 3;
        int wn = mod_pow(g, (P - 1) / (2 * h));
        for (int L = 0; L < len; L += 2 * h) {
            for (int w = 1, k = L; k < L + h; k++, w = 1ll * w * wn % P) {
                int x = a[k], y = 1ll * a[k + h] * w % P;
                a[k] = x + y;
                a[k + h] = x - y;
                if (a[k] >= P) a[k] -= P;
                if (a[k + h] < 0) a[k + h] += P;
            }
        }
    }
    if (f == -1) {
        std::reverse(a + 1, a + len);
        for (int i = 0, val = inv_of(len); i < len; i++) {
            a[i] = 1ll * a[i] * val % P;
        }
    }
}
