// https://www.luogu.com.cn/problem/P1757
// 一共n个物品，背包容量为m, 一共k组物品，组内物品互斥（对任意组，最多只能挑1个）
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
// 从[0 ... i]组里选k个获得的最大收益
int f[110][1010];

int main() {
    cin >> m >> n;
    unordered_map<int, vector<pair<int, int>>> g;
    int mx = -1;

    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[c].emplace_back(a, b);
        mx = max(mx, c);
    }

    for (int i = 0; i < mx + 1; ++i) {
        // 不选这组，记得放前面，如果i不存在这行不执行状态丢失了
        for (int j = 0; j < m + 1; ++j) {
            f[i + 1][j] = f[i][j];
        }
        if (!g.contains(i)) {continue;}
        // 选这组，枚举组内物品
        for (int j = 0; j < m + 1; ++j) {
            for (auto& [c, v] : g[i]) {
                if (c > j) {
                    continue;
                }
                // {之前可能的答案，不选，选}
                f[i + 1][j] = max({f[i + 1][j], f[i][j], f[i][j - c] + v});
            }
        }
    }

    cout << f[mx + 1][m] << endl;
}