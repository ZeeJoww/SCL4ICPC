#include <iostream>

template <typename T>
T exgcd(T a, T b, T &x, T &y) {
    // a * x + b * y == return_value
    if (b == 0) {
        x = 1; y = 0;
        return a;
    } else {
        T t = exgcd(b, a % b, y, x);
        // b * y + (a - (a / b) * b) * x == t
        // a * x + b * (y - (a / b) * x) == t
        y -= (a / b) * x;
        return t;
    }
}

template <typename T>
void get_min_pos(T a, T b, T &x, T &y) {
    T target = x % b;
    if (target <= 0) target += b; // making target POSITIVE
    y -= (target - x) / b * a;
    x = target;
}

int main() {
    long long a, b, c;
    std::cin >> a >> b >> c;
    long long x, y;
    long long g = exgcd(a, b, x, y);
    if (c % g != 0) {
        puts("-1\n");
    } else {
        a /= g; b /= g; c /= g;
        x *= c; y *= c;

        get_min_pos(a, b, x, y);
        long long o1 = x, o4 = y;
        get_min_pos(b, a, y, x);
        long long o2 = y, o3 = x;

        if (x <= 0) {
            // no pos sol: min pos x, min pos y 
            printf("%lld %lld\n", o1, o2);
        } else {
            // all pos: pos sol count, min x, min y, max x, max y
            long long o0 = (o3 - o1) / b + 1;
            printf("%lld %lld %lld, %lld, %lld\n", o0, o1, o2, o3, o4);
        }
    }
}

