#include <algorithm>
#include <iostream>

constexpr int N = 2'000'000 + 5;
constexpr int CHARSET = 26;

struct suffix_automaton {
    int tot, link[N], maxlen[N], trans[N][CHARSET];
    suffix_automaton() { tot = 1; }
    int insert(int ch, int last) {
        if (trans[last][ch]) {
            int p = last, x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]){
                return x;
            } else {
                int y = ++ tot;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < CHARSET; i++) {
                    trans[y][i] = trans[x][i];
                }
                while (p and trans[p][ch] == x) {
                    trans[p][ch] = y;
                    p = link[p];
                }
                link[y] = link[x];
                link[x] = y;
                return y;
            }
        }
        int z = ++ tot, p = last;
        maxlen[z] = maxlen[last] + 1;
        while (p and not trans[p][ch]) {
            trans[p][ch] = z;
            p = link[p];
        }
        if (!p) {
            link[z] = 1;
        } else {
            int x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) {
                link[z] = x;
            } else {
                int y = ++ tot;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < CHARSET; i++) {
                    trans[y][i] = trans[x][i];
                }
                while (p and trans[p][ch] == x) {
                    trans[p][ch] = y;
                    p = link[p];
                }
                link[y] = link[x];
                link[z] = link[x] = y;
            }
        }
        return z;
    }
    long long sakura() {
        // 本质不同的子串个数. 
        long long ans = 0;
        for (int i = 2; i <= tot; i++) {
            ans += maxlen[i] - maxlen[link[i]];
        }
        return ans;
    }
} sam;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        int last = 1;
        for (char c : s) {
            last = sam.insert(c - 'a', last);
        }
    }
    std::cout << sam.sakura() << '\n';
    std::cout << sam.tot << '\n';
}

