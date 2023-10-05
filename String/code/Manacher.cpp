#include <iostream>
#include <cstring>

const int N = 2 * 1.1e7 + 233;
int p[N];

int main() {
    std::cin.tie(nullptr) -> sync_with_stdio(false);

    std::string s0;
    std::cin >> s0;

    std::string s = "$#";
    for (char c : s0) {
        s += c;
        s += '#';
    }
    s += '%';

    int n = s.size() - 1;

    int mid = 0, mr = 0, ans = 0;
    for (int i = 1; i < n; i++) {
        if (i <= mr) p[i] = std::min(p[2 * mid - i], mr - i + 1);
        else p[i] = 1;
        while (s[i - p[i]] == s[i + p[i]]) p[i] ++;
        if (i + p[i] > mr) mr = i + p[i] - 1, mid = i;
        ans = std::max(ans, p[i]);
    }
    std::cout << ans - 1 << '\n';

    return 0;
}
