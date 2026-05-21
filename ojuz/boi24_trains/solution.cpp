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

constexpr int SQRT = 256;

int add(int a, int b) {
    int x = a + b;
    return x < MOD ? x : x - MOD;
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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vec<int> K(N), R(N);
    for(int i = 0; i < N; ++i) {
        cin >> K[i] >> R[i];

        if(K[i] >= N - i) K[i] = 0;
        if(K[i] == 0) continue;

        R[i] = min(R[i], (N - i - 1) / K[i]);
    }

    vec<vec<int>> dp(N, vec<int>(SQRT, -1));

    auto calc = [&](int i, int k, auto &&calc) -> int {
        if(i >= N) return 0;

        if(k < SQRT && dp[i][k] >= 0) return dp[i][k];

        int x = add(dp[i][0], calc(i + k, k, calc));

        if(k < SQRT) dp[i][k] = x;

        return x;
    };

    for(int i = N - 1; i >= 0; i--) {
        dp[i][0] = 1;
        if(K[i] == 0) continue;

        int l = i + K[i];
        int r = i + K[i] * (R[i] + 1);

        if(K[i] < SQRT) {
            calc(l, K[i], calc);

            int dpl = l < N ? dp[l][K[i]] : 0;
            int dpr = r < N ? dp[r][K[i]] : 0;

            chadd(dp[i][0], add(dpl, MOD - dpr));
        } else {
            for(; l < min(r, N); l += K[i]) {
                chadd(dp[i][0], dp[l][0]);
            }
        }
    }

    cout << dp[0][0] << lf;
}
