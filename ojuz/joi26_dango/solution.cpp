// NOTE: I, for some strange reason, wrote this using treap union, even though
//  a simple merge would've sufficed.

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

ll K = 1; // arbitrary non-zero value to initialize T[0]

struct Node {
    struct Value {
        Value(ll x): v(x / K), m(x % K) {}

        ll v, m;
    };

    struct Lazy {
        Lazy(void): z(0), v(0LL), m(0LL) {}
        Lazy(bool z, ll v, ll m): z(z), v(v), m(m) {}

        bool z;
        ll v, m;
    };

    Node(ll x = 0LL): pri(timmy_loves_gambling()), l(0), r(0), f(0), val(x) {}

    int pri;
    int l, r, f;

    Value val;
    Lazy lz;
};

vector<Node> T(1);

int make_node(ll x) {
    T.emplace_back(x);
    return T.size() - 1;
}

void apply_lazy(int v, const Node::Lazy &lz) {
    if(v) {
        if(lz.z) {
            T[v].val.v += lz.v;
            T[v].val.m = lz.m;

            T[v].lz.v += lz.v;
            T[v].lz.m = lz.m;
            T[v].lz.z = 1;
        } else {
            T[v].val.v += lz.v;
            T[v].val.m += lz.m;

            T[v].lz.v += lz.v;
            T[v].lz.m += lz.m;
        }
    }
}

void push(int v) {
    apply_lazy(T[v].l, T[v].lz);
    apply_lazy(T[v].r, T[v].lz);

    T[v].lz = Node::Lazy();
}

int merge(int l, int r) {
    if(!l || !r) return l ? l : r;

    push(l), push(r);

    if(T[l].pri > T[r].pri) {
        T[l].r = merge(T[l].r, r);
        return T[T[l].r].f = l;
    } else {
        T[r].l = merge(l, T[r].l);
        return T[T[r].l].f = r;
    }
}

pii split(int v, const ll x) {
    if(!v) return {};

    push(v);

    if(T[v].val.m < x) {
        auto [l, r] = split(T[v].r, x);
        T[v].r = l;
        T[l].f = v;
        T[v].f = 0;
        return {v, r};
    } else {
        auto [l, r] = split(T[v].l, x);
        T[v].l = r;
        T[r].f = v;
        T[v].f = 0;
        return {l, v};
    }
}

int unite(int l, int r) {
    if(!l || !r) return l ? l : r;
    if(T[l].pri < T[r].pri) swap(l, r);

    push(l), push(r);

    auto [rl, rr] = split(r, T[l].val.m);

    T[l].l = unite(T[l].l, rl);
    T[l].r = unite(T[l].r, rr);

    return T[T[l].l].f = T[T[l].r].f = l;
}

int insert(int v, int n) {
    auto [l, r] = split(v, T[n].val.m);

    return merge(l, merge(n, r));
}

int add(int v, const ll x) {
    infof("===== add({}, {}) =====", v, x);

    ll a = x / K;
    ll b = x % K;

    auto [l, r] = split(v, K - b);

    apply_lazy(l, Node::Lazy(0, a, b));
    apply_lazy(r, Node::Lazy(0, a + 1, b - K));

    return unite(l, r);
}

int remove(int v, const ll x) {
    infof("===== remove({}, {}) =====", v, x);

    auto [l, r] = split(v, x + 1);

    apply_lazy(l, Node::Lazy(1, 0, 0));
    apply_lazy(r, Node::Lazy(0, 0, -x));

    return merge(l, r);
}

void propagate(int v) {
    stack<int> s;
    while(v) {
        s.emplace(v);
        v = T[v].f;
    }

    while(!s.empty()) {
        push(s.top()); s.pop();
    }
}

void print_node(int v) {
    if constexpr(!IS_DEBUG) return;

    infof("----- Node {} -----", v);
    infof("(l, r) = ({}, {}) | f = {}", T[v].l, T[v].r, T[v].f);
    infof("val = {{v: {}, m: {}}}", T[v].val.v, T[v].val.m);
    infof(" lz = {{v: {}, m: {}, z: {}}}", T[v].lz.v, T[v].lz.m, T[v].lz.z);
}

void print(void) {
    if constexpr(!IS_DEBUG) return;

    infof("===== Printing Treap =====");
    infof("size = {}", T.size());
    for(int i = 0; i < T.size(); ++i) {
        print_node(i);
    }
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q >> K;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    vector<vector<pii>> Qs(N);
    for(int q = 0; q < Q; ++q) {
        int l, r; cin >> l >> r;

        l &= -2, r = (r-1)&-2;
        Qs[r].emplace_back(l, q);

        infof("... pushing query ({}, {})", l, r);
    }

    int v = 0;

    vector<ll> ans(Q);
    vector<int> node(N + 1);
    for(int r = 0; r < N; r += 2) {
        infof("======= Adding r = {} =======", r);

        v = add(v, V[r]);

        int n = make_node(V[r]);
        node[r] = n;

        infof("new node: {}", n);

        v = insert(v, n);

        infof("===== Queries r = {} =====", r);
        for(auto [l, q]: Qs[r]) {
            propagate(node[l]);
            ans[q] = T[node[l]].val.v;
            infof("({}, {}): node = {} | ans = {}", l, q, node[l],
                    T[node[l]].val.v);
        }

        print();

        if(r + 1 >= N) continue;
        infof("===== Removing r = {} =====", r + 1);

        v = remove(v, V[r + 1]);

        print();
    }

    for(auto x: ans) {
        cout << x << lf;
    }
}
