#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

    int N; cin >> N;

    vec<pii> V(N);
    for(auto &[x, y]: V) {
        cin >> x >> y;
    }

    array<map<int, int>, 4> T;

    auto push = [&](int n) -> void {
        T[0].emplace(+V[n].fi, n);
        T[1].emplace(-V[n].se, n);
        T[2].emplace(-V[n].fi, n);
        T[3].emplace(+V[n].se, n);
    };

    auto pop = [&](int n) -> void {
        T[0].erase(+V[n].fi);
        T[1].erase(-V[n].se);
        T[2].erase(-V[n].fi);
        T[3].erase(+V[n].se);
    };

    auto next = [&](int d) -> int {
        return T[d].empty() ? N : T[d].begin()->se;
    };

    for(int i = 0; i < N; ++i) {
        push(i);
    }

    vec<pii> spiral, left, right;

    pii last = {0, 0};
    auto rec = [&](const int n, const int d, auto &&rec) -> int {
        if(n == N) return -1;
        if(last == V[n]) return n;

        while(true) {
            push(n);
            last = V[n];

            int e = (d + 1) % 4;
            int m = next(e);

            pop(n);

            int ret = rec(m, e, rec);

            if(T[e].empty()) ret = -1;

            if(ret == n) {
                (d&1 ? right : left).emplace_back(V[n]);

                return -2;
            } else if(ret != -2) {
                spiral.emplace_back(V[n]);

                return ret;
            }
        }
    };

    vec<pii> line;

    auto fix = [&](void) -> void {
        const int m = line.size();
        if(m < 3) return;

        if(line[m - 3].fi == line[m - 2].fi
                && line[m - 2].fi == line[m - 1].fi) {
            if(line[m - 3].se <= line[m - 2].se
                    && line[m - 2].se <= line[m - 1].se) {
                line[m - 2].se = line[m - 1].se;
                line.pop_back();
            } else if(line[m - 3].se >= line[m - 2].se
                    && line[m - 2].se >= line[m - 1].se) {
                line[m - 2].se = line[m - 1].se;
                line.pop_back();
            }
        } else if(line[m - 3].se == line[m - 2].se
                && line[m - 2].se == line[m - 1].se) {
            if(line[m - 3].fi <= line[m - 2].fi
                    && line[m - 2].fi <= line[m - 1].fi) {
                line[m - 2].fi = line[m - 1].fi;
                line.pop_back();
            } else if(line[m - 3].fi >= line[m - 2].fi
                    && line[m - 2].fi >= line[m - 1].fi) {
                line[m - 2].fi = line[m - 1].fi;
                line.pop_back();
            }
        }
    };

    auto solve_spiral = [&](void) -> void {
        const int n = spiral.size();
        const int m = line.size();

        if(n == 0) return;

        if(line.empty()) {
            line.emplace_back(spiral[0].fi, 0);
        } else if(spiral[0].fi <= line[m - 1].fi
                && line[m - 1].fi < line[m - 2].fi) {
            line[m - 1].fi = spiral[0].fi;
        } else if(spiral[0].fi >= line[m - 1].fi
                && line[m - 1].fi > line[m - 2].fi) {
            line[m - 1].fi = spiral[0].fi;
        } else if(spiral[0].se <= line[m - 1].se
                && line[m - 1].se < line[m - 2].se) {
            line[m - 1].se = spiral[0].se;
        } else if(spiral[0].se >= line[m - 1].se
                && line[m - 1].se > line[m - 2].se) {
            line[m - 1].se = spiral[0].se;
        } else {
            line.emplace_back(spiral[0].fi, line[m - 1].se);
        }

        last = spiral[0];
        line.emplace_back(spiral[0]);
        fix();

        if(n == 1) return;

        for(int i = 0; i < n; ++i) {
            const int m = line.size();
            const int d = i % 4;

            auto [x, y] = line.back();

            if(d&1) {
                y = spiral[i].se;
            } else {
                x = spiral[i].fi;
            }

            last = spiral[i];
            line.emplace_back(x, y);
            fix();
        }

        line.emplace_back(last);
        fix();
    };

    auto solve_left = [&](void) -> void {
        const int n = left.size();
        const int m = line.size();

        if(n == 0) return;

        if(line.empty()) {
            line.emplace_back(0, left[0].se);
        } else if(left[0].fi <= line[m - 1].fi
                && line[m - 1].fi < line[m - 2].fi) {
            line[m - 1].fi = left[0].fi;
        } else if(left[0].fi >= line[m - 1].fi
                && line[m - 1].fi > line[m - 2].fi) {
            line[m - 1].fi = left[0].fi;
        } else if(left[0].se <= line[m - 1].se
                && line[m - 1].se < line[m - 2].se) {
            line[m - 1].se = left[0].se;
        } else if(left[0].se >= line[m - 1].se
                && line[m - 1].se > line[m - 2].se) {
            line[m - 1].se = left[0].se;
        } else {
            line.emplace_back(line[m - 1].fi, left[0].se);
        }

        last = left[0];
        line.emplace_back(left[0]);
        fix();

        if(n == 1) return;

        for(int i = 1; i < n; ++i) {
            const int m = line.size();
            auto [x, y] = line.back();

            if((i&1) == (n&1)) {
                x = left[i].fi;
            } else {
                y = left[i].se;
            }

            last = left[i];
            line.emplace_back(x, y);
            fix();
        }

        line.emplace_back(last);
        fix();
    };

    auto solve_right = [&](void) -> void {
        const int n = right.size();
        const int m = line.size();

        if(n == 0) return;

        if(line.empty()) {
            line.emplace_back(0, right[0].se);
        } else if(right[0].fi <= line[m - 1].fi
                && line[m - 1].fi < line[m - 2].fi) {
            line[m - 1].fi = right[0].fi;
        } else if(right[0].fi >= line[m - 1].fi
                && line[m - 1].fi > line[m - 2].fi) {
            line[m - 1].fi = right[0].fi;
        } else if(right[0].se <= line[m - 1].se
                && line[m - 1].se < line[m - 2].se) {
            line[m - 1].se = right[0].se;
        } else if(right[0].se >= line[m - 1].se
                && line[m - 1].se > line[m - 2].se) {
            line[m - 1].se = right[0].se;
        } else {
            line.emplace_back(line[m - 1].fi, right[0].se);
        }

        last = right[0];
        line.emplace_back(right[0]);
        fix();

        if(n == 1) return;

        for(int i = 1; i < n; ++i) {
            const int m = line.size();
            auto [x, y] = line.back();

            if((i&1) == (n&1)) {
                x = right[i].fi;
            } else {
                y = right[i].se;
            }

            last = right[i];
            line.emplace_back(x, y);
            fix();
        }

        line.emplace_back(last);
        fix();
    };

    vec<pii> ans;
    auto run = [&](void) -> void {
        vec<int> P(3);
        iota(all(P), 0);

        do {
            last = {0, 0};
            line.clear();

            for(auto t: P) {
                switch(t) {
                    case 0: solve_spiral(); break;
                    case 1:   solve_left(); break;
                    case 2:  solve_right(); break;
                }
            }

            if(ans.empty() || line.size() < ans.size()) {
                swap(ans, line);
            }
        } while(next_permutation(all(P)));
    };

    while(rec(next(0), 0, rec) != -1);

    reverse(all(spiral));
    sort(all(left));
    sort(rall(right));

    run();

    reverse(all(left));
    reverse(all(right));

    run();

    cout << ans.size() << lf;
    for(auto [x, y]: ans) {
        cout << x _ y << lf;
    }
}
