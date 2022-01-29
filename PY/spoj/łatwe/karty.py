def dodawanie_wartosci(karty):
    wynik = 0
    for i in karty:
        if i.isnumeric():
            wynik += int(i)
        else:
            wynik += wartosci_kart[i]
    return wynik


jasio = list(input())
stasio = list(input())

wartosci_kart = {"T": 10, "J": 11, "Q": 12, "K": 13, "A": 14}

jasio_wynik = dodawanie_wartosci(jasio)
stasio_wynik = dodawanie_wartosci(stasio)


if jasio_wynik > stasio_wynik:
    print("JASIO")
elif stasio_wynik > jasio_wynik:
    print("STASIO")
else:
    print("REMIS")
