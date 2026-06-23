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

struct TreeHasher {
    TreeHasher(void): id(0) {
        m.emplace(vec<int>(), id++);
    }

    int hash(vec<int> &T) {
        sort(all(T));

        if(!m.count(T)) {
            m[T] = id++;
        }

        return m[T];
    }

    int id;
    map<vec<int>, int> m;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vec<vec<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    TreeHasher H;

    vec<ll> szs(N);
    vec<int> p(N), h(N), sz(N), cnt(N);
    auto dfs = [&](int u, auto &&dfs) -> void {
        sz[u] = 1;
        vec<int> T;
        for(auto v: adj[u]) {
            if(v == p[u]) continue;

            p[v] = u;
            dfs(v, dfs);

            sz[u] += sz[v];
            szs[u] += szs[v];
            T.emplace_back(h[v]);
        }

        szs[u] += sz[u];
        h[u] = H.hash(T);
        cnt[h[u]] += 1;
    };

    p[0] = -1;
    dfs(0, dfs);

    infof("  p: {}", p);
    infof("  h: {}", h);
    infof(" sz: {}", sz);
    infof("cnt: {}", cnt);

    vec<int> ch;
    vec<ll> chsz(N);
    auto dfs2 = [&](int u, int d, auto &&dfs2) -> void {
        ch.emplace_back(h[u]);
        chsz[h[u]] += d;

        for(auto v: adj[u]) {
            if(v == p[u]) continue;

            dfs2(v, d + 1, dfs2);
        }
    };

    int ans = 0;

    vec<bool> vis(N);
    for(int i = 0; i < N; ++i) {
        if(szs[i] != N - M || vis[h[i]]) continue;
        vis[h[i]] = 1;

        infof("===== i = {} | h = {} =====", i, h[i]);

        dfs2(i, 1, dfs2);

        infof("  ch: {}", ch);
        infof("chsz: {}", chsz);

        bool ok = 1;
        for(auto x: ch) {
            ok &= cnt[x] >= chsz[x];
        }

        for(auto x: ch) {
            chsz[x] = 0;
        }

        ch.clear();

        ans += ok;
    }

    cout << ans << lf;
}
