const int inf = 1e8; // to modify

std::pair<int, std::vector<int>> shortest_cycle(const std::vector<std::vector<int>> &G, int r) {
    int n = G.size();
    std::vector<int> dist(n, inf * 2), p(n, -1), g(n);
    std::vector<bool> seen(n);
    dist[r] = 0;
    g[r] = r;
    for (int t = 0; t < n; t++) {
        int mn = inf * 2, pos = -1;
        for (int i = 0; i < n; i++) {
            if (!seen[i] and dist[i] < mn) {
                mn = dist[i];
                pos = i;
            }
        }
        assert(pos != -1);
        seen[pos] = true;
        for (int i = 0; i < n; i++) {
            if (dist[i] > dist[pos] + G[pos][i]) {
                dist[i] = dist[pos] + G[pos][i];
                p[i] = pos; // parent 
                g[i] = (pos == r ? i : g[pos]); // in which child of r 
            }
        }
    }
    int mn = 5 * inf;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] == j or p[j] == i) continue; // ensure r is not chosen
            if (g[i] == g[j]) continue;
            mn = std::min(mn, dist[i] + dist[j] + G[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] == j or p[j] == i) continue;
            if (g[i] == g[j]) continue;
            if (mn != dist[i] + dist[j] + G[i][j]) continue;
            std::vector<int> res;
            int a = i, b = j;
            while (a != r) {
                res.push_back(a);
                a = p[a];
            }
            res.push_back(a);
            std::reverse(res.begin(), res.end());
            while (b != r) {
                res.push_back(b);
                b = p[b];
            }
            return {mn, res};
        }
    }
    assert(false);
}

