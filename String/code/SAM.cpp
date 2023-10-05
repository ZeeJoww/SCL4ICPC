#include <iostream>

constexpr int N = 1'000'000 + 10;
constexpr int CHARSET = 26;

struct sam_node {
    int len, pa, size;
    int next[CHARSET];
    sam_node(int l = 0, int p = 0, int s = 1) : len(l), pa(p), size(s), next{} {}
} sam[N * 2];

int tot, last;
void sam_init() {
    tot = 0;
    sam[last = ++ tot] = sam_node(0, 0, 0);
}

void extend(int c) {
    int cur = ++ tot;
    sam[cur] = sam_node(sam[last].len + 1);

    int p = last;
    while (p and not sam[p].next[c]) {
        sam[p].next[c] = cur;
        p = sam[p].pa;
    }

    if (p == 0) {
        sam[cur].pa = 1;
    } else {
        int q = sam[p].next[c];
        if (sam[p].len + 1 == sam[q].len) {
            sam[cur].pa = q;
        } else {
            int clone = ++ tot;
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1;
            sam[clone].size = 0;
            while (p and sam[p].next[c] == q) {
                sam[p].next[c] = clone;
                p = sam[p].pa;
            }
            sam[q].pa = sam[cur].pa = clone;
        }
    }
    last = cur;
}

int count[N], rank[N * 2];
int main() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    sam_init();
    for (char c : s) { 
        extend(c - 'a'); 
    }

    for (int i = 1; i <= tot; i++) {
        count[sam[i].len] ++;
    }
    for (int i = 1; i <= n; i++) {
        count[i] += count[i - 1];
    }
    for (int i = 1; i <= tot; i++) {
        rank[count[sam[i].len] --] = i;
    }

    long long ans = 0;
    for (int i = tot; i >= 1; i--) {
        int x = rank[i], p = sam[x].pa;
        if (p) sam[p].size += sam[x].size;
        if (sam[x].size > 1) {
            ans = std::max(ans, 1LL * sam[x].size * sam[x].len);
        }
    } 

    // S 的所有出现次数不为 1 的子串的出现次数乘上该子串长度的最大值
    std::cout << ans << '\n'; 

    return 0;
}
