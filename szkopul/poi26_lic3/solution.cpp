#include "liclib.h"

#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
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

// constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

constexpr int MAXQ = 1e6;

bool is_algosia;

int previous_bid;
int current_bid;

int queries = 0;

int move_partner(void) {
    if(queries > MAXQ) return -1;

    auto [x, e] = RuchPartnera();

    previous_bid = current_bid;
    current_bid = x;

    int ret = e ? -1 : (current_bid - previous_bid - 1);

    infof("... - Query {}: move_partner_{}() -> {} [({}, {})]",
        queries, is_algosia ? "algosia" : "bajtek", ret, x, e);

    return ret;
}

void bid(int x, bool e) {
    infof("... - Query {}: bid_{}({}, {}) [delta = {}]",
        queries, is_algosia ? "algosia" : "bajtek", x, e, x - current_bid - 1);

    queries += 1;
    Licytuj(x, e);

    previous_bid = current_bid;
    current_bid = x;
}

void bid_delta(int delta, bool e) {
    bid(current_bid + delta + 1, e);
}

void algosia(int M, int K, vector<int> V) {
    int N = V.size();

    int LOGN = 32 - __builtin_clz(N);
    int LOGM = 32 - __builtin_clz(M);

    vector<int> P(N), Q;
    iota(all(P), 0);
    Q.reserve(N);

    vector<bool> A(N), B(N);

    int x = 0;
    for(int lg = LOGM - 1; lg >= 0; lg--) {
        infof("===== Algosia - lg = {} - Q = {} =====", lg, queries);

        int pow = 1 << lg;
        int i = 0, j = 0;

        N = P.size();
        fill(A.begin(), A.begin() + N, 0);
        fill(B.begin(), B.begin() + N, 0);

        while(i < N || j < N) {
            int a = i;
            while(i < N && !(V[P[i]]&pow)) i += 1;
            bid_delta(i - a, 0);
            if(i < N) A[i++] = 1;

            int delta = move_partner();
            assert(delta >= 0);
            j += delta;
            if(j < N) B[j++] = 1;
        }

        for(i = 0; i < N; ++i) {
            j = P[i];

            infof("... A: i = {} | j = {} | A[i] = {} | B[i] = {}", i, j, A[i],
                B[i]);

            if(A[i] == B[i]) {
                infof("... -> A: pushing down [j = {}]", j);
                Q.emplace_back(j);
            } else if(A[i] == 0) {
                infof("... -> A: found min(A[j], B[j]) = {}", V[j]);
                x += V[j];
            }
        }

        swap(P, Q);
        Q.clear();
    }

    infof("A: found x = {}", x);

    int y = 0;
    for(int lg = 0; lg < LOGN + LOGM; ++lg) {
        bid_delta(0, 0);
        int delta = move_partner();
        assert(delta >= 0);

        lg += delta;
        if(lg < LOGN + LOGM) {
            infof("... A: found bit {} is set", lg);
            y += 1 << lg;
        }
    }

    infof("A: found y = {} | Q = {}", y, queries);

    bid(max((x + y)/K, current_bid + 1), 1);
}

void bajtek(int M, int K, vector<int> V) {
    int N = V.size();

    int LOGN = 32 - __builtin_clz(N);
    int LOGM = 32 - __builtin_clz(M);

    vector<int> P(N), Q;
    iota(all(P), 0);
    Q.reserve(N);

    vector<bool> A(N), B(N);

    int y = 0;
    for(int lg = LOGM - 1; lg >= 0; lg--) {
        infof("===== Bajtek - lg = {} - Q = {} =====", lg, queries);

        int pow = 1 << lg;
        int i = 0, j = 0;

        N = P.size();
        fill(A.begin(), A.begin() + N, 0);
        fill(B.begin(), B.begin() + N, 0);

        while(i < N || j < N) {
            int delta = move_partner();
            assert(delta >= 0);
            i += delta;
            if(i < N) A[i++] = 1;

            int b = j;
            while(j < N && !(V[P[j]]&pow)) j += 1;
            bid_delta(j - b, 0);
            if(j < N) B[j++] = 1;
        }

        for(i = 0; i < N; ++i) {
            j = P[i];

            infof("... B: i = {} | j = {} | A[i] = {} | B[i] = {}", i, j, A[i],
                B[i]);

            if(A[i] == B[i]) {
                infof("... -> B: pushing down [j = {}]", j);
                Q.emplace_back(j);
            } else if(B[i] == 0) {
                infof("... -> B: found min(A[j], B[j]) = {}", V[j]);
                y += V[j];
            }
        }

        swap(P, Q);
        Q.clear();
    }

    infof("B: found y = {}", y);

    int cnt = 0;
    for(int lg = 0; lg < LOGN + LOGM; ++lg) {
        int pow = 1 << lg;

        if(y&pow) {
            infof("... B: bit {} is set", lg);
            int delta = move_partner();
            assert(delta == 0);
            bid_delta(cnt, 0);
            cnt = 0;
        } else cnt += 1;
    }

    if(cnt > 0) {
        int delta = move_partner();
        assert(delta == 0);
        bid_delta(cnt, 0);
    }

    infof("B: transmitted y | Q = {}", queries);

    int delta = move_partner();
    assert(delta < 0);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int t = 1; t <= IleGier(); ++t) {
        previous_bid = current_bid = 0;
        is_algosia = KimJestem() == 0;

        (is_algosia ? algosia : bajtek)(DajM(), DajK(), DajCiag());
    }
}
