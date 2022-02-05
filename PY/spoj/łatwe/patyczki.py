_ = input()
patyczki = list(map(int, input().split(" ")))

patyczki_slownik = {}
for i in patyczki:
    if i not in patyczki_slownik:
        patyczki_slownik[i] = 0
    patyczki_slownik[i] += 1

licznik = 0

for i in patyczki_slownik:
    licznik += (patyczki_slownik[i] // 3)

print(licznik)
