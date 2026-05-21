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

constexpr ll INF = 1e18;

template<typename T>
inline void chmin(T &a, T b) {
    a = min(a, b);
}

struct DSU {
    DSU(int N, const vec<ll> &V, const vec<int> &P):
            sum(accumulate(all(V), 0LL)),
            m(N, INF),
            mn(N, {INF, INF}),
            P(P),
            N(N),
            dsu(N, -1) {
        for(int i = 0; i < N; ++i) {
            mn[i].fi = V[i];
        }
    }

    inline ll f(int v) {
        if constexpr(IS_DEBUG) {
            assert(dsu[v] < 0);
        }

        return (-dsu[v])&1 ? min(m[v], mn[v].fi) : 0LL;
    }

    void update(int v, ll x) {
        v = find(v);

        sum -= f(v);
        chmin(m[v], x);
        sum += f(v);
    }

    int find(int v) {
        return dsu[v] < 0 ? v : dsu[v] = find(dsu[v]);
    }

    void join(int u, int v) {
        u = find(u);
        v = find(v);

        if(u == v) return;

        sum -= f(u);
        sum -= f(v);

        if(P[u] > P[v]) swap(u, v);
        if(dsu[u]&1) swap(mn[v].fi, mn[v].se);

        if(dsu[u] > dsu[v]) swap(u, v);

        chmin(m[u], m[v]);
        chmin(mn[u].fi, mn[v].fi);
        chmin(mn[u].se, mn[v].se);

        dsu[u] += dsu[v];
        dsu[v] = u;

        sum += f(u);
    }

    ll sum;
    vec<ll> m;
    vec<pll> mn;

    vec<int> P;

    int N;
    vec<int> dsu;
};

vector<long long> calculate_costs(vector<int> W, vector<int> A, vector<int> B,
        vector<int> E) {
    const int N = W.size();
    const int Q = E.size();

    vec<int> ord(N); iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return W[i] < W[j];
    });

    vec<int> P(N);
    for(int i = 0; i < N; ++i) {
        P[ord[i]] = i;
    }

    vec<int> ord_q(Q); iota(all(ord_q), 0);
    sort(all(ord_q), [&](int i, int j) -> bool {
        return E[i] < E[j];
    });

    vec<pii> events; events.reserve(2 * N - 3);
    for(int ii = 0; ii < N - 1; ++ii) {
        int i = ord[ii + 0], j = ord[ii + 1];
        events.emplace_back(W[j] - W[i], ii);

        if(ii > 0) {
            int k = ord[ii - 1];
            events.emplace_back(W[j] - W[k], -ii);
        }
    }

    sort(all(events));

    vec<ll> V(N);
    for(int i = 0; i < N; ++i) {
        V[i] = A[i] - B[i];
    }

    DSU dsu(N, V, P);
    vec<ll> ans(Q, accumulate(all(B), 0LL));

    int idx = 0;
    for(auto q: ord_q) {
        for(; idx < events.size() && events[idx].fi <= E[q]; ++idx) {
            int ii = events[idx].se;

            if(ii < 0) {
                int v = ord[-ii];
                dsu.update(v, V[v]);
            } else dsu.join(ord[ii + 0], ord[ii + 1]);
        }

        ans[q] += dsu.sum;
    }

    return ans;
}

#ifdef LOCAL
int main() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> W(N), A(N), B(N);
  for (int i = 0; i < N; i++)
    assert(3 == scanf("%d%d%d", &W[i], &A[i], &B[i]));
  int Q;
  assert(1 == scanf("%d", &Q));
  std::vector<int> E(Q);
  for (int j = 0; j < Q; j++)
    assert(1 == scanf("%d", &E[j]));
  fclose(stdin);

  std::vector<long long> R = calculate_costs(W, A, B, E);

  int S = (int)R.size();
  for (int j = 0; j < S; j++)
    printf("%lld\n", R[j]);
  fclose(stdout);

  return 0;
}
#endif
