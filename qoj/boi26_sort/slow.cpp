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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    vec<int> ord(N);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return V[i] == V[j] ? i < j : V[i] < V[j];
    });

    vec<int> dro(N);
    for(int i = 0; i < N; ++i) {
        dro[ord[i]] = i;
    }

    vec<int> p(N), pfx(N), sfx(N), pfx1(N), sfx1(N);

    for(int i = 0; i < N; ++i) {
        int j = N - i - 1;

        int li = i;
        int ri = max(li, dro[i]);

        pfx1[li] += 1;
        pfx1[ri] -= 1;

        int rj = j;
        int lj = min(rj, dro[j]);

        sfx1[rj] += 1;
        sfx1[lj] -= 1;

        infof("pfx1: {}: [{}, {})", i, li, ri);
        infof("sfx1: {}: [{}, {})", j, lj, rj);
    }

    p[0] = -1;
    pfx[0] = ord[0];
    sfx[N - 1] = ord[N - 1];
    for(int i = 1; i < N; ++i) {
        int j = N - i - 1;

        if(V[i] == V[ord[i]]) {
            p[i] = p[i - 1];
        } else {
            p[i] = i - 1;
        }

        pfx[i] = max(ord[i], pfx[i - 1]);
        sfx[j] = min(ord[j], sfx[j + 1]);
        pfx1[i] += pfx1[i - 1];
        sfx1[j] += sfx1[j + 1];
    }

    vec<bool> pfxs(N), sfxs(N);
    pfxs[0] = dro[0] == 0;
    sfxs[N - 1] = dro[N - 1] == N - 1;
    for(int i = 1; i < N; ++i) {
        int j = N - i - 1;

        pfxs[i] = pfxs[i - 1] & (dro[i] == i);
        sfxs[j] = sfxs[j + 1] & (dro[j] == j);
    }

    infof(" ord: {}", ord);
    infof(" dro: {}", dro);
    infof("   p: {}", p);
    infof(" pfx: {}", pfx);
    infof(" sfx: {}", sfx);
    infof("pfx1: {}", pfx1);
    infof("sfx1: {}", sfx1);
    infof("pfxs: {}", pfxs);
    infof("sfxs: {}", sfxs);

    bool zero = is_sorted(all(V));

    for(int qi = 0; qi < Q; ++qi) {
        infof("===== qi = {} =====", qi);

        int a, b; cin >> a >> b;

        infof("a = {} | b = {}", a, b);

        if(zero) {
            cout << 0 << lf;
            continue;
        }

        if(max(a, b) == N) {
            cout << 1 << lf;
            continue;
        }

        if(a + b > N) {
            assert(a < N && b < N);

            int x = pfx1[N - b - 1];
            int y = sfx1[a];

            int k = a + b - N;

            infof("x = {} | y = {} | k = {}", x, y, k);

            int real_ans = INF;
            /* solve with x */
            if(x == 0) {
                int ans = 0;
                ans += 1 - pfxs[N - b - 1];
                ans += 1 - sfxs[a];
                ans = max(1, ans);
                real_ans = min(real_ans, ans);
            } else {
                int ans = 2 * ((x + k - 1) / k);

                int sz = x % k;
                if(sz == 0 && x > 0) sz = k;

                vec<int> pos;
                for(int i = 0; i < N - b; ++i) {
                    if(dro[i] >= N - b) {
                        pos.emplace_back(i);
                    }
                }

                sort(all(pos), [&](int i, int j) -> bool {
                    return dro[i] < dro[j];
                });

                infof("... pos_x: {}", pos);

                assert(pos.size() >= sz);

                if(dro[pos[sz - 1]] > a - 1) {
                    ans += 1;
                }

                real_ans = min(real_ans, ans);
            }

            /* solve with y */
            if(y == 0) {
                int ans = 0;
                ans += 1 - pfxs[N - b - 1];
                ans += 1 - sfxs[a];
                ans = max(1, ans);
                real_ans = min(real_ans, ans);
            } else {
                int ans = 2 * ((y + k - 1) / k);

                int sz = y % k;
                if(sz == 0) sz = k;

                vec<int> pos;
                for(int i = N - 1; i > a - 1; i--) {
                    if(dro[i] <= a - 1) {
                        pos.emplace_back(i);
                    }
                }

                sort(all(pos), [&](int i, int j) -> bool {
                    return dro[i] > dro[j];
                });

                infof("... pos_y: {}", pos);

                assert(pos.size() >= sz);

                if(dro[pos[sz - 1]] < N - b) {
                    ans += 1;
                }

                real_ans = min(real_ans, ans);
            }

            cout << real_ans << lf;
        } else {
            if(p[N - b - 1] > p[a] || pfx[a - 1] > a - 1
                    || sfx[N - b] < N - b) {
                cout << -1 << lf;
            } else {
                int x = 0;
                if(p[a - 1] > -1) x += 1;
                if(p[N - 1] > N - b - 1) x += 1;

                cout << x << lf;
            }
        }
    }
}
