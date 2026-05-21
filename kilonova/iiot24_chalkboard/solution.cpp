#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>

template<typename... Args>
using vec = vector<Args...>;

#ifdef MARCO
constexpr bool IS_DEBUG = 1;
#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)
#else
constexpr bool IS_DEBUG = 0;
#define infor(fmt, ...)
#define infof(fmt, ...)
#endif

mt19937 timmy_loves_gambling(73);

constexpr int MOD = 1e9+7;
constexpr int MAXA = 1e6+1;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return (ll)a * b % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

struct SegTree {
    SegTree(int N): N(N), T(2 * N, 1) {}

    void point_add(int n, int k) {
        T[n += N] += k;

        for(n >>= 1; n > 0; n >>= 1) {
            T[n] = mul(T[n << 1], T[n << 1 | 1]);
        }
    }

    int range_mul(int l, int r) {
        int x = 1;

        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) chmul(x, T[l++]);
            if(r&1) chmul(x, T[--r]);
        }

        return x;
    }

    int N;
    vec<int> T;
};

vec<int> lp(MAXA);
vec<int> p;

vec<pii> factor(int x) {
    infor("factor({}) -> ", x);

    vec<pii> f;
    while(x > 1) {
        if(f.empty() || f.back().fi != lp[x]) {
            f.emplace_back(lp[x], 1);
        }  else {
            f.back().se += 1;
        }

        x /= lp[x];
    }

    infof("{}", f);

    return f;
};

void solve() {
    int Q; cin >> Q;

    SegTree st(MAXA);

    for(int q = 0; q < Q; ++q) {
        int t; cin >> t;

        if(t == 1) {
            int x; cin >> x;

            auto f = factor(x);

            for(auto [p, k]: f) {
                st.point_add(p, k);
            }
        } else if(t == 2) {
            int x; cin >> x;

            auto f = factor(x);

            for(auto [p, k]: f) {
                st.point_add(p, -k);
            }
        } else {
            int l, r; cin >> l >> r;
            r += 1;

            cout << st.range_mul(l, r) << lf;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i = 2; i < MAXA; ++i) {
        if(!lp[i]) {
            lp[i] = i;
            p.emplace_back(i);
        }

        for(int j = 0; j < p.size() && i * p[j] < MAXA; ++j) {
            if(p[j] > lp[i]) break;
            lp[i * p[j]] = p[j];
        }
    }

    int T = 1;
    while(T--) solve();
}
