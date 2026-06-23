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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; ll M; cin >> N >> M;

    vec<ll> V(N), W(N);
    for(int i = 0; i < N; ++i) {
        cin >> V[i] >> W[i];
    }

    vec<ll> kp(M + 1);
    for(int i = 0; i < N; ++i) {
        for(int j = M; j >= W[i]; j--) {
            kp[j] = max(kp[j], kp[j - W[i]] + V[i]);
        }
    }

    cout << kp[M] << lf;
}
