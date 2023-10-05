std::vector<int> z_func(const std::string &s) {
    int n = s.size();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 1; i < n; i++) {
        if (i < r and z[i - l] < r - i) {
            z[i] = z[i - l];
        } else {
            z[i] = std::max(0, r - i);
            while (z[i] + i < n and s[z[i]] == s[i + z[i]]) {
                z[i] ++;
            }
        }
        if (r < i + z[i]) {
            l = i; r = i + z[i];
        }
    }
    return z;
}
