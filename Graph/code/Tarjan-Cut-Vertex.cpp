std::vector<int> edge[N];
int low[N], dfn[N], now, start, child;
bool is_cut[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++ now;
    for (int v : edge[u]) {
        if (dfn[v] != 0) {
            low[u] = std::min(low[u], dfn[v]);
        } else {
            if (u == start) child ++;
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
            if (u != start && low[v] >= dfn[u]) is_cut[u] = true;
        }
    }
    if (u == start && child >= 2) is_cut[u] = true;
}

