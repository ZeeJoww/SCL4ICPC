#include <iostream>

constexpr int N = 2'000'000 + 10;
constexpr int CHARSET = 26;

struct pam_node {
    int len, fail, dep;
    int next[CHARSET];
};

struct pam {
    pam_node tr[N];
    int root[2], n, tot, last;
    char s[N] = "$";

    pam() : root{0, 1}, n(0), tot(1), last(0), s("$") {
        tr[root[0]].len = 0;
        tr[root[1]].len = -1;
        tr[root[0]].fail = root[1];
    }
    
    int get_fail(int x) {
        while (s[n - tr[x].len - 1] != s[n]) {
            x = tr[x].fail;
        }
        return x;
    }

    void insert(int c) {
        s[++n] = 'a' + c;
        int p = get_fail(last);
        if (not tr[p].next[c]) {
            int x = ++ tot;
            tr[x].len = tr[p].len + 2;
            tr[x].fail = tr[get_fail(tr[p].fail)].next[c];
            tr[x].dep = tr[tr[x].fail].dep + 1;
            tr[p].next[c] = x;
        }
        last = tr[p].next[c];
    }
} p;

int main() {
    std::string s;
    std::cin >> s;
    for (char c : s) {
        p.insert(c - 'a');
    }
    return 0;
}

