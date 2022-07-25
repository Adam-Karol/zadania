class Kolor:
    def __init__(self, r: int, g: int, b: int):
        self.r = r
        self.g = g
        self.b = b

    def __repr__(self) -> str:
        """Zwraca reprezentację obiektu jako string."""
        return self.__str__()

    def __str__(self) -> str:
        """Konwertuje obiekt na string."""
        return "(" + str(self.r) + " " + str(self.g) + " " + str(self.b) + ")"


def szesnastkowy_na_rgb(szesnastkowy):
    return Kolor(int(szesnastkowy[1:3], 16),
                 int(szesnastkowy[3:5], 16),
                 int(szesnastkowy[5:], 16))


def suma_bezwzglednych_roznic(a: Kolor, b: Kolor):
    roznica_r = abs(a.r - b.r)
    roznica_g = abs(a.g - b.g)
    roznica_b = abs(a.b - b.b)
    return roznica_r + roznica_g + roznica_b


def srednia(lista):
    return sum(lista) / len(lista)


def wczytaj_obraz(y):
    obraz = []
    for _ in range(int(y)):
        obraz.append(input().split(" "))
    for i in range(len(obraz)):
        if "" in obraz[i]:
            obraz[i].remove("")
    return obraz


def konwertuj_obraz(obraz):
    obraz2 = []
    for wiersz in obraz:
        obraz2.append([])
        for kolor16 in wiersz:
            obraz2[-1].append(szesnastkowy_na_rgb(kolor16))

    return obraz2


x, y = tuple(input().split(" "))

obraz_wzorcowy = wczytaj_obraz(y)

obraz_wzorcowy = konwertuj_obraz(obraz_wzorcowy)

t = int(input())

obrazy = []
for _ in range(t):
    obrazy.append(konwertuj_obraz(wczytaj_obraz(y)))

ile_podobnych = []
for obraz in obrazy:
    ile_podobnych.append(0)
    for i in range(len(obraz)):
        for j in range(len(obraz[i])):
            if suma_bezwzglednych_roznic(obraz[i][j], obraz_wzorcowy[i][j]) <= 5:
                ile_podobnych[obrazy.index(obraz)] += 1

ile_pikseli = int(x) * int(y)
for i in ile_podobnych:
    wynik = i / ile_pikseli
    if wynik.is_integer():
        print(int(wynik))
    else:
        print(round(i / ile_pikseli, 2))



# ile2 = int(input())
# for _ in range(ile2):
#     kolor2 = 0
#     for _ in range(int(ile[1])):
#         temp = input().split(" ")
#         kolor2 += abs(szesnastkowy_na_dziesietny(temp[0][1:3]) - szesnastkowy_na_dziesietny(temp[1][1:3]))
#         kolor2 += abs(szesnastkowy_na_dziesietny(temp[0][3:5]) - szesnastkowy_na_dziesietny(temp[1][3:5]))
#         kolor2 += abs(szesnastkowy_na_dziesietny(temp[0][5:]) - szesnastkowy_na_dziesietny(temp[1][5:]))
#
#     print(abs(kolor2 - kolor))
