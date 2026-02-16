#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int trie[MAXN][26], pass[MAXN], cnt[MAXN], idx;

void init() {
    idx = 1;
    memset(trie, 0, sizeof(trie));
    memset(pass, 0, sizeof(pass));
    memset(cnt, 0, sizeof(cnt));
}

void add(const string& s) {
    int cur = 0;
    for (char c : s) {
        int j = c - 'a';
        if (!trie[cur][j]) trie[cur][j] = idx++;
        cur = trie[cur][j];
        ++pass[cur];
    }
    ++cnt[cur];
}

void del(const string& s) {
    // 先检查是否存在，防止误删
    int cur = 0;
    for (char c : s) {
        int j = c - 'a';
        if (!trie[cur][j]) return;
        cur = trie[cur][j];
    }
    if (!cnt[cur]) return;
    // 确认存在，再沿路减 pass
    cur = 0;
    for (char c : s) {
        cur = trie[cur][c - 'a'];
        --pass[cur];
    }
    --cnt[cur];
}

// 查询 s 作为完整单词出现的次数
int countWord(const string& s) {
    int cur = 0;
    for (char c : s) {
        int j = c - 'a';
        if (!trie[cur][j]) return 0;
        cur = trie[cur][j];
    }
    return cnt[cur];
}

// 查询以 s 为前缀的单词个数
int countPrefix(const string& s) {
    int cur = 0;
    for (char c : s) {
        int j = c - 'a';
        if (!trie[cur][j]) return 0;
        cur = trie[cur][j];
    }
    return pass[cur];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int m, op;
    string word;

    // 每次使用要初始化，防止上次过程污染
    init();
    cin >> m;
    while (m--) {
        cin >> op >> word;
        if (op == 1) add(word);
        else if (op == 2) del(word);
        else if (op == 3) cout << (countWord(word) ? "YES" : "NO") << '\n';
        else cout << countPrefix(word) << '\n';
    }
}

// 字典树最大化异或
// https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/description/
class Solution {
    int trie[10000000][2];
    int idx = 1;

public:
    int findMaximumXOR(vector<int>& nums) {
        // 建树，把所有数字按照二进制加入字典树
        for (int& x : nums) {
            int cur = 0;
            for (int i = 30; i >= 0; --i) {
                int j = x >> i & 1;
                if (!trie[cur][j])
                    trie[cur][j] = idx++;
                cur = trie[cur][j];
            }
        }

        // 贪心地思考每一位数字
        // 如果树里有当前位置的值的异或结果，走那个分支，最大化cnt
        // 否则走和当前位置的值相同的结果，去最大化更小位的异或结果
        int ans = 0;
        for (int& x : nums) {
            int cur = 0, cnt = 0;
            for (int i = 30; i >= 0; --i) {
                int j = x >> i & 1;
                if (trie[cur][j ^ 1]) {
                    cnt |= 1 << i;
                    cur = trie[cur][j ^ 1];
                } else {
                    cur = trie[cur][j];
                }
            }
            ans = max(ans, cnt);
        }

        return ans;
    }
};