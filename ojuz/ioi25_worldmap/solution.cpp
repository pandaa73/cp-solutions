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

void validate(int N, int M, const vec<int> &A, const vec<int> &B,
        const vec<vec<int>> &G) {
    if constexpr(!IS_DEBUG) return;

    infof("======= validator =======");

    bool ok = 1;

    const int K = G.size();

    vec<set<int>> adj(N + 1);
    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < K; ++j) {
            if(i + 1 < K) {
                adj[G[i][j]].emplace(G[i + 1][j]);
                adj[G[i + 1][j]].emplace(G[i][j]);
            }

            if(j + 1 < K) {
                adj[G[i][j]].emplace(G[i][j + 1]);
                adj[G[i][j + 1]].emplace(G[i][j]);
            }
        }
    }

    vec<set<int>> true_adj(N + 1);
    for(int i = 0; i < M; ++i) {
        true_adj[A[i]].emplace(B[i]);
        true_adj[B[i]].emplace(A[i]);
    }

    for(int i = 1; i < N; ++i) {
        adj[i].erase(i);

        if(adj[i] == true_adj[i]) continue;

        ok = 0;

        infof("error: incorrect adjacencies for node {}.", i);
        infof("... expected: {}", true_adj[i]);
        infof("...    found: {}", adj[i]);
    }

    infof("verdict: {}", ok ? "OK" : "WA");
}

vector<vector<int>> create_map(int N, int M, vector<int> A, vector<int> B) {
    vec<vec<int>> adj(N + 1), up(N + 1), ch(N + 1);
    for(int i = 0; i < M; ++i) {
        adj[A[i]].emplace_back(B[i]);
        adj[B[i]].emplace_back(A[i]);
    }

    vec<int> d(N + 1, N), md(N + 1);
    auto dfs = [&](int v, auto &&dfs) -> void {
        md[v] = d[v];

        for(auto u: adj[v]) {
            if(d[u] < d[v]) {
                up[v].emplace_back(u);
            }

            if(d[u] < N) continue;

            ch[v].emplace_back(u);

            d[u] = d[v] + 1;
            dfs(u, dfs);
            md[v] = max(md[v], md[u]);
        }

        sort(all(ch[v]), [&](int i, int j) -> bool {
            return md[i] < md[j];
        });
    };

    d[1] = 0;
    dfs(1, dfs);

    vec<int> tour; tour.reserve(2 * N - 1);
    auto dfs2 = [&](int v, auto &&dfs2) -> void {
        for(auto u: ch[v]) {
            tour.emplace_back(v);
            dfs2(u, dfs2);
        }

        tour.emplace_back(v);
    };

    dfs2(1, dfs2);

    infof("   d: {}", d);
    infof("  md: {}", md);
    infof("tour: {}", tour);

    vec<vec<int>> G(2 * N, vec<int>(2 * N, 1));

    int diag = 0;
    auto fill_diag = [&](const vec<int> &V, int v) {
        int x = 0, y = diag;

        if(y > 2 * N - 1) {
            x += y - (2 * N - 1);
            y = 2 * N - 1;
        }

        int i = 0;
        for(; x < 2 * N && y >= 0; ++x, y--) {
            G[x][y] = i < V.size() ? V[i++] : v;
        }

        diag += 1;
    };

    for(auto v: tour) {
        fill_diag({}, v);

        if(up[v].empty()) continue;

        fill_diag(up[v], v);
        fill_diag({}, v);

        up[v].clear();
    }

    validate(N, M, A, B, G);

    return G;
}

#ifdef LOCAL
int main() {
  int T;
  assert(1 == scanf("%d", &T));

  std::vector<int> Nt(T), Mt(T);
  std::vector<std::pair<std::vector<int>, std::vector<int>>> AB;

  for (int t = 0; t < T; ++t) {
    assert(2 == scanf("%d %d", &Nt[t], &Mt[t]));

    int M = Mt[t];
    std::vector<int> A(M), B(M);

    for (int i = 0; i < Mt[t]; i++) {
      assert(2 == scanf("%d %d", &A[i], &B[i]));
    }
    AB.push_back(make_pair(A, B));
  }

  fclose(stdin);

  std::vector<std::vector<std::vector<int>>> Ct;

  for (int t = 0; t < T; t++) {
    int N = Nt[t], M = Mt[t];
    std::vector<int> A = AB[t].first, B = AB[t].second;

    auto C = create_map(N, M, A, B);
    Ct.push_back(C);
  }

  for (int t = 0; t < T; t++) {
    auto& C = Ct[t];
    int P = (int)C.size();

    std::vector<int> Q(P);
    for (int i = 0; i < P; ++i)
      Q[i] = (int)C[i].size();

    printf("%d\n", P);
    for (int i = 0; i < P; ++i)
      printf("%d%c", Q[i], " \n"[i + 1 == P]);
    printf("\n");
    for (int i = 0; i < P; i++) {
      for (int j = 0; j < Q[i]; j++) {
        printf("%2d%c", C[i][j], " \n"[j + 1 == Q[i]]);
      }
    }
    if (t < T - 1)
      printf("\n");
  }

  fclose(stdout);

  return 0;
}
#endif
