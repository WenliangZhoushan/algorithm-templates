#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128;
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
#define debugline() cerr << "--------------------" << endl

const int INF = 0x3f3f3f3f;
const int NEG_INF = 0xcfcfcfcf;

int t;
i128 n;
vector<i128> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

// 读取 __int128 类型的数字
i128 read() {
    i128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

// 输出 __int128 类型的数字
void print(i128 x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

i128 qpow(i128 a, i128 b, i128 mod) {
    i128 ret = 1;
    while(b) {
        if(b & 1) ret = (ret * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ret % mod;
}

bool miller_rabin(i128 n) {
    if(n < 3 || n % 2 == 0) return n == 2;
    i128 u = n - 1, t = 0;
    while(u % 2 == 0) u /= 2, ++ t;
    for(auto a : p) {
        if(n == a) return 1;
        if(n % a == 0) return 0;
        i128 v = qpow(a, u, n);
        if(v == 1) continue;
        i128 s = 1;
        for(; s <= t; ++ s) {
            if(v == n - 1) break;
            v = v * v % n;
        }
        if(s > t) return 0; 
    }
    return 1;
}

void solve() {
    n = read();
    if (miller_rabin(n)) {
        cout << "Yes" << endl;
        return;
    }
    cout << "No" << endl;
}

int main() {
    // 禁用以下代码，否则MLE
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    cin >> t;
    while (t--) {
        solve();
    }
}
