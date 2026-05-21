#include "liclib.h"

int main() {
    for (int i = 0; i < IleGier(); ++i) {
        std::vector<int> moj_ciag = DajCiag();
        [[maybe_unused]] int m = DajM();
        [[maybe_unused]] int k = DajK();
        int stawka = 0;
        int num_iters = 3;

        if (KimJestem() == 0) {
            // Gra Algosi.
            for (int i = 0; i < num_iters; i++) {
                if (i == num_iters - 1) {
                    Licytuj(stawka + 1, true); // Algosia kończy grę.
                    break;
                }
                Licytuj(stawka + 1, false); // Algosia licytuje.
                auto [nowa_stawka, koniec] = RuchPartnera();
                stawka = nowa_stawka;
            }
        } else {
            // Gra Bajtka.
            while (true) {
                auto [nowa_stawka, koniec] = RuchPartnera();
                stawka = nowa_stawka;
                if (koniec) {
                    break; 
                }
                Licytuj(stawka + 1, false); // Bajtek licytuje wartość o 1 większą i nie kończy gry.
            }
        }
    }

    return 0;
}
