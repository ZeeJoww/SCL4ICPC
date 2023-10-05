#include <iostream>
#include <vector>

std::vector<int> edge[N], rEdge[N];
std::vector<int> scc_nodes[N];
int scc[N], scc_count;

bool visited[N];
int stack[N], top;

void dfs(int node) {
    visited[node] = true;
    for (int next : edge[node]) {
        if (visited[next]) continue;
        dfs(next);
    }
    stack[++top] = node;
}

void rDfs(int node, int scc_num) {
    visited[node] = true;
    for (int next : rEdge[node]) {
        if (visited[next]) continue;
        rDfs(next, scc_num);
    }
    scc_nodes[scc_num].push_back(node);
    scc[node] = scc_num;
}

void kosaraju(int n) {
    ::top = 0;
    ::scc_count = 0;
    std::fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i);
    }

    std::fill(visited, visited + n + 1, false);
    while (top) {
        int node = stack[top --];
        if (!visited[node]) rDfs(node, ++scc_count);
    }
}

void clear(int n) {
    for (int i = 1; i <= n; i++) {
        edge[i].clear();
        rEdge[i].clear();
    }
    for (int i = 1; i <= scc_count; i++) {
        scc_nodes[i].clear();
    }
}

