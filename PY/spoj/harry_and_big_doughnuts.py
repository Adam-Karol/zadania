t = int(input())
for i in range(t):
    wejscie = input().split(" ")
    c = int(wejscie[0])
    k = int(wejscie[1])
    w = int(wejscie[2])
    if c * w <= k:
        print("yes")
    else:
        print("no")