def pktX(pierwszy_punkt, ostatni_punkt):
    dlugosc = ostatni_punkt - pierwszy_punkt
    x = dlugosc // 3 + pierwszy_punkt
    return x


def pktY(pierwszy_punkt, ostatni_punkt):
    dlugosc = ostatni_punkt - pierwszy_punkt
    y = (dlugosc // 3) * 2 + pierwszy_punkt
    return y


def pinezki_na_odcinku(a, b):
    dlugosc = b - a
    if dlugosc == 1:
        return a, b

    return (a,) + pinezki_na_odcinku(a, pktX(a, b)) + pinezki_na_odcinku(pktY(a, b), b) + (b,)


def odp_na_zapytanie(zapytanie, pinezki):
    indeks = zapytanie - 1

    if indeks < len(pinezki):
        return pinezki[indeks]

    return "NIE"


def main():
    n = int(input())
    liczba_zapytan = int(input())

    pinezki = tuple(sorted(set(pinezki_na_odcinku(0, 3**n))))
    print(pinezki)

    for _ in range(liczba_zapytan):
        zapytanie = int(input())
        print(odp_na_zapytanie(zapytanie, pinezki))


main()
