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

struct SegTree {
    struct Value {
        int lz;
        bool zr;

        int mx;
    };

    SegTree(int N): N(N), T(2 * N) {}

    void apply(int v, int x, bool zr) {
        if(zr) {
            T[v].lz = x;
            T[v].zr = 1;
            T[v].mx = x;
        } else {
            T[v].lz += x;
            T[v].mx += x;
        }
    }

    void push(int v) {
        if(v < N) {
            apply(v << 1, T[v].lz, T[v].zr);
            apply(v << 1 | 1, T[v].lz, T[v].zr);
        }

        T[v].lz = T[v].zr = 0;
    }

    void pull(int v) {
        if(v >= N) return;

        push(v);

        T[v].mx = max(T[v << 1].mx, T[v << 1 | 1].mx);
    }

    void build(int v) {
        for(; v > 0; v >>= 1) {
            pull(v);
        }
    }

    void propagate(int v) {
        for(int h = LOG; h > 0; h--) {
            push(v >> h);
        }
    }

    int get_max(void) {
        return T[1].mx;
    }

    void range_increment(int l, int r) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        propagate(l0), propagate(r0);
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, 1, 0);
            if(r&1) apply(--r, 1, 0);
        }

        build(l0), build(r0);
    }

    void range_clear(int l, int r) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        propagate(l0), propagate(r0);
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, 0, 1);
            if(r&1) apply(--r, 0, 1);
        }

        build(l0), build(r0);
    }

    int N;
    vector<Value> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vector<int> V; V.reserve(2 * Q);

    vector<vector<pii>> rg(N);
    for(int i = 0; i < Q; ++i) {
        int d, l, r; cin >> d >> l >> r;
        d -= 1;

        V.emplace_back(l);
        V.emplace_back(r);

        rg[d].emplace_back(l, r);
    }

    sort(all(V));
    V.resize(unique(all(V)) - V.begin());

    for(auto &v: rg) {
        for(auto &[l, r]: v) {
            l = lower_bound(all(V), l) - V.begin();
            r = lower_bound(all(V), r) - V.begin();
        }

        sort(all(v));
    }

    const int M = V.size();

    SegTree st(M);

    vector<int> ans(N);
    for(int i = N - 1; i >= 0; i--) {
        int q = 0;
        for(auto [l, r]: rg[i]) {
            if(q < l) st.range_clear(q, l);
            st.range_increment(l, r);

            q = r;
        }

        if(q < M) st.range_clear(q, M);

        ans[i] = st.get_max();
    }

    for(auto x: ans) {
        cout << x << lf;
    }
}
