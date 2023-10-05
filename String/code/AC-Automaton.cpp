#include <iostream>
#include <queue>

const int maxnode = 1e6 + 7;
const int charset = 26;
const char base = 'a';
int ac[maxnode][charset], tot, acc[maxnode], fail[maxnode];
inline int getid(int ch) { return int(ch - base); }

void insert(const std::string &p) {
    int u = 0;
    for (const auto &ch : p) {
        int id = getid(ch);
        if (!ac[u][id]) ac[u][id] = ++tot;
        u = ac[u][id];
    }
    ++acc[u];
}

// call getfail() after all `insert()` calls. 
void getfail() {
    std::queue<int> que;
    for (int i = 0; i < charset; ++i) {
        if (ac[0][i]) que.emplace(ac[0][i]);
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (int i = 0; i < charset; ++i) {
            if (ac[u][i]) {
                fail[ac[u][i]] = ac[fail[u]][i];
                que.emplace(ac[u][i]);
            } else {
                ac[u][i] = ac[fail[u]][i];
            }
        }
    }
}

int match(const std::string &t) {
    int u = 0, ans = 0;
    for (const auto &ch : t) {
        int id = getid(ch);
        u = ac[u][id];
        for (int v = u; v && -1 != acc[v]; v = fail[v]) {
            ans += acc[v];
            acc[v] = -1;
        }
    }
    return ans;
}

int main() {
    std::cin.tie(0) -> sync_with_stdio(false);
    int n; 
    std::cin >> n;
    while (n--) {
        std::string t; 
        std::cin >> t;
        insert(t);
    }
    getfail();
    std::string s;
    std::cin >> s;
    std::cout << match(s) << "\n";
    return 0;
}
