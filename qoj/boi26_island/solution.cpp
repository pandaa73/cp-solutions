#include <bits/stdc++.h>
using namespace std;

#include <cassert>

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << " " <<
#define all(r) begin(r),end(r)
#define rall(r) rbegin(r),rend(r)

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

constexpr int LOG = 20;

struct Solver {
    Solver(int M, const vector<string> &G): T(M, vec<int>(M, -1)) {
        int N = 0;

        for(int r = 1; r < M - 1; ++r) {
            bool fi = 1;
            for(int c = 1; c < M - 1; ++c) {
                if(G[r][c] == '.') {
                    fi = 1;
                } else if(fi) {
                    T[r][c] = N++;
                    fi = 0;
                } else {
                    T[r][c] = T[r][c - 1];
                }
            }
        }

        vec<vec<int>> adj(N);
        auto add_edge = [&](int u, int v) -> void {
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        };

        for(int r = 1; r < M - 1; ++r) {
            for(int c = 1; c < M - 1; ++c) {
                if(G[r][c] == '.') continue;

                if(G[r + 1][c] == '#' && T[r + 1][c] > T[r][c]
                        && (G[r + 1][c - 1] == '.' || G[r][c - 1] == '.')) {
                    add_edge(T[r][c], T[r + 1][c]);
                }

                if(G[r - 1][c] == '#' && T[r - 1][c] > T[r][c]
                        && (G[r - 1][c - 1] == '.' || G[r][c - 1] == '.')) {
                    add_edge(T[r][c], T[r - 1][c]);
                }
            }
        }

        vec<int> tour;
        tour.reserve(2 * N - 1);
        d.resize(N), in.resize(N);
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            in[u] = tour.size();
            tour.emplace_back(u);

            for(auto v: adj[u]) {
                if(v == p) continue;

                d[v] = 1 + d[u];
                dfs(v, u, dfs);
                tour.emplace_back(u);
            }
        };

        dfs(0, N, dfs);

        const int K = tour.size();
        tbl = vector(LOG, vec<pii>(K));
        for(int i = 0; i < K; ++i) {
            tbl[0][i] = {d[tour[i]], tour[i]};
        }

        for(int lg = 0; lg < LOG - 1; ++lg) {
            int pow = 1 << lg;
            for(int i = 0; i + pow < K; ++i) {
                tbl[lg + 1][i] = min(tbl[lg][i], tbl[lg][i + pow]);
            }
        }

        for(int i = 0; i < M; ++i) {
            infof("T[{}]: {}", i, T[i]);
        }

        infof("N = {}", N);
        for(int i = 0; i < N; ++i) {
            infof("adj[{}]: {}", i, adj[i]);
        }

        infof("tour: {}", tour);
        infof("d: {}", d);
        infof("in: {}", in);
    }

    int get_lca(int u, int v) {
        if(in[u] > in[v]) {
            swap(u, v);
        }

        int l = in[u], r = in[v] + 1;
        int lg = 31 - __builtin_clz(r - l);
        int pow = 1 << lg;
        return min(tbl[lg][l], tbl[lg][r - pow]).se;
    }

    int distance(int u, int v) {
        int lca = get_lca(u, v);
        return d[u] + d[v] - 2 * d[lca];
    }

    int distance(int ar, int ac, int br, int bc) {
        return distance(T[ar][ac], T[br][bc]);
    }

    vec<vec<int>> T;

    vec<int> d;
    vec<int> in;
    vec<vec<pii>> tbl;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vec<string> G(N);
    for(auto &r: G) cin >> r;

    vector H(N, string(N, '.'));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            H[i][j] = G[j][i];
        }
    }

    Solver r_solver(N, G);
    Solver c_solver(N, H);

    for(int qi = 0; qi < Q; ++qi) {
        int ar, ac; cin >> ar >> ac;
        int br, bc; cin >> br >> bc;

        ar -= 1, ac -= 1;
        br -= 1, bc -= 1;

        int dr = r_solver.distance(ar, ac, br, bc);
        int dc = c_solver.distance(ac, ar, bc, br);

        cout << dr + dc << lf;
    }
}
