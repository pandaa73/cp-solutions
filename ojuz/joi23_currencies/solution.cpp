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

mt19937 timmy_loves_gambling(73);

constexpr int LOG = 20;
constexpr int INF = 1e9;

struct Query {
    int u, v;

    int x;
    ll y;
};

struct BIT {
    struct Node {
        Node(void): x(0), y(0) {}

        int x;
        ll y;
    };

    BIT(int N): N(N), T(N + 1) {}

    void add(int i, int x, ll y) {
        for(++i; i <= N; i += i&-i) {
            T[i].x += x;
            T[i].y += y;
        }
    }

    void add(int l, int r, int x, ll y) {
        add(l, x, y);
        add(r, -x, -y);
    }

    Node query(int i) {
        Node n;

        for(++i; i > 0; i -= i&-i) {
            n.x += T[i].x;
            n.y += T[i].y;
        }

        return n;
    }

    int N;
    vec<Node> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, Q; cin >> N >> M >> Q;

    vec<pii> ed(N - 1);
    vec<vec<int>> adj(N);
    for(auto &[u, v]: ed) {
        cin >> u >> v;
        u -= 1, v -= 1;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vec<pll> E(M);
    for(auto &[c, n]: E) {
        cin >> n >> c;
        n -= 1;
    }

    sort(rall(E));

    vec<Query> Qs(Q);
    for(auto &[u, v, x, y]: Qs) {
        cin >> u >> v;
        cin >> x >> y;
        u -= 1, v -= 1;
    }

    vec<int> in(N), out(N);
    vec<int> d(N), t_in(N), tour; tour.reserve(2 * N);
    auto dfs = [&](int u, int f, auto &&dfs) -> void {
        static int t = 0;

        in[u] = t++;
        t_in[u] = tour.size();

        for(auto v: adj[u]) {
            if(v == f) continue;

            d[v] = 1 + d[u];
            tour.emplace_back(u);

            dfs(v, u, dfs);
        }

        out[u] = t;
        tour.emplace_back(u);
    };

    dfs(0, -1, dfs);

    const int T = tour.size();

    vector tbl(LOG, vec<pii>(T));
    for(int i = 0; i < T; ++i) {
        tbl[0][i] = {d[tour[i]], tour[i]};
    }

    for(int lg = 0; lg < LOG - 1; ++lg) {
        for(int i = 0; i + (1 << (lg+1)) < T; ++i) {
            tbl[lg + 1][i] = min(tbl[lg][i], tbl[lg][i + (1 << lg)]);
        }
    }

    auto get_lca = [&](int u, int v) -> int {
        if(t_in[u] > t_in[v]) swap(u, v);

        const int l = t_in[u], r = t_in[v] + 1;
        const int lg = 31 - __builtin_clz(r - l);

        return min(tbl[lg][l], tbl[lg][r - (1 << lg)]).se;
    };

    BIT bit(N);
    int pos = 0;

    for(auto &[c, n]: E) {
        auto [u, v] = ed[n];

        n = d[u] > d[v] ? u : v;

        bit.add(in[n], out[n], 0, c);
    }

    vec<int> ans(Q, INF);
    auto search = [&](int l, int r, vec<int> M, auto &&search) -> void {
        int m = (l + r) / 2;

        while(pos < m) {
            auto [c, n] = E[pos++];
            bit.add(in[n], out[n], 1, -c);
        }

        while(pos > m) {
            auto [c, n] = E[--pos];
            bit.add(in[n], out[n], -1, c);
        }

        vec<int> L, R;
        for(auto q: M) {
            auto [u, v, x, y] = Qs[q];

            auto [x_u, y_u] = bit.query(in[u]);
            auto [x_v, y_v] = bit.query(in[v]);

            int lca = get_lca(u, v);
            auto [x_lca, y_lca] = bit.query(in[lca]);

            auto x_path = x_u + x_v - 2 * x_lca;
            auto y_path = y_u + y_v - 2 * y_lca;

            if(y >= y_path) {
                ans[q] = min(ans[q], x_path);
            }

            if(r - l <= 1) continue;

            (y >= y_path ? L : R).emplace_back(q);
        }

        if(L.size()) search(l, m, L, search);
        if(R.size()) search(m, r, R, search);
    };

    vec<int> init(Q);
    iota(all(init), 0);
    search(0, M + 1, init, search);

    for(int q = 0; q < Q; ++q) {
        cout << (ans[q] > Qs[q].x ? -1 : Qs[q].x - ans[q]) << lf;
    }
}
