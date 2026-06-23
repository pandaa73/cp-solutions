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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; ll M; cin >> N >> M;

    vec<ll> V0(N), W0(N);
    for(int i = 0; i < N; ++i) {
        cin >> V0[i] >> W0[i];
    }

    vec<int> ord(N);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return W0[i] == W0[j] ? V0[i] > V0[j] : W0[i] < W0[j];
    });

    vec<ll> V(N), W(N);
    for(int i = 0; i < N; ++i) {
        V[i] = V0[ord[i]];
        W[i] = W0[ord[i]];
    }

    V0.clear();
    V0.shrink_to_fit();
    W0.clear();
    W0.shrink_to_fit();
    ord.clear();
    ord.shrink_to_fit();

    vec<int> L = {0};
    for(int i = 1; i < N; ++i) {
        if(W[i] > W[i - 1]) {
            L.emplace_back(i);
        }
    }

    const int K = L.size();
    L.emplace_back(N);

    W.emplace_back(INF);

    vec<ll> bcnt(K);
    for(int k = K - 1; k >= 0; k--) {
        bcnt[k] = M / W[L[k]];
        M %= W[L[k]];
    }

    infof("bcnt: {}", bcnt);

    ll ans = 0;
    vec<ll> p, q;
    for(int k = 0; k < K; ++k) {
        ll m = bcnt[k];

        infof("k = {} | W[k] = {} | m = {}", k, W[L[k]], m);

        for(int l = L[k]; l < L[k + 1]; ++l) {
            p.emplace_back(V[l]);
        }

        sort(rall(p));

        infof("p: {}", p);

        for(int i = 0; i < min(m, (ll)p.size()); ++i) {
            ans += p[i];
        }

        ll sz = W[L[k + 1]] / W[L[k]];
        for(ll i = m; i < p.size(); i += sz) {
            q.emplace_back(0);

            for(int j = 0; j < min(sz, (ll)p.size() - i); ++j) {
                q.back() += p[i + j];
            }
        }

        swap(p, q);
        q.clear();
    }

    cout << ans << lf;
}
