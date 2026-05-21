#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

#ifdef GRADER_DEBUG

constexpr bool IS_DEBUG = 1;

#else

constexpr bool IS_DEBUG = 0;

#endif

struct Subprocess {
    FILE* in;   // licsoc pisze na stdin podprocesu
    FILE* out;  // licsoc czyta z stdout podprocesu
    pid_t pid;
};

Subprocess spawn(const char* cmd) {
    int to_child[2], from_child[2];
    [[maybe_unused]] int r1 = pipe(to_child);
    [[maybe_unused]] int r2 = pipe(from_child);
    pid_t pid = fork();
    if (pid == 0) {
        close(to_child[1]);
        close(from_child[0]);
        dup2(to_child[0], STDIN_FILENO);
        dup2(from_child[1], STDOUT_FILENO);
        close(to_child[0]);
        close(from_child[1]);
        execl("/bin/sh", "sh", "-c", cmd, nullptr);
        _exit(1);
    }
    close(to_child[0]);
    close(from_child[1]);
    return {fdopen(to_child[1], "w"), fdopen(from_child[0], "r"), pid};
}

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        cerr << "Usage: ./licsoc.e <cmd_programu> [plik_wejsciowy]" << endl;
        return 1;
    }
    const char* cmd_a = argv[1];
    const char* input_path = (argc == 3 ? argv[2] : "input.in");

    cerr << "[DEBUG] Poczatek gry!" << endl;

    // Otworz plik wejsciowy (domyslnie input.in).
    ifstream input(input_path);
    if (!input) {
        cerr << "Error: Cannot open input file: " << input_path << endl;
        return 1;
    }

    // Wczytaj t, n, m, k.
    // t -- liczba gier, n -- dlugosc ciagu, m -- maksymalna wartosc elementu, k -- parametr.
    int t, n, m, k;
    input >> t >> n >> m >> k;

    vector<vector<int>> a(t, vector<int>(n)); // ciagi Algosi
    vector<vector<int>> b(t, vector<int>(n)); // ciagi Bajtka
    for (int game = 0; game < t; ++game) {
        for (int i = 0; i < n; ++i) input >> a[game][i];
        for (int i = 0; i < n; ++i) input >> b[game][i];
    }
    input.close();

    cerr << "[DEBUG] t = " << t << " n = " << n << " m = " << m << " k = " << k << endl;

    // Spawn both contestant processes.
    Subprocess algosia = spawn(cmd_a);
    Subprocess bajtek  = spawn(cmd_a);

    // Wyslij t g n m k  (g = 0 dla Algosi, g=1 dla Bajtka)
    fprintf(algosia.in, "%d %d %d %d %d\n", t, 0, n, m, k); fflush(algosia.in);
    fprintf(bajtek.in,  "%d %d %d %d %d\n", t, 1, n, m, k); fflush(bajtek.in);

    int won = 0;

    for (int game = 0; game < t; ++game) {
        bool failed = 0;
        // W = floor(sum(min(a_i, b_i)) / k).
        int true_answer = 0;
        for (int i = 0; i < n; ++i) {
            true_answer += min(a[game][i], b[game][i]);
        }
        true_answer /= k;

        // Wyslij do kazdego zawodnika ich ciag
        for (int i = 0; i < n; ++i) {
            if (i > 0) fprintf(algosia.in, " ");
            fprintf(algosia.in, "%d", a[game][i]);
        }
        fprintf(algosia.in, "\n"); fflush(algosia.in);

        for (int i = 0; i < n; ++i) {
            if (i > 0) fprintf(bajtek.in, " ");
            fprintf(bajtek.in, "%d", b[game][i]);
        }
        fprintf(bajtek.in, "\n"); fflush(bajtek.in);

        cerr << "[DEBUG] Gra " << game + 1 << ": wartosc W = " << true_answer << endl;

        int last_bid = 0;
        while (true) {
            // Przeczytaj warotsc zalicytowana przez Algosie i przekaz dla Bajtka.
            int bid_a, end_a;
            [[maybe_unused]]int r = fscanf(algosia.out, "%d %d", &bid_a, &end_a);

            if(last_bid >= bid_a) {
                cerr << "[DEBUG] Failed. Last bid is not smaller than new bid:"
                    << " last_bid = " << last_bid << ", new_bid = " << bid_a
                    << endl;
                failed = 1;
            }

            if constexpr(IS_DEBUG) {
                cerr << "[DEBUG] Algosia zalicytowala: (" << bid_a << ", " << end_a << ")" << endl;
            }


            last_bid = bid_a;
            fprintf(bajtek.in, "%d %d\n", bid_a, end_a); fflush(bajtek.in);
            if (end_a) break;

            // Przeczytaj wartosc zalicytowana przez Bajtka i przekaz dla Algosi.
            int bid_b, end_b;
            [[maybe_unused]]int r2 = fscanf(bajtek.out, "%d %d", &bid_b, &end_b);

            if(last_bid >= bid_b) {
                cerr << "[DEBUG] Failed. Last bid is not smaller than new bid:"
                    << " last_bid = " << last_bid << ", new_bid = " << bid_b
                    << endl;
                failed = 1;
            }

            if constexpr(IS_DEBUG) {
                cerr << "[DEBUG] Bajtek zalicytowal:   (" << bid_b << ", " << end_b << ")" << endl;
            }

            last_bid = bid_b;
            fprintf(algosia.in, "%d %d\n", bid_b, end_b); fflush(algosia.in);
            if (end_b) break;
        }

        if (!failed && last_bid == true_answer) {
            ++won;
            cerr << "[DEBUG] Gra wygrana! (W = " << last_bid << ")" << endl;
        } else {
            cerr << "[DEBUG] Gra przegrana :( (zalicytowana wartosc = " << last_bid << ", W = " << true_answer << ")" << endl;
        }
    }

    fclose(algosia.in);
    fclose(bajtek.in);
    waitpid(algosia.pid, nullptr, 0);
    waitpid(bajtek.pid, nullptr, 0);

    cerr << "Liczba wygranych gier: " << won << " / " << t << endl;

    return 0;
}
