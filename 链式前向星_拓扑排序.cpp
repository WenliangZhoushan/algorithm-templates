// https://www.luogu.com.cn/problem/P4017

#include <bits/stdc++.h>
using namespace std;

const int mod = 80112002;

int n, m;
struct edge {
    int from, nxt;
};
int heads[500010];
edge edges[500010];
int ins[500010];
int outs[500010];
int f[500010];
int cnt = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        edge e;
        e.from = u;
        e.nxt = heads[v];
        heads[v] = cnt;
        edges[cnt++] = e;
        ++outs[u];
        ++ins[v];
    }

    queue<int> q;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (outs[i] == 0) {
            f[i] = 1;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = heads[v]; i != 0; i = edges[i].nxt) {
            int u = edges[i].from;
            f[u] = (f[u] + f[v]) % mod;
            if (--outs[u] == 0) {
                q.push(u);
            }
        }
    }

    for (int u = 1; u <= n; ++u) {
        if (ins[u] == 0) {
            ans = (ans + f[u]) % mod;
        }
    }

    cout << ans << '\n';
}