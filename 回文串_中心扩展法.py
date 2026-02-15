# https://leetcode.cn/problems/longest-palindromic-substring/description/

class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        ans_l = ans_r = 0  # [ans_l, ans_r]

        # 同时枚举长度为奇数和偶数的回文串
        for i in range(2 * n - 1):
            l, r = i // 2, (i + 1) // 2
            while l >= 0 and r < n and s[l] == s[r]:
                l -= 1
                r += 1
            if r - l - 1 > ans_r - ans_l + 1:
                ans_l, ans_r = l + 1, r - 1

        return s[ans_l : ans_r + 1]
