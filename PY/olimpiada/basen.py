N = int(input())
dlugosci = input().split(" ")

for i in range(len(dlugosci)):
    dlugosci[i] = int(dlugosci[i])

wyjscie = 1
poprzedni = -1
rosnacy = True

for i in dlugosci:
    if rosnacy and poprzedni > i:
        wyjscie += 1
        rosnacy = False
    elif not rosnacy and poprzedni < i:
        wyjscie += 1
        rosnacy = True
    poprzedni = i

print(wyjscie)
