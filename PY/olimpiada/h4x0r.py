wejscie = input()
wyjscie = ""

for i in wejscie:
    if i == "a":
        wyjscie += "4"
    elif i == "e":
        wyjscie += "3"
    elif i == "i":
        wyjscie += "1"
    elif i == "o":
        wyjscie += "0"
    elif i == "s":
        wyjscie += "5"
    else:
        wyjscie += i

print(wyjscie)
