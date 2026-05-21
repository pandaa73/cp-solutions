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
constexpr int MAXV = 1e6 + 1;

struct Line {
    Line(void): m(0), q(INF) {}
    Line(ll m, ll q): m(m), q(q) {}

    ll m, q;

    ll operator()(ll x) const {
        return m * x + q;
    }
};

struct LiChaoTree {
    struct Node {
        Node(void): l(0), r(0), line() {}

        int l, r;
        Line line;
    };

    LiChaoTree(int N): N(N), root(0), T(1) {}

    int make_node() {
        T.emplace_back();
        return T.size() - 1;
    }

    int insert(int n, int l, int r, Line line) {
        int m = (l + r) / 2;

        if(n == 0) n = make_node();

        if(T[n].line(m) > line(m)) {
            swap(T[n].line, line);
        }

        if(r - l <= 1) return n;

        if(T[n].line.m < line.m) {
            T[n].l = insert(T[n].l, l, m, line);
        } else {
            T[n].r = insert(T[n].r, m, r, line);
        }

        return n;
    }

    void insert(Line line) {
        root = insert(root, 0, N, line);
    }

    void insert(ll m, ll q) {
        insert(Line(m, q));
    }

    ll query(int n, int l, int r, int x) {
        ll mn = T[n].line(x);

        if(r - l <= 1) return mn;

        int m = (l + r) / 2;
        if(x < m) {
            return min(mn, query(T[n].l, l, m, x));
        } else {
            return min(mn, query(T[n].r, m, r, x));
        }
    }

    ll query(int x) {
        return query(root, 0, N, x);
    }

    int N;
    int root;
    vec<Node> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;
    vec<int> V(N);
    for(auto &x: V) cin >> x;
    V.emplace_back(0);

    vec<vec<ll>> dp(K + 1, vec<ll>(N + 1, INF));
    for(int i = 1; i <= N; ++i) {
        ll x = V[i - 1], y = V[0];
        dp[1][i] = (x - y) * (x - y);
    }

    for(int k = 2; k <= K; ++k) {
        LiChaoTree lct(MAXV);

        for(int i = 1; i <= N; ++i) {
            ll x = V[i - 1], y = V[i];
            lct.insert(-2 * y, dp[k - 1][i] + y * y);
            dp[k][i] = lct.query(x) + x * x;
        }
    }

    cout << dp[K][N] << lf;
}
