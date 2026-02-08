// https://www.luogu.com.cn/problem/P8776
// Dilworth定理：将数组划分为最少的严格下降子序列数 = 最长不下降子序列的长度

#include <bits/stdc++.h>
using namespace std;

int nums[100010];
int f[100010];
int N, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> nums[i];
    }

    if (K >= N) {
        cout << K << '\n';
        return 0;
    }

    vector<int> cnt;
    for (int i = N; i > 0; --i) {
        int l = 0, r = cnt.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (cnt[m] >= nums[i]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (l == (int)cnt.size()) {
            cnt.push_back(nums[i]);
        } else {
            cnt[l] = nums[i];
        }
        f[i] = l + 1;
    }

    int ans = K + f[K + 1];
    cnt.clear();

    for (int i = 1; i <= N - K; ++i) {
        int l = 0, r = cnt.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (cnt[m] <= nums[i]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (l == (int)cnt.size()) {
            cnt.push_back(nums[i]);
        } else {
            cnt[l] = nums[i];
        }

        int j = i + K + 1;
        if (j == N + 1) {
            ans = max(ans, K + (int)cnt.size());
            break;
        }
        l = 0, r = cnt.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (cnt[m] <= nums[j]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        ans = max(ans, l + K + f[j]);
    }

    cout << ans << '\n';
}