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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

struct DSU {
    DSU(int N): dsu(N, -1) {}

    int find(int v) {
        return dsu[v] < 0 ? v : dsu[v] = find(dsu[v]);
    }

    int find_safe(int v) {
        return v < 0 ? v : find(v);
    }

    void join(int u, int v) {
        u = find(u);
        v = find(v);

        if(u == v) return;

        if(dsu[u] > dsu[v]) swap(u, v);

        dsu[u] += dsu[v];
        dsu[v] = u;
    }

    int size(int v) {
        return -dsu[find(v)];
    }

    vector<int> dsu;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    DSU cc(N), bcc(N);

    vector<pii> F(N, {-1, -1});
    auto reroot = [&](int v) -> void {
        int f = -1, e = -1;
        for(int u = v; u >= 0;) {
            auto &[x, y] = F[u];

            x = bcc.find_safe(x);

            swap(f, x);
            swap(y, e);
            swap(f, u);
        }
    };

    auto merge = [&](int u, int v, int t) -> void {
        if(cc.size(u) > cc.size(v)) swap(u, v);

        reroot(u);
        F[u] = {v, t - 1};

        cc.join(u, v);
    };

    vector<bool> vis(N);
    vector<int> ans(M, -1);
    auto compress = [&](int u, int v, int t) -> void {
        int u0 = u, v0 = v;

        ans[t - 1] = t;

        stack<int> s;
        while(1) {
            if(u >= 0) {
                if(vis[u]) break;
                s.emplace(u);
                vis[u] = 1;

                u = F[u].fi = bcc.find_safe(F[u].fi);
            }

            if(v >= 0) {
                if(vis[v]) break;
                s.emplace(v);
                vis[v] = 1;

                v = F[v].fi = bcc.find_safe(F[v].fi);
            }
        }

        int lca = u < 0 ? v : (v < 0 ? u : (vis[u] ? u : v));

        while(!s.empty()) {
            vis[s.top()] = 0; s.pop();
        }

        auto merge_up = [&](int i) -> void {
            for(; i != lca; i = F[i].fi) {
                ans[F[i].se] = t;
                bcc.join(i, F[i].fi);
            }
        };

        merge_up(u0), merge_up(v0);

        int n = bcc.find(lca);
        F[n] = F[lca];
    };

    for(int t = 1; t <= M; ++t) {
        int u, v; cin >> u >> v;
        u = bcc.find(u - 1);
        v = bcc.find(v - 1);

        if(cc.find(u) != cc.find(v)) {
            merge(u, v, t);
        } else compress(u, v, t);
    }

    for(auto x: ans) {
        cout << x << " ";
    }

    cout << lf;
}
