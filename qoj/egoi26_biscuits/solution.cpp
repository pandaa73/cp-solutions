#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << " " <<
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

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int M = 51;
constexpr int MAXN = 1 << 17;

struct SegTree {
    struct Node {
        Node(void): f(M) {}

        void update(int w) {
            for(int x = 0; x < M; ++x) {
                f[x] = abs(x - w);
            }
        }

        vec<int> f;
    };

    SegTree(const vec<int> &V): N(MAXN), T(2 * MAXN) {
        for(int i = 0; i < V.size(); ++i) {
            T[N + i].update(V[i]);
        }

        for(int i = N - 1; i > 0; i--) {
            pull(i);
        }
    }

    void pull(int n) {
        for(int x = 0; x < M; ++x) {
            T[n].f[x] = T[n << 1].f[T[n << 1 | 1].f[x]];
        }
    }

    void update(int n, int x) {
        n += N;
        T[n].update(x);
        for(n >>= 1; n > 0; n >>= 1) {
            pull(n);
        }
    }

    int value(void) {
        return T[1].f[0];
    }

    int N;
    int S;
    vec<Node> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N, Q; cin >> N >> Q;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    int S = accumulate(all(V), 0);
    SegTree st(V);

    cout << (S - st.value()) / 2 << lf;

    for(int qi = 0; qi < Q; ++qi) {
        int p, x; cin >> p >> x;

        S -= V[p];
        V[p] = x;
        S += V[p];

        st.update(p, x);

        cout << (S - st.value()) / 2 << lf;
    }
}
