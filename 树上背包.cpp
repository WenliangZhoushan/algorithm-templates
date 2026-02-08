// https://www.luogu.com.cn/problem/P2014

// ------------- 树上背包 利用dfn序倒序递推 O(N * K) ------------- //
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> g[310];
int scores[310];
int f[310][310]; // dfn从0到n + 1（0和n + 1都为虚拟节点），选k门课的最大收益
int dfn[310];
int cnt = 0; // 把0给虚拟头节点0，后面是正常的1 ... N
int dfn_size[310];

// 建立dfn序（先序遍历），dfn序->节点值
int build_dfn(int u) {
    dfn[cnt] = u;
    dfn_size[cnt] = 1;
    int i = cnt++;
    for (auto& v : g[u]) {
        dfn_size[i] += build_dfn(v);
    }
    return dfn_size[i];
}

int main() {
    // N个节点，M的背包容量
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    int k, s;
    for (int i = 1; i <= N; ++i) {
        cin >> k >> s;
        g[k].push_back(i);
        scores[i] = s;
    }

    build_dfn(0); // 0为虚拟头节点

    // f[i][k]定义：选dfn序[i ... N + 1]区间的节点，选恰好k个的最大收益。固定到N + 1
    // 倒序遍历dfn，正序遍历空间
    for (int i = N + 1; i > 0; --i) {
        // 如果不选，则底下子树都不能选，跳到右侧第一棵合法子树父节点的dfn
        int j = i + dfn_size[i];
        for (int k = 1; k <= M; ++k) {
            int ans1 = f[j][k];
            int ans2 = f[i + 1][k - 1] + scores[dfn[i]];
            f[i][k] = max(ans1, ans2);
        }
    }

    cout << f[1][M] << '\n';
}

// ------------- 树上背包 分组背包模板 O(N ^ 2 * K) ------------- //
// #include <bits/stdc++.h>
// using namespace std;

// int N, M;
// int memo[310][310][310];
// vector<int> g[310];
// int scores[310];

// // 当前来到i号节点为头的子树
// // 只在i号节点、及其i号节点下方的前j棵子树上挑选节点
// // 一共挑选k个节点，并且保证挑选的节点连成一片
// // 返回最大的累加和
// int dfs(int i, int j, int k) {
//     if (k == 0) {
//         return 0;
//     }
//     if (j == 0 || k == 1) {
//         return scores[i];
//     }
//     if (memo[i][j][k] != -1) {
//         return memo[i][j][k];
//     }
//     int& ans = memo[i][j][k];
//     ans = dfs(i, j - 1, k); // 不选第j个子树
//     int v = g[i][j - 1]; // v是第j个子树的头节点
//     // 为什么不枚举所有子节点v呢？
//     // 因为这是背包问题，背包问题对于某个物品，只有选或者不选
//     for (int kk = 1; kk < k; ++kk) {
//         ans = max(ans, dfs(i, j - 1, k - kk) + dfs(v, g[v].size(), kk));
//     }
//     return ans;
// }

// int main() {
//     cin >> N >> M;
//     int k, s;
//     for (int i = 1; i < N + 1; ++i) {
//         cin >> k >> s;
//         g[k].push_back(i);
//         scores[i] = s;
//     }

//     memset(memo, -1, sizeof(memo));

//     // 应该选择M + 1门课，引入了一个收益为0的虚拟头节点
//     cout << dfs(0, g[0].size(), M + 1) << endl;
// }
