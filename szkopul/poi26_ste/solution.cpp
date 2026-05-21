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

using pl = pair<ll, ll>;
using pi = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

constexpr int MAXK = 1000;

constexpr int BASE = 26;
constexpr int SQUARE_SIZE = 970;
constexpr int IDENTIFIER_BITS = 11;
constexpr int CORRECTION_BITS_1 = 10;
constexpr int CORRECTION_BITS_2 = 9;
constexpr int BLOCK_SIZE_BITS = 127;
constexpr int BLOCK_SIZE_CHAR = 27;
constexpr int MAX_BLOCK_COUNT = 7408;

// Minimums: 970, 458, 458, 458, 458, 480, 480, 482, 484, 484, 485
const array<int, IDENTIFIER_BITS> EXPECTED_COUNT = {
    970, 458, 459, 460, 461, 480, 481, 482, 484, 485, 486
};

const map<int, int> EXPECTED_COUNT_MAP = {
    {970, 0}, {458, 1}, {459, 2}, {460, 3},
    {461, 4}, {480, 5}, {481, 6}, {482, 7},
    {484, 8}, {485, 9}, {486, 10}
};

using u128 = __uint128_t;

#define ord(c) (c - 'a')
#define chr(c) (c + 'a')
#define G(x, y) grid[P[x]][Q[y]]

vector<int> P, Q;
array<bitset<MAXK>, MAXK> grid;

void next(int &i, int &j) {
    j += 1;

    if(j == SQUARE_SIZE) {
        j -= SQUARE_SIZE;
        i += 1;
    }
}

int find_type(int x) {
    auto it = EXPECTED_COUNT_MAP.find(x);
    return it == EXPECTED_COUNT_MAP.end() ? -1 : it->se;
}

void write_message(const string &S) {
    const int N = S.size();

    int x = 0, y = 0;
    for(int i = 0; i < N; i += BLOCK_SIZE_CHAR) {
        u128 value = 0;

        for(int j = 0; j < BLOCK_SIZE_CHAR; ++j) {
            value = value * BASE + ord(S[i + BLOCK_SIZE_CHAR - j - 1]);
        }

        for(int j = 0; j < BLOCK_SIZE_BITS; ++j) {
            G(x, y) = value&1;
            value >>= 1;
            next(x, y);
        }
    }
}

string read_message(void) {
    string S(BLOCK_SIZE_CHAR * MAX_BLOCK_COUNT, 'a');

    int N = S.size();

    int x = 0, y = 0;
    for(int i = 0; i < N; i += BLOCK_SIZE_CHAR) {
        u128 value = 0;

        for(int j = 0; j < BLOCK_SIZE_BITS; ++j) {
            u128 pow = (u128)1 << j;
            value += pow * G(x, y);
            next(x, y);
        }

        for(int j = 0; j < BLOCK_SIZE_CHAR; ++j) {
            S[i + j] = chr(value % BASE);
            value /= BASE;
        }
    }

    // remove padding and terminal character
    for(N--; N > 0; N--) {
        if(S[N] == 'b') break;
    }

    S.resize(N);
    return S;
}

void first(const int K) {
    int N; cin >> N;

    string S; cin >> S;
    S += 'b'; // non-zero terminal character

    // pad to a multiple of BLOCK_SIZE_CHAR
    S.resize(N + BLOCK_SIZE_CHAR - (N % BLOCK_SIZE_CHAR), 'a');

    write_message(S);

    // write identifier bits
    vector<int> cnt(IDENTIFIER_BITS);
    for(int x = 0; x < SQUARE_SIZE; ++x) {
        int v = x + (1 << (IDENTIFIER_BITS - 1));
        int y = SQUARE_SIZE + IDENTIFIER_BITS - 1;
        while(v > 0) {
            if(v&1) {
                G(x, y) = G(y, x) = 1;
                cnt[y - SQUARE_SIZE] += 1;
            }

            y -= 1;
            v >>= 1;
        }
    }

    // write correction bits
    for(int j = 0; j < IDENTIFIER_BITS; ++j) {
        int y = SQUARE_SIZE + j;
        for(int i = 0; i < EXPECTED_COUNT[j] - cnt[j]; ++i) {
            int x = SQUARE_SIZE + IDENTIFIER_BITS + i;
            G(x, y) = G(y, x) = 1;
        }
    }

    for(int x = 0; x < SQUARE_SIZE; ++x) {
        int cnt = 0;
        for(int y = 0; y < MAXK; ++y) {
            cnt += G(x, y);
        }

        for(int i = 0; find_type(cnt) >= 0; ++i) {
            int y = SQUARE_SIZE + IDENTIFIER_BITS + i;
            G(x, y) = 1;
            cnt += 1;
        }
    }

    for(int y = 0; y < SQUARE_SIZE; ++y) {
        int cnt = 0;
        for(int x = 0; x < MAXK; ++x) {
            cnt += G(x, y);
        }

        for(int i = 0; find_type(cnt) >= 0; ++i) {
            int x = SQUARE_SIZE + IDENTIFIER_BITS + i;
            G(x, y) = 1;
            cnt += 1;
        }
    }

    // write correction bits for the correction bits

    for(int i = 0; i < CORRECTION_BITS_1; ++i) {
        int cnt_r = 0, cnt_c = 0;
        for(int j = 0; j < MAXK; ++j) {
            cnt_r += G(SQUARE_SIZE + IDENTIFIER_BITS + i, j);
            cnt_c += G(j, SQUARE_SIZE + IDENTIFIER_BITS + i);
        }

        for(int j = 0; find_type(cnt_r) >= 0; ++j) {
            int x = SQUARE_SIZE + IDENTIFIER_BITS + i;
            int y = SQUARE_SIZE + IDENTIFIER_BITS + CORRECTION_BITS_1 + j;

            G(x, y) = 1;
            cnt_r += 1;
        }

        for(int j = 0; find_type(cnt_c) >= 0; ++j) {
            int x = SQUARE_SIZE + IDENTIFIER_BITS + CORRECTION_BITS_1 + j;
            int y = SQUARE_SIZE + IDENTIFIER_BITS + i;

            G(x, y) = 1;
            cnt_c += 1;
        }
    }

    for(int i = 0; i < MAXK; ++i) {
        cout << grid[i] << lf;
    }
}

void second(const int K) {
    for(int i = 0; i < MAXK; ++i) {
        cin >> grid[i];
    }

    // un-permutate stuff, that is calculate P and Q
    vector<int> cnt_r(MAXK), cnt_c(MAXK);
    vector<int> bits_r(IDENTIFIER_BITS, -1), bits_c(IDENTIFIER_BITS, -1);
    for(int x = 0; x < MAXK; ++x) {
        for(int y = 0; y < MAXK; ++y) {
            cnt_r[x] += G(x, y);
            cnt_c[y] += G(x, y);
        }
    }

    for(int i = 0; i < MAXK; ++i) {
        int p = find_type(cnt_r[i]);
        int q = find_type(cnt_c[i]);

        if(p >= 0) bits_r[p] = i;
        if(q >= 0) bits_c[q] = i;
    }

    vector<int> new_P(MAXK), new_Q(MAXK);
    for(int i = 0; i < IDENTIFIER_BITS; ++i) {
        new_P[SQUARE_SIZE + i] = bits_r[i];
        new_Q[SQUARE_SIZE + i] = bits_c[i];
    }

    for(int i = 0; i < MAXK; ++i) {
        int p = 0, q = 0;
        for(int j = 0; j < IDENTIFIER_BITS; ++j) {
            p = (p << 1) + G(i, bits_c[j]);
            q = (q << 1) + G(bits_r[j], i);
        }

        constexpr int POW = 1 << (IDENTIFIER_BITS - 1);

        if(p&POW) new_P[p - POW] = i;
        if(q&POW) new_Q[q - POW] = i;
    }

    swap(P, new_P);
    swap(Q, new_Q);

    cout << read_message() << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int K; cin >> K;

    assert(K == MAXK);

    P.resize(MAXK); iota(all(P), 0);
    Q.resize(MAXK); iota(all(Q), 0);

    string R; cin >> R;
    (R[0] == 'e' ? first : second)(K);
}
