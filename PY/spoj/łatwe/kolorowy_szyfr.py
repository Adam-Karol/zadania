wejscie = input().split("#")[1:]
for kolor in wejscie:
    r = kolor[:2]
    g = kolor[2:4]
    b = kolor[4:]
    print(chr(int(r, 16) + int(g, 16) + int(b, 16)), end="")
