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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    vec<int> c(N), t(N, -1);
    for(int q = 0; q < Q; ++q) {
        char type; cin >> type;
        int r; cin >> r;

        int x = V[r];
        if(type == '!') {
            cin >> x;
        }

        if(r > 0) {
            c[r] += (q - t[r]) * (V[r] < V[r - 1]);
            t[r] = q;
        }

        if(r < N - 1) {
            c[r + 1] += (q - t[r + 1]) * (V[r + 1] < V[r]);
            t[r + 1] = q;
        }

        V[r] = x;

        if(type == '?') {
            cout << c[r] << lf;
        }
    }
}
