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

def main():
    k1, k2 = wczytaj_poz()
    
    if k1.x == k2.x or k1.y == k2.y:
        print("TAK")
        quit()

    print("NIE")

main()