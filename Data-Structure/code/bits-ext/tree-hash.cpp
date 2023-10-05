// #include "hashmap-pbds.cpp"
void dfs(int u, int p) { // 有根 
    for (int v : edge[u]) if (v != p) dfs(v, u), H[u] += splitmix64(H[v] ^ SEED);
}
void sol(int u, int p) { // 无根 
    if (p != 0) H[u] = H[u] + splitmix64((G[p] - splitmix64(H[u] ^ SEED)) ^ SEED);
    for (int v : edge[u]) if (v != p) sol(v, u);
}
