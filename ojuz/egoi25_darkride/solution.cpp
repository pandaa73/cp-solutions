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
constexpr int MAXN = 3e4+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    auto query = [&](string qry) -> int {
        cout << "?" _ qry << ff;

        int x; cin >> x;
        return x;
    };

    int x = 0;
    for(int pow = 1; pow < N; pow <<= 1) {
        string s(N, '0');
        for(int i = 0; i < N; ++i) {
            if(i&pow) s[i] = '1';
        }

        if(query(s)&1) {
            x |= pow;
        }

    }

    vec<int> qry, tmp; qry.reserve(N);
    int pow = 1 << (31 - __builtin_clz(x));
    for(int i = 0; i < N; ++i) {
        if(i&pow) {
            qry.emplace_back(i);
        }
    }

    while(qry.size() > 1) {
        int m = qry.size() / 2;

        vec<int> l = vec<int>(qry.begin(), qry.begin() + m);
        vec<int> r = vec<int>(qry.begin() + m, qry.end());

        string s(N, '0');
        for(int i = 0; i < m; ++i) {
            s[qry[i]] = '1';
        }

        if(query(s)&1) {
            tmp = l;
        } else {
            tmp = r;
        }

        qry.clear();
        swap(qry, tmp);
    }

    int p = qry[0];
    int q = p ^ x;

    cout << "!" _ p _ q << ff;
}
