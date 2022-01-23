ilosc = int(input())
for _ in range(ilosc):
    slowo = list(input())
    for i in range(len(slowo)):
        slowo[i] = ord(slowo[i])
    print(max(slowo) - min(slowo))
