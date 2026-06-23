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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N; cin >> N;

    string S; cin >> S;

    if(S[0] == '-' || S[N - 1] == '+') {
        cout << "NO" << lf;
        return 0;
    }

    vec<int> P(N);
    int last = 0;
    for(int i = 1; i < N; ++i) {
        if(S[i] != '-') continue;

        P[i] = last;
        last = i;
    }

    last = N - 1;
    for(int i = N - 2; i >= 0; i--) {
        if(S[i] != '+') continue;

        P[i] = last;
        last = i;
    }

    cout << "YES" << lf;

    int n = 0;
    do {
        cout << n << " ";
        n = P[n];
    } while(n != 0);

    cout << lf;
}
