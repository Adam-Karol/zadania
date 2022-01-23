przedzial = list(map(int, input().split(" ")))
for liczba in range(przedzial[0], przedzial[1] + 1):
    if liczba % 6 == 0:
        print("ab", end="", sep="")
    elif liczba % 2 == 0 and liczba % 3 != 0:
        print("a", end="", sep="")
    elif liczba % 3 == 0 and liczba % 2 != 0:
        print("b", end="", sep="")
