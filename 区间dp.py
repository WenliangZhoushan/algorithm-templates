'''
类型一：枚举两个端点
https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/
'''

from functools import cache
from typing import List
from math import inf

class Solution:
    def minInsertions(self, s: str) -> int:
        n = len(s)
        f = [[0] * n for _ in range(n)]

        # 枚举长度，固定长度情况下枚举左端点，通过左端点+长度计算出右端点
        for length in range(2, n + 1):
            for l in range(n - length + 1):
                r = l + length - 1
                if s[l] == s[r]:
                    f[l][r] = f[l + 1][r - 1]
                else:
                    f[l][r] = min(f[l + 1][r], f[l][r - 1]) + 1

        # return f[0][n - 1]

        n = len(s)
        f = [[0] * n for _ in range(n)]
        # 枚举右端点，固定右端点情况下枚举左端点，实际上左端点变小时相当于枚举更大的长度
        for i in range(n - 2, -1, -1):
            for j in range(i + 1, n):
                if s[i] == s[j]:
                    # i依赖于i + 1，i倒序。j依赖于j - 1，j正序
                    f[i][j] = f[i + 1][j - 1]
                else:
                    f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1

        # return f[0][n - 1]

        n = len(s)

        @cache
        def dfs(i, j):
            if i >= j:
                return 0
            if s[i] == s[j]:
                return dfs(i + 1, j - 1)
            return 1 + min(dfs(i + 1, j), dfs(i, j - 1))

        # return dfs(0, n - 1)

'''
类型二：固定左右端点情况下，枚举中间分割点
https://leetcode.cn/problems/minimum-score-triangulation-of-polygon/
'''

class Solution2:
    def minScoreTriangulation(self, values: List[int]) -> int:
        n = len(values)
        f = [[inf] * n for _ in range(n)]
        for i in range(n):
            for j in range(2):
                if i + j < n:
                    f[i][i + j] = 0

        # 枚举长度，固定长度下枚举左端点，通过长度+左端点计算右端点
        for l in range(3, n + 1):
            for i in range(0, n - l + 1):
                j = i + l - 1
                for k in range(i + 1, j):
                    cnt = values[i] * values[j] * values[k]
                    # i到k和k到j都有之前更小的长度遍历过，i和k任何顺序遍历都可
                    f[i][j] = min(f[i][j], cnt + f[i][k] + f[k][j])

        # return f[0][n - 1]

        n = len(values)
        f = [[inf] * n for _ in range(n)]
        for i in range(n):
            for j in range(2):
                if i + j < n:
                    f[i][i + j] = 0

        # 枚举左端点i，固定左端点i枚举右端点j，隐式地枚举长度l，逐渐变大
        for i in range(n - 3, -1, -1):
            for j in range(i + 2, n):
                for k in range(i + 1, j):
                    # i < k < j，j正序i倒序
                    cnt = values[i] * values[k] * values[j]
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j] + cnt)

        # return f[0][n - 1]

        @cache
        def dfs(i, j):
            if j - i + 1 < 3:
                return 0
            ans = inf
            for k in range(i + 1, j):
                a, b, c = values[i], values[k], values[j]
                ans = min(ans, a * b * c + dfs(i, k) + dfs(k, j))
            return ans

        # return dfs(0, len(values) - 1)

        @cache
        def dfs(i, j):
            if j - i + 1 == 3:
                return values[i] * values[i + 1] * values[j]
            ans = inf
            for k in range(i + 1, j):
                a, b, c = values[i], values[k], values[j]
                if k == i + 1:
                    ans = min(a * b * c + dfs(k, j), ans)
                    continue
                if k == j - 1:
                    ans = min(a * b * c + dfs(i, k), ans)
                    continue
                ans = min(a * b * c + dfs(i, k) + dfs(k, j), ans)
            return ans

        return dfs(0, len(values) - 1)


'''
类型三：固定左右端点为开区间，枚举中间端点
https://leetcode.cn/problems/burst-balloons/
'''

class Solution3:
    def maxCoins(self, nums: List[int]) -> int:
        nums = [1] + nums + [1]
        n = len(nums)
        f = [[0] * n for _ in range(n)]
        for i in range(1, n - 1):
            f[i - 1][i + 1] = nums[i - 1] * nums[i] * nums[i + 1]

        for i in range(n - 4, -1, -1):
            for j in range(i + 3, n):
                for k in range(i + 1, j):
                    # i和j最后被戳爆，枚举中间节点k
                    cnt = nums[k] * nums[i] * nums[j] + f[i][k] + f[k][j]
                    f[i][j] = max(f[i][j], cnt)

        return f[0][n - 1]
