#include<bits/stdc++.h>
using namespace std;

#include <cassert>

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
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

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

constexpr int MOD = 1e9 + 7;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    vec<vec<int>> adj(N);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vec<tuple<int, int, int>> ed;

    vec<int> d(N);
    vec<bool> vis(N), intr(N);

    intr[0] = intr[N - 1] = 1;

    auto dfs = [&](int u, int p, auto &&dfs) -> int {
        vis[u] = 1;

        vec<int> ch;
        for(auto v: adj[u]) {
            if(vis[v]) {
                if(d[v] < d[p]) {
                    intr[u] = intr[v] = 1;
                    ed.emplace_back(u, v, 1);
                }

                continue;
            }

            d[v] = 1 + d[u];
            int n = dfs(v, u, dfs);
            if(n >= 0) {
                ch.emplace_back(n);
            }
        }

        if(ch.size() >= 2) {
            intr[u] = 1;
        }

        if(intr[u]) {
            for(auto v: ch) {
                ed.emplace_back(u, v, d[v] - d[u]);
            }

            return u;
        }

        return ch.empty() ? -1 : ch[0];
    };

    dfs(N - 1, N - 1, dfs);

    infof(" ed: {}", ed);

    vec<int> p(N, -1);

    int n = 0;
    for(int u = 0; u < N; ++u) {
        if(intr[u]) p[u] = n++;
    }

    vec<vec<tuple<int, int, int>>> adj2(n);
    for(int e = 0; e < ed.size(); ++e) {
        auto [u, v, w] = ed[e];
        adj2[p[u]].emplace_back(p[v], w, e);
        adj2[p[v]].emplace_back(p[u], w, e);
    }

    for(int u = 0; u < n; ++u) {
        infof("adj[{}]: {}", u, adj2[u]);
    }

    vector dp(K + 1, vec<int>(n));
    vector rm(K + 1, vec<unordered_map<int, int>>(n));

    dp[0][p[0]] = 1;

    for(int k = 0; k < K; ++k) {
        for(int u = 0; u < n; ++u) {
            for(auto [v, w, e]: adj2[u]) {
                if(k + w > K) continue;

                int x = add(dp[k][u], MOD - rm[k][u][e]);
                rm[k + w][v][e] = x;
                chadd(dp[k + w][v], x);
            }
        }
    }

    for(int k = 0; k <= K; ++k) {
        infof("k = {} | dp[k] = {}", k, dp[k]);
    }

    cout << dp[K][n - 1] << lf;
}
