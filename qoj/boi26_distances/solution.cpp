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

constexpr int INF = 1e9;
constexpr int A = 5040;

int root(ll x) {
    int l = 0, r = INF;

    while(r - l > 1) {
        ll m = (l + r) / 2;

        if(m * m <= x) {
            l = m;
        } else {
            r = m;
        }
    }

    return l;
}

bool is_square(ll x) {
    int y = root(x);
    return x == (ll)y * y;
}

bool is_integer_dist(pii A, pii B) {
    pll C = {A.fi - B.fi, A.se - B.se};
    return is_square(C.fi * C.fi + C.se * C.se);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vec<pii> V;
    V.reserve(N);

    int sz = 100;
    for(; sz * (sz - 1) / 2 > K; sz--);

    vec<int> pos;
    pos.reserve(sz);
    pos.emplace_back(0);
    for(int b = 1; pos.size() < sz; ++b) {
        if(is_square((ll)A * A + (ll)b * b)) {
            pos.emplace_back(b);
        }
    }

    int x = -INF, y = -INF;

    int r = K - (sz * (sz - 1) / 2);

    for(int i = 0; i < r; ++i) {
        V.emplace_back(x, y + pos[i]);
    }

    if(r > 0) {
        V.emplace_back(x + A, y);
    }

    for(int i = r; i < sz; ++i) {
        V.emplace_back(x, y + pos[i] + 1);
    }

    for(x = INF, y = INF; V.size() < N; x -= 1, y -= 1) {
        V.emplace_back(x, y);
    }

    if constexpr(IS_DEBUG) {
        if(V.size() != N) {
            cout << "WA. Didn't return N points." << lf;
        }

        int cnt = 0;
        for(int i = 0; i < N - 1; ++i) {
            for(int j = i + 1; j < N; ++j) {
                cnt += is_integer_dist(V[i], V[j]);
            }
        }

        if(cnt != K) {
            cout << "WA. Found " << cnt << " pairs, expected " << K << ".\n";
        } else {
            cout << "OK. Found " << cnt << " pairs.\n";
        }
    }

    for(auto [x, y]: V) {
        cout << x _ y << lf;
    }
}
