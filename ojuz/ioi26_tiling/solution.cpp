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

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

int N, M;
vec<vec<bool>> G;
pii tl, tr, bl, br;

void init(int N, int M) {
    ::N = N, ::M = M;
    G = vector (N, vec<bool>(M));

    tl = {N - 1, M - 1};
    tr = {N - 1,     0};
    bl = {    0, M - 1};
    br = {    0,     0};
}

pair<int, int> receive_block(int TL, int TR, int BL, int BR) {
    pii ans = {-1, -1};

    if(TL == 0) {
        while(G[tl.fi][tl.se]) {
            tl.se -= 1;
            if(tl.se < 0) {
                tl.se = M - 1;
                tl.fi -= 1;
            }
        }

        ans = tl;
    } else if(TR == 0) {
        while(G[tr.fi][tr.se]) {
            tr.fi -= 1;
            if(tr.fi < 0) {
                tr.fi = N - 1;
                tr.se += 1;
            }
        }

        ans = tr;
    } else if(BL == 0) {
        while(G[bl.fi][bl.se]) {
            bl.fi += 1;
            if(bl.fi >= N) {
                bl.fi = 0;
                bl.se -= 1;
            }
        }

        ans = bl;
    } else if(BR == 0) {
        while(G[br.fi][br.se]) {
            br.se += 1;
            if(br.se >= M) {
                br.se = 0;
                br.fi += 1;
            }
        }

        ans = br;
    } else assert(0);

    G[ans.fi][ans.se] = 1;
    return {ans.fi * 2, ans.se * 2};
}

#ifdef LOCAL

int main() {
  int N, M;
  assert(2 == scanf("%d%d", &N, &M));

  std::vector<int> TL(N * M), TR(N * M), BL(N * M), BR(N * M);
  for (int k = 0; k < N * M; ++k) {
    assert(4 == scanf("%d%d%d%d", &TL[k], &TR[k], &BL[k], &BR[k]));
  }
  fclose(stdin);

  init(N, M);

  for (int k = 0; k < N * M; ++k) {
    auto [R, C] = receive_block(TL[k], TR[k], BL[k], BR[k]);
    printf("%d %d\n", R, C);
  }
  fclose(stdout);

  return 0;
}

#endif /* LOCAL */
