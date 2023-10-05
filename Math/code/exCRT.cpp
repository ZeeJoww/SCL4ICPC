template <typename T> 
T exgcd(T a, T b, T& x, T& y) {
    // ax + by == g
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        // (a - (a / b) * b) x + by == g
        // ax + b(y + (a / b) x) == g
        T t = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return t;
    }
}

// [modulo, remainder] in num, T: int{B}, Y: int{2B} 
template <typename T, typename Y> 
T excrt(const std::vector<std::pair<T, T>> &num) {
    Y A = 1;
    T B = 0;
    for (auto [b, a] : num) {
        // t = Ax + B = ay + b
        // Ax - ay = b - B
        T c = b - B, x, y;
        T g = exgcd<T>(A, a, x, y);
        if (c % g != 0) return -1; // no solution. 
        x *= (c / g), y *= (c / g);
        B = (B + A * x) % (A * a / g);
        A *= a / g;
        if (B < 0) B += A;
    }
    return B;
}

