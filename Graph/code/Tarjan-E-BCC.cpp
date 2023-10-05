int e[M], e_cnt;
std::vector<int> edge[N];
void add_edge(int u, int v) {
    int i = e_cnt ++;
    edge[u].push_back(i);
    e[i] = v;
}
int dfn[N], low[N], now, ebcc_cnt;
std::vector<int> ebcc[N], sta;
// start point -> from == -1 
void tarjan(int u, int from) {
    dfn[u] = low[u] = ++now;
    sta.push_back(u);
    int child = 0;
    for (int j : edge[u]) {
        if ((j ^ from) == 1) continue;
        child ++;
        int v = e[j];
        if (dfn[v] > 0) {
            low[u] = std::min(low[u], dfn[v]);
        } else {
            tarjan(v, j);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                int idx = ebcc_cnt ++, x;
                do {
                    x = sta.back();
                    sta.pop_back();
                    ebcc[idx].push_back(x);
                } while (x != v);
                ebcc[idx].push_back(u);
            }
        }
    }
    if (from == -1 && child == 0) {
        ebcc[ebcc_cnt ++].push_back(u);
    }
}

