#include <bits/stdc++.h>
using namespace std;

// 版本1，范围是 [0, n]
class Solution {
public:
    int countSpecialNumbers(int n) {
        string s = to_string(n);
        int m = s.length();
        vector<vector<int>> memo(m, vector<int>(1 << 10, -1)); // -1 表示没有计算过
        auto dfs = [&](auto&& dfs, int i, int mask, bool is_limit, bool is_num) -> int {
            if (i == m) {
                return is_num; // is_num 为 true 表示得到了一个合法数字
            }
            if (!is_limit && is_num && memo[i][mask] != -1) {
                return memo[i][mask]; // 之前计算过
            }
            int res = 0;
            if (!is_num) { // 可以跳过当前数位
                res = dfs(dfs, i + 1, mask, false, false);
            }
            // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 啦）
            int up = is_limit ? s[i] - '0' : 9;
            // 枚举要填入的数字 d
            // 如果前面没有填数字，则必须从 1 开始（因为不能有前导零）
            for (int d = is_num ? 0 : 1; d <= up; d++) {
                if ((mask >> d & 1) == 0) { // d 不在 mask 中，说明之前没有填过 d
                    res += dfs(dfs, i + 1, mask | (1 << d), is_limit && d == up, true);
                }
            }
            if (!is_limit && is_num) {
                memo[i][mask] = res; // 记忆化
            }
            return res;
        };
        return dfs(dfs, 0, 0, true, false);
    }
};

// 版本2，范围是 [start, finish]
class Solution2 {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string low = to_string(start);
        string high = to_string(finish);
        int n = high.size();
        low = string(n - low.size(), '0') + low; // 补前导零，和 high 对齐
        int diff = n - s.size();

        vector<long long> memo(n, -1);
        auto dfs = [&](auto&& dfs, int i, bool limit_low, bool limit_high) -> long long {
            if (i == low.size()) {
                return 1;
            }

            if (!limit_low && !limit_high && memo[i] != -1) {
                return memo[i]; // 之前计算过
            }

            // 第 i 个数位可以从 lo 枚举到 hi
            // 如果对数位还有其它约束，应当只在下面的 for 循环做限制，不应修改 lo 或 hi
            int lo = limit_low ? low[i] - '0' : 0;
            int hi = limit_high ? high[i] - '0' : 9;

            long long res = 0;
            if (i < diff) { // 枚举这个数位填什么
                for (int d = lo; d <= min(hi, limit); d++) {
                    res += dfs(dfs, i + 1, limit_low && d == lo, limit_high && d == hi);
                }
            } else { // 这个数位只能填 s[i-diff]
                int x = s[i - diff] - '0';
                if (lo <= x && x <= hi) { // 题目保证 x <= limit，无需判断
                    res = dfs(dfs, i + 1, limit_low && x == lo, limit_high && x == hi);
                }
            }

            if (!limit_low && !limit_high) {
                memo[i] = res; // 记忆化 (i,false,false)
            }
            return res;
        };
        return dfs(dfs, 0, true, true);
    }
};