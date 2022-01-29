poczatek_lekcji = list(map(int, input().split(":")))
dlugosci_przerw = []

while True:
    przerwa = input()
    if przerwa == "":
        break
    dlugosci_przerw.append(int(przerwa))

dzwonki_h = [poczatek_lekcji[0]]
dzwonki_m = [poczatek_lekcji[1]]

j = 1
for i in range(len(dlugosci_przerw)):
    dzwonki_h.append(0)
    dzwonki_m.append(0)
    dzwonki_m[j] = dzwonki_m[j - 1] + 45
    dzwonki_h[j] = dzwonki_h[j - 1]
    if dzwonki_m[j] >= 60:
        dzwonki_m[j] -= 60
        dzwonki_h[j] += 1
    j += 1
    dzwonki_h.append(0)
    dzwonki_m.append(0)
    dzwonki_m[j] = dzwonki_m[j - 1] + dlugosci_przerw[i]
    dzwonki_h[j] = dzwonki_h[j - 1]
    if dzwonki_m[j] >= 60:
        dzwonki_m[j] -= 60
        dzwonki_h[j] += 1
    j += 1

dzwonki_h.append(0)
dzwonki_m.append(0)
dzwonki_m[j] = dzwonki_m[j - 1] + 45
dzwonki_h[j] = dzwonki_h[j - 1]
if dzwonki_m[j] >= 60:
    dzwonki_m[j] -= 60
    dzwonki_h[j] += 1

wyjscie = ""
for i in range(len(dzwonki_h)):
    if len(str(dzwonki_h[i])) == 1:
        wyjscie += "0"
    wyjscie += str(dzwonki_h[i])
    wyjscie += ":"
    if len(str(dzwonki_m[i])) == 1:
        wyjscie += "0"
    wyjscie += str(dzwonki_m[i])
    wyjscie += ", "

print(wyjscie[:-2])
