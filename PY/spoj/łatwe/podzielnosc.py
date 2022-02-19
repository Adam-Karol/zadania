for _ in range(int(input())):
    liczby = input().split(" ")
    n = int(liczby[0])
    x = int(liczby[1])
    y = int(liczby[2])
    for liczba in range(n):
        if liczba % x == 0 and liczba % y != 0:
            print(liczba, end=" ")
    print()
