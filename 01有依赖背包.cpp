// https://www.luogu.com.cn/problem/P1064

#include <bits/stdc++.h>
using namespace std;

int n, m;
pair<int, int> cv[65];
int king[65];
int subs[65][2];
int f[65][32010];

int f1(int i, int j) {
    // buy main item only
    return max(f[i - 1][j], f[i - 1][j - cv[i].first] + cv[i].second);
}

int f2(int i, int j) {
    // buy main and fist sub
    return max({
        f1(i, j),
        f[i - 1][j - cv[i].first - cv[subs[i][0]].first] + cv[i].second + cv[subs[i][0]].second,
    });
}

int f3(int i, int j) {
    // buy main and second sub
    return max({
        f1(i, j),
        f[i - 1][j - cv[i].first - cv[subs[i][1]].first] + cv[i].second + cv[subs[i][1]].second,
    });
}

int f4(int i, int j) {
    // buy main and both sub
    return max({
        f2(i, j), f3(i, j),
        f[i - 1][j - cv[i].first - cv[subs[i][0]].first - cv[subs[i][1]].first] + cv[i].second + cv[subs[i][0]].second + cv[subs[i][1]].second,
    });
}

int main() {
    memset(subs, -1, sizeof(subs));
    cin >> n >> m;
    int v, p, q;

    for (int i = 1; i < m + 1; ++i) {
        cin >> v >> p >> q;
        cv[i] = make_pair(v, v * p);
        if (q != 0) {
            int j = subs[q][0] == -1 ? 0 : 1;
            subs[q][j] = i;
        } else {
            ++king[i];
        }
    }

    int ans = 0;

    for (int i = 1; i < m + 1; ++i) {
        if (!king[i]) {
            for (int j = 0; j < n + 1; ++j) f[i][j] = f[i - 1][j]; 
            continue;
        }
        for (int j = 0; j < n + 1; ++j) {
            if (cv[i].first > j) {
                f[i][j] = f[i - 1][j];
                continue;
            };
            if (subs[i][0] == -1 && subs[i][1] == -1) {
                f[i][j] = f1(i, j);
            } else if (subs[i][0] != -1 && subs[i][1] == -1) {
                f[i][j] = cv[i].first + cv[subs[i][0]].first <= j ? f2(i, j) : f1(i, j);
            } else {
                if (cv[i].first + cv[subs[i][0]].first + cv[subs[i][1]].first <= j) {
                    f[i][j] = f4(i, j);
                } else if (cv[i].first + cv[subs[i][0]].first <= j && cv[i].first + cv[subs[i][1]].first <= j) {
                    f[i][j] = max(f2(i, j), f3(i, j));
                }else if (cv[i].first + cv[subs[i][0]].first <= j) {
                    f[i][j] = f2(i, j);
                } else if (cv[i].first + cv[subs[i][1]].first <= j) {
                    f[i][j] = f3(i, j);
                } else {
                    f[i][j] = f1(i, j);
                }
            }
        }
        ans = max(ans, ranges::max(f[i]));
    }

    cout << ans << endl;
}