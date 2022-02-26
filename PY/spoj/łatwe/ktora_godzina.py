def na_dziesietny(n):
    return int(n, 2)


liczby = input().split(" ")
for i in range(len(liczby)):
    if i == 2:
        print(":", end="")
    print(na_dziesietny(liczby[i]), end="")
