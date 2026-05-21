#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

constexpr ll INF = 2e18;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    ll S; cin >> S;

    vec<int> W(N + 1);
    vec<vec<int>> adj(N + 1);
    for(int i = 1; i <= N; ++i) {
        int x, p; cin >> x >> p;

        W[i] = x;
        adj[p].emplace_back(i);
    }

    vec<ll> mn(N + 1, 0), p(N + 1, 0);
    vec<priority_queue<pll, vec<pll>, greater<pll>>> q(N + 1);
    auto dfs = [&](int v, auto &&dfs) -> void {
        for(auto u: adj[v]) {
            dfs(u, dfs);

            if(mn[u] < INF) {
                q[v].emplace(mn[u], u);
            }
        }

        p[v] = W[v];
        while(!q[v].empty() && p[v] <= 0) {
            auto [m, u] = q[v].top();
            q[v].pop();

            mn[v] = max(mn[v], mn[u] - p[v]);
            p[v] += p[u];

            if(q[v].size() < q[u].size()) {
                swap(q[u], q[v]);
            }

            while(!q[u].empty()) {
                q[v].emplace(q[u].top());
                q[u].pop();
            }
        }

        if(p[v] <= 0) {
            mn[v] = INF;
        }
    };

    dfs(0, dfs);

    infof("mn: {}", mn);
    infof(" p: {}", p);

    ll profit = 0;

    priority_queue<pll, vec<pll>, greater<pll>> r;
    r.emplace(mn[0], 0);

    while(!r.empty()) {
        auto [m, v] = r.top();
        r.pop();

        if(S + profit < m) break;

        profit += p[v];

        if(r.size() < q[v].size()) {
            swap(r, q[v]);
        }

        while(!q[v].empty()) {
            r.emplace(q[v].top());
            q[v].pop();
        }
    }

    cout << profit << lf;
}
