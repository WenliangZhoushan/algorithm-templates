#include <bits/stdc++.h>
using namespace std;

// https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
// 找到s2在s1中第一个出现的下标

vector<int> build_next(string& s) {
  int m = s.size();
  if (m == 1) {
    return {-1};
  }
  vector<int> nxt(m, -1);
  nxt[1] = 0;
  int i = 2, cn = 0;
  while (i < m) {
    if (s[i - 1] == s[cn]) {
      nxt[i++] = ++cn;
    } else if (cn == 0) {
      nxt[i++] = 0;
    } else {
      cn = nxt[cn];
    }
  }
  return nxt;
}

int kmp(string& s1, string& s2) {
  int n = s1.size(), m = s2.size(), x = 0, y = 0;
  vector<int> nxt = build_next(s2);
  while (x < n && y < m) {
    if (s1[x] == s2[y]) {
      ++x;
      ++y;
    } else if (y == 0) {
      ++x;
    } else {
      y = nxt[y];
    }
  }
  return y == m ? x - y : -1;
}
