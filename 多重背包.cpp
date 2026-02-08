// https://www.luogu.com.cn/problem/P1776
// n种物品，背包容量为W，每个物品价值为v, 重量为c，数量为m

// 单调队列优化组内枚举
#include <bits/stdc++.h>
using namespace std;

int n, W;
int values[110], costs[110], nums[110];
int f[2][40010]; // 滚动数组空间压缩

int f1(int i, int j) {
    // 在 j 位置下全拿（即使超过物品本身数量）能获得的价值
    return j / costs[i] * values[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> W;
    int v, w, m;
    for (int i = 0; i < n; ++i) {
        cin >> v >> w >> m;
        values[i] = v; costs[i] = w; nums[i] = m;
    }
    deque<int> dq;

    for (int i = 0; i < n; ++i) {
        // 用余数枚举背包内空间的起始位置
        for (int mod = 0; mod < min(costs[i], W + 1); ++mod) {
            dq.clear();
            for (int j = mod; j < W + 1; j += costs[i]) {
                // 当前容量减掉队头容量的差值大于物品最多可能的空间，出队
                while (!dq.empty() && j - dq.front() > costs[i] * nums[i]) {
                    dq.pop_front();
                }
                // 价值更大且排在更后面，入队
                while (!dq.empty() && f[i % 2][j] - f1(i, j) >= f[i % 2][dq.back()] - f1(i, dq.back())) {
                    dq.pop_back();
                }
                dq.push_back(j);
                // 保持单调队列的单调性，计算实际价值时候，当前位置一共可以拿的数量减掉队头位置一共可以拿的数量
                // 比如说某个位置j，一共可以拿6个，队头位置一共可以拿3个，两个差值为实际拿的数量（物品一共就3个）
                f[(i + 1) % 2][j] = f1(i, j) + f[i % 2][dq.front()] - f1(i, dq.front());
            }
        }
    }

    cout << f[n % 2][W] << '\n';
}

// 二进制优化枚举 + 暴力组内枚举
// #include <bits/stdc++.h>
// using namespace std;

// int n, W;
// /* 原版 
// int costs[110], values[110], nums[110];
// int f[110][40010];
// */
// int costs[2200], values[2200], nums[2200]; // log_2(m)
// int f[40010];

// int main () {
//     cin >> n >> W;
//     int v, w, m;
//     int j = 0;
//     for (int i = 0; i < n; ++i) {
//         cin >> v >> w >> m;
//         // 把物品用二进制拆分，比如说13 = 1 + 2 + 4 + 6
//         // 1 2 4 6可以组合出[1 ... 13]的所有组合
//         for (int k = 1; k <= m; k = (k << 1)) {
//             costs[j] = k * w; values[j] = k * v; nums[j] = k;
//             m -= k;
//             ++j;
//         }
//         if (m > 0) {
//             costs[j] = m * w; values[j] = m * v; nums[j] = m;
//             ++j;
//         }
//     }
//     // 二进制拆分后相当于枚举所有可能的子集，相当于01背包
//     for (int i = 0; i < j; ++i) {
//         for (int k = W; k > 0; --k) {
//             if (costs[i] > k) {
//                 break;
//             }
//             f[k] = max(f[k], f[k - costs[i]] + values[i]);
//         }
//     }

//     cout << f[W] << endl;

//     /* 枚举所有可能性，f[i + 1][j]固定情况下枚举[1...nums[i]]个物品。可AC
//     cin >> n >> W;
//     int v, w, m;
//     for (int i = 0; i < n; ++i) {
//         cin >> v >> w >> m;
//         costs[i] = w; values[i] = v; nums[i] = m;
//     }

//     for (int i = 0; i < n; ++i) {
//         int cost = costs[i], value = values[i], num = nums[i];
//         for (int j = 0; j < W + 1; ++j) {
//             for (int k = 0; k < num + 1; ++k) {
//                 if (k * cost > j) {
//                     f[i + 1][j] = max(f[i + 1][j], f[i][j]);
//                     break;
//                 } else {
//                     f[i + 1][j] = max(f[i + 1][j], f[i][j - k * cost] + k * value);
//                 }
//             }
//         }
//     }

//     cout << f[n][W] << endl;
//     */
// }