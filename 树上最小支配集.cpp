// https://www.luogu.com.cn/problem/P2458

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n, m;
int costs[1510];
struct edge{
    int to, nxt;
};
int heads[1510];
edge edges[1510];
int ins[1510];
int cnt = 1;

/*
a: security on the node
b: security on its father
c: security on its son
*/

tuple<int, int, int> dfs(int u) {
    if (heads[u] == 0) {
        return {costs[u], 0, INF};
    }
    int a = costs[u], b = 0, c = 0;
    int c_cnt = INF; // min cost to make sure at least one a if cur node is c
    for (int i = heads[u]; i != 0; i = edges[i].nxt) {
        auto [x, y, z] = dfs(edges[i].to);
        a += min({x, y, z});
        b += min(x, z);
        c += min(x, z);
        // 如果当前节点是被儿子监控，则儿子的属性可以是儿子上有监控，或者儿子节点被儿子的儿子节点监控
        // 但确保必须当前节点的某个儿子节点上有监控。所以选择那个从被监控到有监控代价最小的儿子
        c_cnt = min(c_cnt, x - z);
    }
    // 如果某个儿子本身有监控的花费比被监控的花费小，则已经选择过，所以加0，此时c_cnt < 0
    c += max(0, c_cnt);
    return {a, b, c};
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int j, k, m;
        cin >> j >> k >> m;
        costs[j] = k;
        for (int ii = 0; ii < m; ++ii) {
            edge e;
            cin >> e.to;
            e.nxt = heads[j];
            heads[j] = cnt;
            edges[cnt++] = e;
            ++ins[e.to];
        }
    }

    for (int i = 1; i < n + 1; ++i) {
        if (ins[i] == 0) {
            auto [a, b, c] = dfs(i);
            cout << min(a, c) << endl;
            return 0;
        }
    }
}