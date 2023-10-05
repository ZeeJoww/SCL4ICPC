// n = \sum (d : n % d == 0) phi(d) 
int solve(int n, int m) {
    int res = 0; // muSum is the presum of mu
    for (int i = 1, j; i <= std::min(n, m); i = j + 1) {
        j = std::min(n / (n / i), m / (m / i));
        res += (muSum[j] - muSum[i - 1]) * (n / i) * (m / i);
    }
    return res;
}
int query(int a, int b, int c, int d, int k) {
    --a, --c;
    return + solve(b / k, d / k) - solve(b / k, c / k)
           - solve(a / k, d / k) + solve(a / k, c / k);
}
