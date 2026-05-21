#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#else

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    N = 1 << N;

    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int f; cin >> f;

        adj[f - 1].emplace_back(i);
    }

    vector<int> sz(N);
    auto dfs = [&](int v, auto &&dfs) -> void {
        sz[v] = 1;
        for(auto u: adj[v]) {
            dfs(u, dfs);
            sz[v] += sz[u];
        }
    };

    dfs(0, dfs);

    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(sz[0], 0);

    cout << N << lf;

    set<int> s = {0};
    while(!q.empty()) {
        auto [x, v] = q.top(); q.pop();

        cout << s.size();
        for(auto n: s) {
            cout << " " << n + 1;
        }
        cout << lf;

        s.erase(v);

        for(auto u: adj[v]) {
            s.emplace(u);
            q.emplace(sz[u], u);
        }
    }
}
