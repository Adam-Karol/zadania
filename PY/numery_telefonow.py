dozwolone_znaki = ["+", "-", " ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
numer = input()

sprawdz = [znaki in dozwolone_znaki for znaki in numer]
czy_poprawny = all(sprawdz)

if czy_poprawny == False:
    print("Podany numer jest niepoprawny")
    quit()

numer = numer.replace(" ", "")
numer = numer.replace("-", "")

if numer[0] == "+":
    if str(numer[1] + numer[2]) != "48":
        print("To nie jest numer z Polski")
        quit()
    print(numer)
    quit()
numer = numer[-9:]
print(numer)