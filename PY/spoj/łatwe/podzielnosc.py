for _ in range(int(input())):
    liczby = list(map(int, input().split(" ")))
    for liczba in range(liczby[0]):
        if liczba % liczby[1] == 0 and liczba % liczby[2] != 0:
            print(liczba, end=" ")
