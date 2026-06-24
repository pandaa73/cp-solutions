#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << " " <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) dp { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int INF = 1e9;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N, M; cin >> N >> M;

    vec<bool> vis(N);

    vec<int> ans;
    vec<vec<int>> s(M + 1);
    for(int i = 0; i < M; ++i) {
        int K; cin >> K;
        s[i].resize(K);
        for(auto &x: s[i]) {
            cin >> x;
            vis[x] = 1;
        }

        ans.emplace_back(s[i][0]);
    }

    s.back().emplace_back(-1);
    for(int i = 0; i < N; ++i) {
        if(!vis[i]) {
            s.back().emplace_back(i);
        }
    }

    sort(all(s), [&](const vec<int> &a, const vec<int> &b) -> bool {
        return a[0] < b[0];
    });

    s.emplace_back();
    s.back().emplace_back(INF);

    vec<int> p(M + 2, 0);
    for(int i = 0; i <= M; ++i) {
        if(p[i] == s[i].size() - 1) continue;
        if(s[i][p[i] + 1] < s[i][p[i]]) break;
        if(s[i][p[i] + 1] > s[i + 1][p[i + 1]]) continue;

        ans.emplace_back(s[i][++p[i]]);

        i -= 1 + (i > 0);
    }

    if(ans.size() != N) {
        cout << "NO" << lf;
        return 0;
    }

    cout << "YES" << lf;
    for(auto x: ans) {
        cout << x << " ";
    }

    cout << lf;
}
