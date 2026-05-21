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

#define NOT(x, m) ((~x)&(m-1))

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int K, Q; cin >> K >> Q;

    string S; cin >> S;

    const int N = 1 << K;

    vec<ll> V(N), dp(N), pd(N);
    for(int i = 0; i < N; ++i) {
        V[i] = S[i] - '0';
        dp[i] = V[i];
        pd[NOT(i, N)] = V[i];
    }

    for(int k = 0; k < K; ++k) {
        const int pow = 1 << k;
        for(int x = N - 1; x >= 0; x--) {
            if(x & pow) {
                dp[x] += dp[x ^ pow];
                pd[x] += pd[x ^ pow];
            }
        }
    }

    // solve in O(2^#{0})
    auto solve_a = [&](string T) -> ll {
        int m = 0, y = 0;
        for(int k = 0; k < K; ++k) {
            const int pow = 1 << k;

            if(T[k] == '1') {
                m |= pow;
            } else if(T[k] == '?') {
                y |= pow;
            }
        }

        const int q = __builtin_popcount(m);

        ll ans = q&1 ? -dp[y] : dp[y];
        for(int x = m; x > 0; x = (x-1)&m) {
            int p = __builtin_popcount(x);

            ans += (q-p)&1 ? -dp[x | y] : dp[x | y];
        }

        return ans;
    };

    // solve in O(2^#{1})
    auto solve_b = [&](string T) -> ll {
        for(auto &c: T) {
            if(c != '?') c ^= 1;
        }

        swap(dp, pd);
        ll x = solve_a(T);
        swap(dp, pd);

        return x;
    };

    // solve in O(2^#{?})
    auto solve_c = [&](string T) -> ll {
        int m = 0, y = 0;
        for(int k = 0; k < K; ++k) {
            const int pow = 1 << k;

            if(T[k] == '?') {
                m |= pow;
            } else if(T[k] == '1') {
                y |= pow;
            }
        }

        ll ans = V[y];
        for(int x = m; x > 0; x = (x-1)&m) {
            ans += V[x | y];
        }

        return ans;
    };

    for(int q = 0; q < Q; ++q) {
        string T; cin >> T;
        reverse(all(T));

        int a = 0, b = 0, c = 0;
        for(auto k: T) {
            a += k == '1';
            b += k == '0';
            c += k == '?';
        }

        int m = min({a, b, c});

        ll x = -1;
        if(m == a) {
            x = solve_a(T);
        } else if(m == b) {
            x = solve_b(T);
        } else {
            x = solve_c(T);
        }

        cout << x << lf;
    }
}
