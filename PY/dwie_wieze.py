class Pozycja:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def wczytaj_poz():
    wejscie = input().split(' ')
    temp1 = wejscie[0]
    temp2 = wejscie[1]
    k1 = Pozycja(int(ord(temp1[0])-96), int(temp1[1]))
    k2 = Pozycja(int(ord(temp2[0]) - 96), int(temp2[1]))
    return k1, k2


def oblicz_ataki(wieza):
    ataki = []

    for i in range(wieza.x, 9):
        atak = Pozycja(i, wieza.y)
        ataki.append(atak)
    for i in range(0, wieza.x):
        atak = Pozycja(i, wieza.y)
        ataki.append(atak)
    for i in range(wieza.y, 9):
        atak = Pozycja(wieza.x, i)
        ataki.append(atak)
    for i in range(0, wieza.y):
        atak = Pozycja(wieza.x, i)
        ataki.append(atak)

    return ataki

def main():
    k1, k2 = wczytaj_poz()

    ataki = oblicz_ataki(k1)

    for i in ataki:
        if i.x == k2.x and i.y == k2.y:
            print("TAK")
            return

    print("NIE")


main()