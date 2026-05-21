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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T, N; cin >> T >> N;

    vec<int> V(N); for(auto &x: V) cin >> x;

    int l, r;
    vec<int> fq(T);

    for(r = N - 1; r >= 0; r--) {
        if(fq[V[r]]) break;

        fq[V[r]] += 1;
    }

    r += 1;

    int L = 0, R = r;
    for(l = 0; l < N; ++l) {
        while(fq[V[l]] && r < N) {
            fq[V[r]] -= 1;
            r += 1;
        }

        if(fq[V[l]]) break;

        fq[V[l]] += 1;

        if(R - L > r - l - 1) {
            L = l + 1, R = r;
        }
    }

    cout << L _ R - 1 << lf;
}
