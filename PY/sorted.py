class Osoba:
    def __init__(self, imie, nazwisko, wiek):
        self.imie = imie
        self.nazwisko = nazwisko
        self.wiek = wiek

    def __str__(self):
        return "Imię: " + self.imie + ", Nazwisko: " + self.nazwisko + ", Wiek: " + str(self.wiek)

    def __repr__(self):
        return str(self)


# def sortuj(osoby):
#     for i in range(len(osoby)):
#         for j in range(i, len(osoby)):
#             if len(osoby[i].nazwisko) > len(osoby[j].nazwisko):
#                 temp = osoby[i]
#                 osoby[i] = osoby[j]
#                 osoby[j] = temp


os1 = Osoba("Jan", "Kowalski", 50)
os2 = Osoba("Marcin", "Nowak", 11)
os3 = Osoba("Kuba", "Wiśniewski", 30)
os4 = Osoba("Robert", "Lewandowski", 27)
os5 = Osoba("Adrian", "Zieliński", 90)
osoby = [os1, os2, os3, os4, os5]



def sortuj(lista: list, f_porownujaca) -> list:
    for i in range(len(lista)):
        for j in range(i, len(lista)):
            if f_porownujaca(lista[i], lista[j]):
                temp = lista[i]
                lista[i] = lista[j]
                lista[j] = temp

    return lista


print(*map(lambda x: x.nazwisko, sortuj(osoby, lambda x, y: len(x.nazwisko) > len(y.nazwisko))), sep="\n")


# print("sortuj: ", l1)
# print("sorted: ", l2)
# print("sort: ", l0)
#
#
# # sortuj(osoby)
# print(*[osoba.nazwisko for osoba in osoby], sep="\n")
#
# osoby_sorted = sorted(osoby, key=lambda x: len(x.nazwisko), reverse=True)
#
#
# print()
# osoby.sort(key=lambda x: len(x.nazwisko), reverse=True)
# print(*[osoba.nazwisko for osoba in osoby], sep="\n")
