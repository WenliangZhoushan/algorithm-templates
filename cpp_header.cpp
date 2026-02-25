#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
#define endl "\n"
#define fi first
#define se second

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i < v.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}
#define debug(x) cerr << #x << " = " << x << endl
#define debug_arr(a, n) do { cerr << #a << " = ["; for (int i = 0; i < (n); ++i) { if (i) cerr << ", "; cerr << (a)[i]; } cerr << "]" << endl; } while(0)
#define debug2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl
#define debug3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl
#define debugline() cerr << "--------------------" << endl

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}

// ===== 使用示例 =====
/*
int main() {
    int n = 5;
    vector<int> nums = {1, 2, 3, 4, 5};
    vector<int> s = {10, 20, 30};
    
    debug(n);              // 输出: n = 5
    debug(nums);           // 输出: nums = [1, 2, 3, 4, 5]
    debug(s);              // 输出: s = [10, 20, 30]
    debug2(n, nums);       // 输出: n = 5, nums = [1, 2, 3, 4, 5]
    debugline();           // 输出: --------------------
    
    return 0;
}
*/

// 注意事项：
// - 使用 cerr 而不是 cout，避免与正常输出混淆
// - 提交代码前记得删除或注释掉 debug 语句
// - 可以用 #ifdef LOCAL 包裹，本地测试时定义 LOCAL 宏即可
