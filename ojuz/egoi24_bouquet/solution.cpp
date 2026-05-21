#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

struct SegTree {
    SegTree(int N): N(N), st(2 * N) {}

    void update(int i, int x) {
        st[i += N] = x;

        for(i >>= 1; i > 0; i >>= 1)
            st[i] = max(st[i << 1], st[i << 1 | 1]);
    }

    int range_max(int l, int r) {
        int ans = 0;

        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans = max(ans, st[l++]);
            if(r&1) ans = max(ans, st[--r]);
        }

        return ans;
    }

    int N;
    vector<int> st;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    vector<int> L(N), R(N);
    for(int i = 0; i < N; ++i) {
        auto &l = L[i], &r = R[i];

        cin >> l >> r;

        l = max(0, i - l);
        r = min(i + r, N - 1);
    }


    SegTree dp(N);
    vector<vector<array<int, 2>>> psh(N);
    for(int i = 0; i < N; ++i) {
        int val = 1 + dp.range_max(0, L[i]);
        psh[R[i]].push_back({i, val});

        for(auto [v, x]: psh[i])
            dp.update(v, x);
    }

    cout << dp.range_max(0, N) << lf;
}
