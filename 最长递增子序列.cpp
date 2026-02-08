// https://www.luogu.com.cn/problem/P8776
// 一个数组中非递减子序列的数量等于数组中最长递增子序列

#include <bits/stdc++.h>
using namespace std;

int nums[100010];
int f[100010];
int N, K;

int main() {
    cin >> N >> K;
    for (int i = 1; i < N + 1; ++i) {
        cin >> nums[i];
    }

    if (K >= N) {
        cout << K << endl;
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
        if (l == cnt.size()) {
            cnt.push_back(nums[i]);
        } else {
            cnt[l] = nums[i];
        }
        f[i] = l + 1;
    }

    int ans = K + f[K + 1];
    cnt.clear();

    for (int i = 1; i < N - K + 1; ++i) {
        int l = 0, r = cnt.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (cnt[m] <= nums[i]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (l == cnt.size()) {
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

    cout << ans << endl;
}