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

const int MOD = 1'000'000'007;
const int MAXN = 105;
int n;
ll k;

struct Matrix {
    ll a[MAXN][MAXN];
    Matrix() { memset(a, 0, sizeof(a)); }
} nums;

// 这里 i -> k -> j 的遍历顺序涉及cpu和内存优化
Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= n; ++k) {
            if (A.a[i][k] == 0) continue;
            for (int j = 1; j <= n; ++j) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
        }
    }
    return C;
}

void solve() {
    cin >> n >> k;
    Matrix ans;
    for (int i = 1; i <= n; ++i) {
        ans.a[i][i] = 1;
        for (int j = 1; j <= n; ++j) {
            cin >> nums.a[i][j];
        }
    }

    while (k > 0) {
        if (k & 1) ans = multiply(ans, nums);
        nums = multiply(nums, nums);
        k >>= 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << ans.a[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
}
