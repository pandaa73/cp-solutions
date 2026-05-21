from liclib import IleGier, KimJestem, DajCiag, DajM, DajK, RuchPartnera, Licytuj

def main():
    for _ in range(IleGier()):
        moj_ciag = DajCiag()
        m = DajM()
        k = DajK()

        if KimJestem() == 0:
            # Gramy jako Algosia.
            stawka = 0
            for i in range(3):
                stawka += 1  # Algosia licytuje wartość o 1 większą.
                if i == 2:
                    Licytuj(stawka, 1)  # Algosia kończy grę.
                    break
                Licytuj(stawka, 0)  # Algosia licytuje wartość stawki i nie kończy gry.
                stawka, koniec = RuchPartnera()  # Wczytujemy ruch Bajtka.
        else:
            # Gramy jako Bajtek.
            while True:
                stawka, koniec = RuchPartnera()  # Wczytujemy ruch Algosii.
                if koniec:
                    break  # Bajtek kończy grę.
                Licytuj(stawka + 1, 0)  # Bajtek licytuje wartość o 1 większą i nie kończy gry.

if __name__ == "__main__":
    main()
