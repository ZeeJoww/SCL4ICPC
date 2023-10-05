#include <iostream>
#include <complex>
#include <cmath>

using Complex = complex<double>;

const double pi = acos(-1.0);

inline void dft(Complex a[], int len, int f) {
    for (int i = 0, k = 0; i < len; ++i) {
        if (i < k) std::swap(a[i], a[k]);
        for (int j = len >> 1; (k ^= j) < j; j >>= 1);
    }
    for (int h = 1; h < len; h *= 2) {
        Complex wn(cos(pi / h), f * sin(pi / h));
        for (int L = 0; L < len; L += h * 2) {
            Complex t(1.0, 0.0);
            for (int k = L; k < L + h; k++, t *= wn) {
                Complex t1 = a[k], t2 = t * a[k + h];
                a[k] = t1 + t2, a[k + h] = t1 - t2;
            }
        }
    }
    if (f == -1) {
        for (int i = 0; i < len; ++i) {
            a[i] /= len;
        }
    }
}

