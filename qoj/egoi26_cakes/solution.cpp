#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

constexpr ll INF = 1e18;

constexpr int ROOT = 512;
constexpr int MAXM = ROOT * ROOT;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    int mx = *max_element(all(V));

    vec<ll> lo(MAXM), hi(MAXM);
    for(int t = 1; t <= mx; ++t) {
        lo[t] = (mx + t - 1) / t;

        if(t < ROOT) {
            for(int i = 0; i < N; ++i) {
                int x = V[i] / t;
                hi[t] += x;
                hi[t + 1] -= x;
            }
        }
    }

    for(int k = 1; k <= ROOT; ++k) {
        for(int i = 0; i < N; ++i) {
            int l = max(ROOT, 1 + V[i] / (k + 1));
            int r = max(l, 1 + V[i] / k);

            hi[l] += k;
            hi[r] -= k;
        }
    }

    hi[0] = 1; // now hi is excluded
    for(int i = 1; i < MAXM; ++i) {
        hi[i] += hi[i - 1];
    }

    vec<pll> rg;
    for(int t = 1; t <= mx; ++t) {
        if(lo[t] > hi[t]) continue;

        if(rg.empty() || rg.back().fi > hi[t]) {
            rg.emplace_back(lo[t], hi[t]);
        } else {
            rg.back().fi = lo[t];
            assert(hi[t] <= rg.back().se);
        }
    }

    map<ll, ll> m;
    for(auto [l, r]: rg) {
        m[r] = l;
    }

    for(int q = 0; q < Q; ++q) {
        ll K; cin >> K;

        auto it = m.upper_bound(K);

        if(it == m.end() || it->se > K) {
            cout << "NO" << lf;
        } else {
            cout << "YES" << lf;
        }
    }
}
