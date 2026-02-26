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
#define debugline() cerr << "--------------------" << endl

const int INF = 0x3f3f3f3f;
const int NEG_INF = 0xcfcfcfcf;

// 返回n的质因子分解结果：(质因子, 指数)
// 例如：n = 360 -> (2,3), (3,2), (5,1)
vector<pair<ll, int>> factorize(ll n) {
	vector<pair<ll, int>> factors;
	if (n <= 1) {
		return factors;
	}

	for (ll p = 2; p * p <= n; ++p) {
		if (n % p != 0) {
			continue;
		}
		int cnt = 0;
		while (n % p == 0) {
			n /= p;
			++cnt;
		}
		factors.push_back({p, cnt});
	}

	if (n > 1) {
		factors.push_back({n, 1});
	}
	return factors;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	auto factors = factorize(n);

	if (factors.empty()) {
		cout << n << " 没有质因子分解结果\n";
		return 0;
	}

	// 输出格式：p1^a1 * p2^a2 * ...
	for (int i = 0; i < (int)factors.size(); ++i) {
		if (i) {
			cout << " * ";
		}
		cout << factors[i].first;
		if (factors[i].second > 1) {
			cout << '^' << factors[i].second;
		}
	}
	cout << endl;;
}
