slowo = input()
licz = 0
for i in range(len(slowo)-1):
    if slowo[i] == slowo[i+1]:
        licz += 1
print(licz)