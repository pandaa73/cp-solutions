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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

pair<vector<int>, long long> transaction(long long M);

void buy_souvenirs(int N, long long P0) {
    vector<ll> P(N, -1);
    vector<int> cnt(N);

    stack<pair<vector<int>, ll>> s; s.emplace((vector<int>){0}, P0);
    auto query = [&](ll x) -> void {
        auto [v, r] = transaction(x);

        for(auto i: v) {
            cnt[i] += 1;
        }

        s.emplace(v, x - r);
    };

    auto purge = [&](void) -> int {
        if(s.empty()) return 0;

        auto [v, x] = s.top();

        vector<int> u; ll y = x;
        for(auto i: v) {
            if(P[i] < 0) {
                u.emplace_back(i);
            } else y -= P[i];
        }

        if(x == y) return v.size();

        s.pop(); s.emplace(u, y);

        return u.size();
    };

    for(int i = N - 1; i >= 0; i--) {
        while(1) {
            int sz = purge();

            assert(sz > 0);

            const auto &[v, x] = s.top();

            if(sz > 1) {
                query(x / v.size());
            } else if(v[0] != i) {
                query(x - 1);
            } else break;
        }

        assert(s.top().fi.size() == 1);
        assert(s.top().fi[0] == i);

        P[i] = s.top().se; s.pop();
    }

    for(int i = 0; i < N; ++i) {
        for(; cnt[i] < i; ++cnt[i]) {
            transaction(P[i]);
        }
    }
}

#ifdef LOCAL
namespace {
const int CALLS_CNT_LIMIT = 10'000;

int calls_cnt;
int N;
std::vector<long long> P;
std::vector<int> Q;

void quit(const char* message) {
  printf("%s\n", message);
  exit(0);
}
} // namespace

std::pair<std::vector<int>, long long> transaction(long long M) {
  calls_cnt++;
  if (calls_cnt > CALLS_CNT_LIMIT)
    quit("Too many calls");
  if (M >= P[0] || M < P[N - 1])
    quit("Invalid argument");

  std::vector<int> L;
  long long R = M;
  for (int i = 0; i < N; i++) {
    if (R >= P[i]) {
      R -= P[i];
      Q[i]++;
      L.push_back(i);
    }
  }
  return {L, R};
}

int main() {
  assert(1 == scanf("%d", &N));
  P.resize(N);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%lld", &P[i]));
  fclose(stdin);

  Q.assign(N, 0);
  calls_cnt = 0;
  buy_souvenirs(N, P[0]);
  for (int i = 0; i < N; i++)
    printf("%s%d", i ? " " : "", Q[i]);
  printf("\n");
  fclose(stdout);

  return 0;
}
#endif
