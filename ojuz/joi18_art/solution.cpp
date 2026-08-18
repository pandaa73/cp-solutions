#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

#endif /* DEBUG */

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

    int N; cin >> N;

    vec<ll> A(N), B(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }

    vec<int> ord(N);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return A[i] < A[j];
    });

    vec<ll> px(N + 1);
    for(int i = 0; i < N; ++i) {
        px[i + 1] = px[i] + B[ord[i]];
    }

    vec<ll> sx(N + 1);
    sx[N] = px[N] - A[ord[N - 1]];
    for(int i = N - 1; i > 0; i--) {
        sx[i] = max(px[i] - A[ord[i - 1]], sx[i + 1]);
    }

    ll mx = -INF;
    for(int i = 0; i < N; ++i) {
        mx = max(mx, sx[i + 1] - px[i] + A[ord[i]]);
    }

    cout << mx << lf;
}
