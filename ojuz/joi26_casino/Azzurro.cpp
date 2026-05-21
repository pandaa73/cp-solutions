#include "Azzurro.h"

namespace {
    // グローバル変数と内部関数は無名名前空間内で宣言すること
    // All global variables and internal functions should be declared in an unnamed namespace
    int variable_example = 0;
    int function_example(void) { return 0; }
}

std::vector<std::vector<int>> Azzurro(int N, int L, std::string S) {
    std::vector<std::vector<int>> x(N, std::vector<int>(N, 0));
    return x;
}