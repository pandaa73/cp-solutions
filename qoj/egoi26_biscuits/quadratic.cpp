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
#define infof(fmt, ...) dp { println(stderr, fmt, ##__VA_ARGS__); } while(0)

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

constexpr int INF = 1e9;

int solve(int N, const vec<int> &V) {
    int mx1 = V[0], mx2 = 0;

    for(int i = 0; i < N; ++i) {
        int x = mx2 + V[i + 1];

        if(x > mx2) mx2 = x;
        if(mx2 > mx1) swap(mx1, mx2);
    }

    return mx2;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N, Q; cin >> N >> Q;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    V.emplace_back(0);

    reverse(all(V));

    cout << solve(N, V) << lf;
    for(int q = 0; q < Q; ++q) {
        int p, x; cin >> p >> x;
        V[N - p] = x;
        cout << solve(N, V) << lf;
    }
}
