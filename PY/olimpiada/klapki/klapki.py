from time import time
czas1 = time()
liczba_osob = int(input())
wzrosty = list(map(int, input().split(" ")))
liczba_klapek = int(input())
if liczba_klapek != 0:
    rozmiary_obcasow = list(map(int, input().split(" ")))
else:
    _ = input()
minimalny_wzrost = int(input())

mozliwosci = 0
for wzrost in wzrosty:
    if wzrost >= minimalny_wzrost:
        mozliwosci += 1
    else:
        if liczba_klapek != 0:
            for obcas in rozmiary_obcasow:
                if (wzrost + obcas) >= minimalny_wzrost:
                    mozliwosci += 1
                    rozmiary_obcasow.remove(obcas)
                    break

print(mozliwosci)
print(time()-czas1)
