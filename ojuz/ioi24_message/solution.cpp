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

constexpr int LOG = 4;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

vector<bool> send_packet(vector<bool> A);

constexpr int N = 31;
constexpr int C = 16;
constexpr int Q = 66;
constexpr int SZ = 1025;

void send_message(vector<bool> M, vector<bool> C) {
    reverse(all(M));

    M.emplace_back(1);
    M.resize(SZ, 0);

    reverse(all(M));

    int p = 0;
    vec<vec<bool>> P(Q, vec<bool>(N));
    for(int i = 0; i < N; ++i) {
        if(C[i]) continue;

        int j = 0;

        for(; C[(i + j + 1) % N] == 1; ++j) {
            P[j][i] = 1;
        }

        for(++j; j < Q; ++j) {
            P[j][i] = M[p++];
        }
    }

    for(const auto &packet: P) {
        (void)send_packet(packet);
    }
}

vector<bool> receive_message(vector<vector<bool>> R) {
    vec<bool> S; S.reserve(SZ);

    vec<int> E(N);
    for(int i = 0; i < N; ++i) {
        int j = 0;

        while(j < Q && R[j++][i]);

        E[i] = j;
    }

    vec<int> cyc; cyc.reserve(C);
    for(int i = 0; i < N; ++i) {
        vec<bool> vis(N);

        for(int j = i; !vis[j]; j = (j + E[j]) % N) {
            vis[j] = 1;
        }

        if(accumulate(all(vis), 0) != C) continue;

        for(int j = 0; j < N; ++j) {
            if(vis[j]) cyc.emplace_back(j);
        }

        break;
    }

    bool ok = 0;
    for(auto i: cyc) {
        for(; E[i] < Q; ++E[i]) {
            if(!ok) {
                ok = R[E[i]][i];
            } else S.emplace_back(R[E[i]][i]);
        }
    }

    return S;
}

#ifdef LOCAL
namespace {
const int PACKET_SIZE = 31;
const int CALLS_CNT_LIMIT = 100;

int calls_cnt;
std::vector<bool> C(PACKET_SIZE);
std::vector<std::vector<bool>> R;

void quit(const char* message) {
  printf("%s\n", message);
  exit(0);
}

void run_scenario() {
  R.clear();
  calls_cnt = 0;

  int S;
  assert(1 == scanf("%d", &S));
  std::vector<bool> M(S);
  for (int i = 0; i < S; i++) {
    int bit;
    assert(1 == scanf("%d", &bit));
    assert((bit == 0) || (bit == 1));
    M[i] = bit;
  }

  for (int i = 0; i < PACKET_SIZE; i++) {
    int bit;
    assert(1 == scanf("%d", &bit));
    assert((bit == 0) || (bit == 1));
    C[i] = bit;
  }

  send_message(M, C);
  std::vector<bool> D = receive_message(R);

  int K = (int)R.size();
  int L = (int)D.size();
  printf("%d %d\n", K, L);
  for (int i = 0; i < L; i++)
    printf("%s%d", (i == 0 ? "" : " "), (D[i] ? 1 : 0));
  printf("\n");
}

std::vector<bool> taint(const std::vector<bool>& A) {
  std::vector<bool> B = A;
  for (int i = 0; i < PACKET_SIZE; i++)
    if (C[i] == 1) {
      B[i] = timmy_loves_gambling()&1;
    }
  return B;
}

} // namespace

std::vector<bool> send_packet(std::vector<bool> A) {
  calls_cnt++;
  if (calls_cnt > CALLS_CNT_LIMIT)
    quit("Too many calls");
  if ((int)A.size() != PACKET_SIZE)
    quit("Invalid argument");

  std::vector<bool> B = taint(A);
  R.push_back(B);
  return B;
}

int main() {
  int T;
  assert(1 == scanf("%d", &T));
  for (int i = 1; i <= T; i++)
    run_scenario();
}
#endif
