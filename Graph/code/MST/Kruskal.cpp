#include <iostream>
#include <algorithm>
#include <vector>

const static int maxn = 110, inf = 0x3f3f3f3f;
int pa[maxn];

int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

bool cmp(Edge a, Edge b) { return a.w < b.w; }

int solve(int n, std::vector<Edge> edges) {
    int m = (int) edges.size();
    for (int i = 1; i <= n; ++i) pa[i] = i;
    sort(edges.begin(), edges.end(), cmp);
    edges.emplace_back(0, 0, inf);
    bool unic = true;
    int sum = 0, tail = -1, avail = 0, used = 0, cnt = n - 1;
    for (int i = 0; i < m; ++i) {
        if (i > tail) {
            if (avail != used) unic = false;
            avail = used = 0;
            do { ++tail; } while (edges[tail].w == edges[tail + 1].w);
            for (int j = i; j <= tail; ++j) {
                if (find(edges[j].u) != find(edges[j].v)) ++avail;
            }
        }
        if (find(edges[i].u) == find(edges[i].v)) continue;
        sum += edges[i].w;
        ++used, --cnt;
        pa[pa[edges[i].u]] = pa[edges[i].v];
    }
    if (avail != used) unic = false;
    if (cnt > 0) return -1; // no MST exists 
    else if (!unic) return -2; // multiple MSTs exist
    else return sum; // unique MST exists 
}
