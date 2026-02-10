// https://www.luogu.com.cn/problem/P1171

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int g[20][20];
// 2的x次幂大约是10的x/3次幂
int memo[1 << 20][20];

// visited, current pos
int dfs(int cnt, int i) {
    if (cnt == (1 << n) - 1) {
        return g[i][0];
    }
    if (memo[cnt][i] != INF) {
        return memo[cnt][i];
    }
    int& ans = memo[cnt][i];
    for (int j = 0; j < n; ++j) {
        if (i != j && ((1 << j) & cnt) == 0) {
            ans = min(ans, g[i][j] + dfs(cnt ^ (1 << j), j));
        }
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    
    // 递归形式
    // memset(memo, 0x3f, sizeof(memo));
    // cout << dfs(1 << 0, 0) << endl;

    // 递推
    // memo[i][j]: 从0出发，走过i状态后，停留在j的最小开销
    memset(memo, 0x3f, sizeof(memo));
    memo[1 << 0][0] = 0;
    for (int i = 1 << 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(i & (1 << j))) {
                continue;
            }
            // 优化，如果当前mask等于1 << j，说明只经过了一个点且j是初始点，但初始点之能是0
            if (i == (1 << j)) {
                continue;
            }
            for (int k = 0; k < n; ++k) {
                if (k == j || !((1 << k) & i)) {
                    continue;
                }
                memo[i][j] = min(memo[i][j], g[k][j] + memo[i ^ (1 << j)][k]);
            }
        }
    }

    int ans = INF;
    for (int j = 1; j < n; ++j) {
        ans = min(ans, g[j][0] + memo[(1 << n) - 1][j]);
    }

    cout << ans << endl;
}