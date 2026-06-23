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

void solve(void) {
    int N, K; cin >> N >> K;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    vec<int> f(K + 1);
    for(int i = 0; i < N; ++i) {
        f[V[i]] += 1;
    }

    int M = N;
    vec<int> on, tr, ev;
    for(int c = 1; c <= K; ++c) {
        if(f[c] == 1) {
            on.emplace_back(c);
            f[c] -= 1;
        } else if(f[c]&1) {
            tr.emplace_back(c);
            f[c] -= 3;
        }

        M -= f[c];
        ev.emplace_back(c);
    }

    if(on.size() > 1 || (on.size() + tr.size() && ~N&1)) {
        cout << "NO" << lf;
        return;
    }

    /* this makes it looks nicer :) */
    sort(all(tr));
    sort(all(ev));

    vec<int> v;
    if(on.size()) {
        M += 2;
        v.emplace_back(on[0]);
    }

    for(auto &x: tr) {
        v.emplace_back(x);
    }

    int m = M / 3;
    assert(m == v.size());
    assert(3 * m == M);

    vec<int> q(M);

    int a = 0, b = m/2, c = m - 1;
    for(int i = 0; i < m; ++i) {
        q[a] = q[b + m] = q[c + 2 * m] = v[i];

        a = (a + 1) % m;
        b = (b + 1) % m;
        c = (c + m - 2) % m;
    }

    vec<int> p(N);
    int i = 0;
    for(auto c: ev) {
        for(; f[c] > 0; f[c] -= 2, i += 1) {
            p[i] = p[N - i - 1] = c;
        }
    }

    i -= on.size();
    for(int j = on.size(); j < M - on.size(); ++j) {
        p[i + j] = q[j];
    }

    cout << "YES" << lf;
    for(auto x: p) {
        cout << x << " ";
    }

    cout << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
