#include <bits/stdc++.h>
#include <regex>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 2e5+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<vector<int>> stations(N);
    for(int i = 0; i < M; ++i) {
        int o; cin >> o;

        stations[o - 1].push_back(i);
    }

    vector<ll> target(N);
    for(auto &x: target) cin >> x;

    int Q; cin >> Q;
    vector<array<ll, 3>> pred(Q);
    for(auto &[l, r, w]: pred)
        cin >> l >> r >> w;

    const int H = 32 - __builtin_clz(M - 1); /* log2 rounded up */

    int K = 0;
    vector<ll> bit(M + 1);

    auto add = [&](int i, ll x) -> void {
        for(++i; i <= M; i += i&(-i))
            bit[i] += x;
    };

    auto ft_add = [&](int l, int r, ll x) -> void {
        add(l, x), add(r, -x);
    };

    auto ft_qry = [&](int i) -> ll {
        ll sum = 0;

        for(++i; i > 0; i -= i&(-i))
            sum += bit[i];

        return sum;
    };

    vector<int> ans(N);
    auto search = [&](int l, int r, vector<int> &q, auto &&search) -> void {
        if(r - l <= 1) {
            for(auto u: q)
                ans[u] = l == Q ? -1 : l + 1;

            return;
        }

        int m = (l + r) / 2;

        while(K < m) {
            auto &[ql, qr, w] = pred[K++];

            if(ql > qr) {
                ft_add(0, qr, w);
                ft_add(ql - 1, M, w);
            } else ft_add(ql - 1, qr, w);
        }

        while(K > m) {
            auto &[ql, qr, w] = pred[--K];

            if(ql > qr) {
                ft_add(0, qr, -w);
                ft_add(ql - 1, M, -w);
            } else ft_add(ql - 1, qr, -w);
        }

        vector<int> left, right;
        for(auto u: q) {
            ll sum = 0;

            for(auto v: stations[u]) {
                sum += ft_qry(v);
                if(sum >= target[u]) break;
            }

            if(sum >= target[u])
                left.push_back(u);
            else right.push_back(u);
        }

        if(!left.empty()) search(l, m, left, search);
        if(!right.empty()) search(m, r, right, search);
    };

    vector<int> start(N); iota(all(start), 0);
    search(0, Q + 1, start, search);

    for(auto &x: ans) {
        if(x >= 0)
            cout << x << lf;
        else cout << "NIE" << lf;
    }
}
