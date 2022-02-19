liczby = []
for i in range(int(input())):
    liczby.append(int(input()))

warunek = input().split(" ")
if warunek[0] == "<":
    for liczba in liczby:
        if liczba < int(warunek[1]):
            print(liczba)
else:
    for liczba in liczby:
        if liczba > int(warunek[1]):
            print(liczba)
