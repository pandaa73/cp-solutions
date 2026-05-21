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

constexpr ll INF = 1e18;

struct Node {
    Node(void): d(0), l(0), r(0) {}
    Node(ll k, ll v): d(0), k(k), v(v), l(0), r(0) {}
    Node(int d, ll k, ll v, int l, int r): d(d), k(k), v(v), l(l), r(r) {}

    int d;
    ll k, v;
    int l, r;
};

vec<Node> T(1);

int make_node(ll k, ll v) {
    T.emplace_back(k, v);
    return T.size() - 1;
}

int make_node(int d, ll k, ll v, int l, int r) {
    T.emplace_back(d, k, v, l, r);
    return T.size() - 1;
}

int merge(int n, int m) {
    if(!n || !m) return n ? n : m;

    if(T[n].k > T[m].k) swap(n, m);

    int l = T[n].l, r = merge(T[n].r, m);
    if(T[l].d < T[r].d) swap(l, r);

    return make_node(T[r].d + 1, T[n].k, T[n].v, l, r);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, s, t, K; cin >> N >> M >> s >> t >> K;

    vec<vec<pii>> adj(N), radj(N);
    for(int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;

        adj[u].emplace_back(v, w);
        radj[v].emplace_back(u, w);
    }

    vec<int> p(N, -1);
    vec<ll> d(N, INF);

    priority_queue<pll, vec<pll>, greater<pll>> q;

    q.emplace(0, t);
    d[t] = 0;

    while(!q.empty()) {
        auto [x, u] = q.top();
        q.pop();

        if(d[u] < x) continue;

        for(auto [v, w]: radj[u]) {
            if(d[v] > d[u] + w) {
                p[v] = u;
                d[v] = d[u] + w;

                q.emplace(d[v], v);
            }
        }
    }

    vec<vec<int>> radj2(N);
    for(int i = 0; i < N; ++i) {
        if(p[i] >= 0) {
            radj2[p[i]].emplace_back(i);
        }
    }

    vec<int> h(N);
    queue<int> r; r.emplace(t);
    while(!r.empty()) {
        int u = r.front(); r.pop();

        bool s = 1;
        for(auto [v, w]: adj[u]) {
            ll c = d[v] + w - d[u];

            if(s && v == p[u] && c == 0) {
                s = 0;
            } else {
                h[u] = merge(h[u], make_node(c, v));
            }
        }

        for(auto v: radj2[u]) {
            r.emplace(v);
            h[v] = h[u];
        }
    }

    vec<ll> ans = {d[s]};

    q.emplace(d[s] + T[h[s]].k, h[s]);
    while(!q.empty() && ans.size() < K) {
        auto [x, n] = q.top();
        q.pop();

        if(!n) continue;

        ans.emplace_back(x);

        q.emplace(x + T[h[T[n].v]].k, h[T[n].v]);
        q.emplace(x + T[T[n].l].k - T[n].k, T[n].l);
        q.emplace(x + T[T[n].r].k - T[n].k, T[n].r);
    }

    ans.resize(K, INF);
    for(auto x: ans) {
        cout << (x < INF ? x : -1) << lf;
    }
}
