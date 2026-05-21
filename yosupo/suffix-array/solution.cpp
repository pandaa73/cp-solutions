#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr int ALPHABET = 256;

vector<int> suffix_array(const string &S) {
    const int N = S.size();

    vector<int> cnt(max(N, ALPHABET));
    vector<int> c(N), cn(N), p(N), pn(N);

    for(int i = 0; i < N; ++i) c[i] = S[i];

    int k = ALPHABET;

    for(int i = 0; i < N; ++i) cnt[c[i]] += 1;
    for(int i = 1; i < k; ++i) cnt[i] += cnt[i - 1];
    for(int i = N - 1; i >= 0; i--) p[--cnt[c[i]]] = i;

    for(int pow = 1; pow < N; pow <<= 1) {
        for(int i = 0; i < N; ++i) {
            pn[i] = p[i] - pow;
            if(pn[i] < 0) pn[i] += N;
        }

        fill(cnt.begin(), cnt.begin() + k, 0);

        for(int i = 0; i < N; ++i) cnt[c[i]] += 1;
        for(int i = 1; i < k; ++i) cnt[i] += cnt[i - 1];
        for(int i = N - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];

        k = 0;
        cn[p[0]] = 0;
        for(int i = 1; i < N; ++i) {
            k += (c[p[i]] != c[p[i - 1]])
                || (c[(p[i] + pow) % N] != c[(p[i - 1] + pow) % N]);

            cn[p[i]] = k;
        }

        k += 1;

        swap(c, cn);
    }

    return p;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string S; cin >> S;
    S.push_back('$');

    auto s = suffix_array(S);
    for(int i = 1; i < s.size(); ++i) {
        cout << s[i] << " ";
    }

    cout << lf;
}
