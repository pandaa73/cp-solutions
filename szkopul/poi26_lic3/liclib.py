class _LicLib:
    def __init__(self):
        self._initialized = False
        self._need_new_ciag = True

    def _initialize(self):
        if not self._initialized:
            self._t, self._g, self._n, self._m, self._k = map(int, input().split())
            self._initialized = True

    def _read_ciag(self):
        self._sequence = list(map(int, input().split()))
        self._need_new_ciag = False

    def IleGier(self) -> int:
        if not self._initialized:
            self._initialize()
        return self._t

    def KimJestem(self) -> int:
        if not self._initialized:
            self._initialize()
        return self._g

    def DajCiag(self) -> list[int]:
        if not self._initialized:
            self._initialize()
        if self._need_new_ciag:
            self._read_ciag()
        return self._sequence

    def DajM(self) -> int:
        if not self._initialized:
            self._initialize()
        return self._m

    def DajK(self) -> int:
        if not self._initialized:
            self._initialize()
        return self._k

    def RuchPartnera(self) -> tuple[int, bool]:
        if not self._initialized:
            self._initialize()
        stawka, koniec = map(int, input().split())
        if koniec:
            self._need_new_ciag = True
        return stawka, bool(koniec)

    def Licytuj(self, bid: int, end: bool) -> None:
        if not self._initialized:
            self._initialize()
        print(bid, int(end), flush=True)
        if end:
            self._need_new_ciag = True

# Singleton instance of _LicLib
__some_class_object = _LicLib()

# Public API
def IleGier() -> int:
    """Zwraca liczbę gier do rozegrania."""
    return __some_class_object.IleGier()

def KimJestem() -> int:
    """Zwraca 0, jeśli gramy jako Algosia, lub 1, jeśli gramy jako Bajtek."""
    return __some_class_object.KimJestem()

def DajCiag() -> list[int]:
    """Zwraca ciąg liczb przypisany do gracza w trakcie tej gry."""
    return __some_class_object.DajCiag()

def DajM() -> int:
    """Zwraca zakres liczb, z którego zostały wygenerowane elementy ciągu."""
    return __some_class_object.DajM()

def DajK() -> int:
    """Zwraca parametr k z zadania."""
    return __some_class_object.DajK()

def RuchPartnera() -> tuple[int, bool]:
    """Zwraca parę (stawka, koniec), gdzie:
        - stawka to wartosc ostatnio zalicytowana przez partnera,
        - koniec to wartosc logiczna mowiaca, czy partner zakonczyl licytacje w tej grze.
    """
    return __some_class_object.RuchPartnera()

def Licytuj(bid: int, end: bool) -> None:
    __some_class_object.Licytuj(bid, end)

# Expose the public functions for import
__all__ = ['IleGier', 'KimJestem', 'DajCiag', 'DajM', 'DajK', 'RuchPartnera', 'Licytuj']