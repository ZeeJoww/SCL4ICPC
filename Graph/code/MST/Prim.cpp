#include <iostream>
#include <vector>
#include <queue>
using PII = std::pair<int, int>;

const static int N = 100010;
bool in_S[N];
std::vector<PII> edge[N];

int prim(int n) {
    std::fill(in_S + 1, in_S + 1 + n, false);
    std::priority_queue<PII, std::vector<PII>, std::greater<PII> > pque;
    pque.emplace(0, 1);
    int cnt = n, ans = 0;
    while (!pque.empty()) {
        int w = pque.top().first;
        int u = pque.top().second;
        pque.pop();
        if (in_S[u]) continue;
        in_S[u] = true;
        ans += w;
        if (0 == (-- cnt)) return ans;
        for (auto p : edge[u]) {
            int v = p.first, c = p.second;
            if (!in_S[v]) pque.emplace(c, v);
        }
    }
    return -1;
}
