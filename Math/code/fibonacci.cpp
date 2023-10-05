// fast doubling method
template <typename T>
std::pair<T, T> fib(int n) {
    if (n == 0) return { 0, 1 };
    auto [c0, d0] = fib<T>(n >> 1);
    T c = c0 * (2 * d0 - c0);
    T d = c0 * c0 + d0 * d0;
    if (n & 1) return { d, c + d };
    else return { c, d };
}

