liczba_linijek = int(input())

licznik = 0
maks = 0

for i in range(liczba_linijek):

    linia = input()

    if linia == "for":
        licznik += 1

        if licznik > maks:
            maks += 1

    elif linia == "end":
        licznik -= 1

print("O(1)" if maks == 0 else "O(n)" if maks == 1 else f"O(n^{maks})")