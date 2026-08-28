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

int add_and(vector<int> Ns);
int add_or(vector<int> Ns);
int add_xor(vector<int> Ns);
int add_not(int N);

constexpr int LOG = 8;

int H, W;
int ZERO, ONE;

int read(int x, int y) {
    return y * W + x;
}

void setup(int H, int W) {
    ::H = H;
    ::W = W;

    int x = add_xor({0, 1});
    ZERO = add_and({0, 1, 2});
    ONE = add_not(ZERO);
}

pii add_adder(int a, int b) {
    int lo = add_xor({a, b});
    int hi = add_and({a, b});

    return {lo, hi};
}

void construct_network(int H, int W, int K) {
    setup(H, W);

    vec<int> cols(W), px(W);
    for(int x = 0; x < W; ++x) {
        vec<int> v(H);
        for(int y = 0; y < H; ++y) {
            v[y] = read(x, y);
        }

        cols[x] = add_xor(v);
        px[x] = x ? add_xor({px[x - 1], cols[x]}) : cols[x];
    }

    vec<int> rows(H), py(H);
    for(int y = 0; y < H; ++y) {
        vec<int> v(W);
        for(int x = 0; x < W; ++x) {
            v[x] = read(x, y);
        }

        rows[y] = add_xor(v);
        py[y] = y ? add_xor({py[y - 1], rows[y]}) : rows[y];
    }

    vector<vector<int>> V(LOG + 1);
    for(auto x: px) V[0].emplace_back(x);
    for(auto y: py) V[0].emplace_back(y);

    for(int lg = 0; lg < LOG; ++lg) {
        while(V[lg].size() >= 2) {
            int a = V[lg][V[lg].size() - 1];
            int b = V[lg][V[lg].size() - 2];

            V[lg].pop_back();
            V[lg].pop_back();

            auto [lo, hi] = add_adder(a, b);

            V[lg].emplace_back(lo);
            V[lg + 1].emplace_back(hi);
        }

        V[lg].resize(1, ZERO);
    }

    vec<int> k(LOG);
    for(int lg = 0; lg < LOG; ++lg) {
        const int pow = 1 << lg;
        k[lg] = K&pow ? ZERO : ONE;
    }

    vec<int> c(LOG);
    for(int lg = 0; lg < LOG; ++lg) {
        c[lg] = add_xor({V[lg][0], k[lg]});
    }

    add_and(c);
}

#ifdef LOCAL

static const int MAX_INSTRUCTIONS = 10000;
static const int MAX_INPUTS = 1000000;

static const int _AND = 0;
static const int _OR = 1;
static const int _XOR = 2;
static const int _NOT = 3;

static inline bool increasing(int a, int b, int c) {
	return a <= b && b <= c;
}

[[noreturn]] static inline void error(string message) {
	printf("%s\n", message.c_str());
	exit(0);
}

class InstructionNetwork {

	struct Instruction {
		int type;
		vector<int> input_indexes;

		inline Instruction(int _type, const vector<int>& _input_indexes):
				type(_type), input_indexes(_input_indexes) {
		}

		inline int apply(int a, int b) const {
			switch (type) {
				case _AND:
					return a & b;
				case _OR:
					return a | b;
				case _XOR:
					return a ^ b;
				default:
					return 0;
			}
		}

		inline int compute(const vector<int>& memory_cells) const {
			int r = memory_cells[input_indexes[0]];
			if (type == _NOT)
				return 1 - r;
            for (int j = 1; j < (int)input_indexes.size(); j++)
				r = apply(r, memory_cells[input_indexes[j]]);

			return r;
		}
	};

	int input_size;
	int total_inputs;
	vector<Instruction> instructions;

public:

	inline void init(int _input_size) {
		this->input_size = _input_size;
		this->total_inputs = 0;
		this->instructions.clear();
	}

	inline int add_instruction(int type, const vector<int>& input_indexes) {
		if (input_indexes.size() == 0)
			error("Instruction with no inputs");

		if (instructions.size() + 1 > MAX_INSTRUCTIONS)
			error("Too many instructions");

		if (total_inputs + input_indexes.size() > MAX_INPUTS)
			error("Too many inputs");

		instructions.emplace_back(type, input_indexes);
		total_inputs += input_indexes.size();
		int new_index = input_size + (int)instructions.size() - 1;

		for (int input_index : input_indexes)
			if (!increasing(0, input_index, new_index-1))
				error("Invalid index");

		return new_index;
	}

	inline int compute(vector<int> &memory_cells) const {
		for (auto &instruction : instructions)
			memory_cells.push_back(instruction.compute(memory_cells));
		return memory_cells.back();
	}
};


static InstructionNetwork instructionNetwork;

int main() {
	int H, W, K;
	assert(3 == scanf("%d%d%d", &H, &W, &K));

	FILE *log_file = fopen("log.txt","w");

	instructionNetwork.init(H * W);
	construct_network(H, W, K);

	while (true) {
		int rowA, colA, rowB, colB;
		assert(1 == scanf("%d", &rowA));
		if (rowA == -1)
			break;
		assert(3 == scanf("%d%d%d", &colA, &rowB, &colB));

		if ((!increasing(0, rowA, H-1)) ||
			(!increasing(0, colA, W-1)) ||
			(!increasing(0, rowB, H-1)) ||
			(!increasing(0, colB, W-1)) ||
			(rowA == rowB && colA == colB)) {
			printf("-1\n");
			fprintf(log_file, "-1\n");
			fflush(stdout);
			fflush(log_file);
			continue;
		}

		vector<int> memory_cells;
		for (int row = 0; row < H; row++)
			for (int col = 0; col < W; col++) {
				bool active = (row == rowA && col == colA) || (row == rowB && col == colB);
				memory_cells.push_back(active ? 1 : 0);
			}
		int computation_result = instructionNetwork.compute(memory_cells);

		printf("%d\n", computation_result);
		fflush(stdout);

		for(int i = 0; i < (int)memory_cells.size(); i++)
			fprintf(log_file, (i ? " %d" : "%d"), memory_cells[i]);
		fprintf(log_file, "\n");
		fflush(log_file);
	}
	fclose(stdin);
}

int add_and(vector<int> Ns) {
	return instructionNetwork.add_instruction(_AND, Ns);
}

int add_or(vector<int> Ns) {
	return instructionNetwork.add_instruction(_OR, Ns);
}

int add_xor(vector<int> Ns) {
	return instructionNetwork.add_instruction(_XOR, Ns);
}

int add_not(int N) {
	vector<int> Ns = {N};
	return instructionNetwork.add_instruction(_NOT, Ns);
}

#endif /* LOCAL */
