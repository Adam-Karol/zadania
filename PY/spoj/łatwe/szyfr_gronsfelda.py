wybor = input()
klucz = input()
tekst = input()

wyjscie = ""

if wybor == "SZYFRUJ":
    temp = 0
    przesuniecie = int(klucz[temp])
    for i in tekst:
        wyjscie += chr(ord(i) + przesuniecie)
        try:
            temp += 1
            przesuniecie = int(klucz[temp])
        except IndexError:
            temp = 0
            przesuniecie = int(klucz[temp])

else:
    temp = 0
    przesuniecie = int(klucz[temp])
    for i in tekst:
        wyjscie += chr(ord(i) - przesuniecie)
        try:
            temp += 1
            przesuniecie = int(klucz[temp])
        except IndexError:
            temp = 0
            przesuniecie = int(klucz[temp])

print(wyjscie)
