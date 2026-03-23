#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream& operator<<(ostream& os, const T_container& v) {
  os << "{"; string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << "}";
}

// ---- Debug macros: use cout for LeetCode (stderr not shown) ----
#define debug(x)       cout << "[DBG] " << #x << " = " << x << "\n" << flush
#define debug2(x, y)   cout << "[DBG] " << #x << " = " << x << ", " << #y << " = " << y << "\n" << flush
#define debug3(x,y,z)  cout << "[DBG] " << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << "\n" << flush
#define debug_arr(a, n) do { \
  cout << "[DBG] " << #a << " = ["; \
  for (int i = 0; i < (n); ++i) { if (i) cout << ", "; cout << (a)[i]; } \
  cout << "]\n" << flush; \
} while(0)
#define debugline() cout << "[DBG] --------------------\n" << flush

const int INF = 0x3f3f3f3f;
const int NEG_INF = 0xcfcfcfcf;
