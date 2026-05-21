#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>

template<typename... Args>
using vec = vector<Args...>;

#ifdef MARCO
constexpr bool IS_DEBUG = 1;
#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)
#else
constexpr bool IS_DEBUG = 0;
#define infor(fmt, ...)
#define infof(fmt, ...)
#endif

mt19937 timmy_loves_gambling(73);

constexpr int MOD = 1e9+9;
constexpr ll INF = 1e18;

void solve() {
    int N, S, T, M; cin >> N >> S >> T >> M;
    S -= 1, T -= 1;

    vec<vec<pii>> adj(N);
    for(int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;
        u -= 1, v -= 1;

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    auto dijkstra = [&](int s, vec<ll> &d) -> void {
        priority_queue<pll, vec<pll>, greater<pll>> q;
        q.emplace(0, s);
        d[s] = 0;

        while(!q.empty()) {
            auto [l, u] = q.top();
            q.pop();

            if(d[u] != l) continue;

            for(auto [v, w]: adj[u]) {
                if(l + w >= d[v]) continue;

                d[v] = l + w;
                q.emplace(d[v], v);
            }
        }
    };

    vec<ll> ds(N, INF), dt(N, INF);
    dijkstra(S, ds);
    dijkstra(T, dt);

    vec<int> ord(N);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return ds[i] - dt[i] < ds[j] - dt[j];
    });

    int ans = 0;
    for(int i = 0; i < N; ++i) {
        int j = ord[i];
        ll x = ds[ord[i]] % MOD;
        ll y = dt[ord[i]] % MOD;

        int l = i, r = N - i - 1;

        ans = (ans + (x * r)) % MOD;
        ans = (ans + (y * l)) % MOD;
    }

    ll x = ds[T] % MOD;
    int c = (ll)N * (N - 1) / 2 % MOD;

    ans = (ans + (x * c)) % MOD;

    cout << ans << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T = 1;
    while(T--) solve();
}
