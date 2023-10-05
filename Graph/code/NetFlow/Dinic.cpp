#include <iostream>
#include <vector>
#include <queue>

const int INF = 1e9;

template <typename T>
struct Dinic {
    struct Edge {
        int from, to;
        T cap, flow;
        Edge(int u, int v, T c, T f) : from(u), to(v), cap(c), flow(f) {}
    };

    int n, m, s, t;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> G;
    std::vector<int> dep, cur;

    Dinic(int _n) : n(_n), m(0), G(n), dep(n), cur(n) {}

    int add_edge(int u, int v, T c) {
        edges.emplace_back(u, v, c, 0);
        edges.emplace_back(v, u, 0, 0);
        m = edges.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
        return m - 2;
    }

    bool bfs() {
        dep.assign(n, 0);
        std::queue<int> que;
        que.push(s);
        dep[s] = 1;
        while (not que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = 0; i < (int) G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (not dep[e.to] and e.cap > e.flow) {
                    dep[e.to] = dep[x] + 1;
                    que.push(e.to);
                }
            }
        }
        return dep[t] > 0;
    }

    T dfs(int x, T a) {
        if (x == t or a == 0) return a;
        T res = 0, f;
        for (int &i = cur[x]; i < (int) G[x].size(); i++) {
            Edge &e = edges[G[x][i]];
            if (dep[x] + 1 == dep[e.to] 
            and (f = dfs(e.to, std::min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                res += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return res;
    }

    T max_flow(int s, int t, T lim = INF) {
        this->s = s, this->t = t;
        T flow = 0;
        while (bfs() and flow < lim) {
            cur.assign(n, 0);
            flow += dfs(s, INF);
        }
        return flow;
    }
};

