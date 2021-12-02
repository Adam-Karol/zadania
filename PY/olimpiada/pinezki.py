def pinezki(a, b):
    odc = b - a
    x = odc // 3 + a
    y = 2 * (odc // 3) + a
    x, y = int(x), int(y)

    return x, y


potega = int(input())
a = 0
b = 3**potega
lista = [0, b]


for _ in range(potega):
    out = pinezki(a, b)
    out2 = pinezki(out[1], b)
    x, y = out[0], out[1]
    lista.append(x)
    lista.append(y)
    x2, y2 = out2[0], out2[1]
    lista.append(x2)
    lista.append(y2)
    b = x

b = 3**potega
y = pinezki(a, b)[1]
temp = False

for _ in range(potega):
    out = pinezki(a, b)
    if temp:
        out2 = pinezki(y, out[0])
        temp = False
    else:
        out2 = out
    x, y = out[0], out[1]
    lista.append(x)
    lista.append(y)
    x2, y2 = out2[0], out2[1]
    lista.append(x2)
    lista.append(y2)
    a = y
    temp = True


lista = sorted(list(set(lista)))


for i in range(int(input())):
    zapytanie = int(input())
    try:
        print(lista[zapytanie - 1])
    except IndexError:
        print("NIE")
