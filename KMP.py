# https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
# 找到s2在s1中第一个出现的下标

def build_next(s):
    m = len(s)
    if m == 1:
        return [-1]
    nxt = [-1] * m
    nxt[1] = 0
    i, cn = 2, 0
    while i < m:
        if s[cn] == s[i - 1]:
            nxt[i] = cn + 1
            i += 1
            cn += 1
        elif cn > 0:
            cn = nxt[cn]
        else:
            nxt[i] = 0
            i += 1
    return nxt

def kmp(s1, s2):
    n, m = len(s1), len(s2)
    nxt = build_next(s2)
    x = y = 0
    while x < n and y < m:
        if s1[x] == s2[y]:
            x += 1
            y += 1
        elif y == 0:
            x += 1
        else:
            y = nxt[y]
    return x - m if y == m else -1
