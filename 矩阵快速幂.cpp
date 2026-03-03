#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define endl "\n"
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream& os, const T_container& v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
#define debug(x) cerr << #x << " = " << x << endl
#define debug2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl
#define debug3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl
#define debug_arr(a, n) do { cerr << #a << " = ["; for (int i = 0; i < (n); ++i) { if (i) cerr << ", "; cerr << (a)[i]; } cerr << "]" << endl; } while(0)
#define line() cerr << "--------------------" << endl

const int INF = 0x3f3f3f3f;
const int NEG_INF = 0xcfcfcfcf;

/* ------------ 删掉mod如果题目没要求，同36行 ------------ */
const int MOD = 1'000'000'007;

using Mat = vector<vector<ll>>;

// 通用矩阵乘法：A(r×m) @ B(m×c) -> C(r×c)
// 这里 i -> k -> j 的遍历顺序涉及cpu和内存优化
Mat multiply(const Mat& A, const Mat& B) {
    int r = A.size(), m = B.size(), c = B[0].size();
    Mat C(r, vector<ll>(c, 0));
    for (int i = 0; i < r; ++i) {
        for (int k = 0; k < m; ++k) {
            if (A[i][k] == 0) continue;
            for (int j = 0; j < c; ++j) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 计算 A^n @ f0，A 为 n×n 方阵，f0 形状任意（如列向量 n×1）
Mat pow_mul(Mat A, ll n, Mat f0) {
    while (n > 0) {
        if (n & 1) f0 = multiply(A, f0);
        A = multiply(A, A);
        n >>= 1;
    }
    return f0;
}

void solve() {
    int n; ll k;
    cin >> n >> k;

    Mat A(n, vector<ll>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    // 单位矩阵作为 f0 示例，等价于直接计算 A^k
    Mat f0(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i) f0[i][i] = 1;

    Mat ans = pow_mul(A, k, f0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << ans[i][j] << " \n"[j == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
}
