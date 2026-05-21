#ifndef LICLIB_H
#define LICLIB_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <stdexcept>

class __LicLib {
private:
    bool initialized = false;
    bool need_new_seq = true;
    int t, g, n, m, k;
    std::vector<int> ciag;

    void initialize() {
        if (!initialized) {
            std::cin >> t >> g >> n >> m >> k;
            initialized = true;
        }
    }

    void readNextSequence() {
        ciag.resize(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> ciag[i];
        }
        need_new_seq = false;
    }

public:
    int IleGier() {
        if (!initialized) {
            initialize();
        }
        return t;
    }

    int KimJestem() {
        if (!initialized) {
            initialize();
        }
        return g;
    }

    std::vector<int> dajCiag() {
        if (!initialized) {
            initialize();
        }
        if (need_new_seq) {
            readNextSequence();
        }
        return ciag;
    }

    int dajM() {
        if (!initialized) {
            initialize();
        }
        return m;
    }

    int dajK() {
        if (!initialized) {
            initialize();
        }
        return k;
    }

    std::pair<int, bool> RuchPartnera() {
        if (!initialized) {
            initialize();
        }
        int stawka, koniec;
        std::cin >> stawka >> koniec;
        if (koniec) {
            need_new_seq = true;
        }
        return std::make_pair(stawka, (bool)koniec);
    }

    void Licytuj(int stawka, bool koniec) {
        if (!initialized) {
            initialize();
        }
        std::cout << stawka << " " << koniec << std::endl;
        if (koniec) {
            need_new_seq = true;
        }
    }
};

// Singleton instance
static __LicLib __some_class_object;

/** Zwraca liczbe gier t. */
inline int IleGier() {
    return __some_class_object.IleGier();
}

/** Zwraca 0, jesli ten program to Algosia, lub 1, jesli to Bajtek. */
inline int KimJestem() {
    return __some_class_object.KimJestem();
}

/** Zwraca ciąg gracza. */
inline std::vector<int> DajCiag() {
    return __some_class_object.dajCiag();
}

/** Zwraca liczbe m. */
inline int DajM() {
    return __some_class_object.dajM();
}

/** Zwraca liczbe k. */
inline int DajK() {
    return __some_class_object.dajK();
}

/**
 * Zwraca pare (stawka, koniec):
 *   - stawka  -- wartosc zalicytowana przez partnera,
 *   - koniec  -- true, jesli partner zakonczyl licytacje, lub false w przeciwnym przypadku.
 */
inline std::pair<int, bool> RuchPartnera() {
    return __some_class_object.RuchPartnera();
}

/**
 * Zalicytuj liczbe calkowita 'stawka'.
 * Jesli koniec == true, gracz oglasza zakonczenie licytacji.
 */
inline void Licytuj(int stawka, bool koniec) {
    __some_class_object.Licytuj(stawka, koniec);
}

#endif // LICLIB_H
