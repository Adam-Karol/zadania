n = int(input())
ile = 0

wejscie = input().split()
for i in range(n-3):
    if int(wejscie[i+3]) == (int(wejscie[i+2]) + int(wejscie[i+1])):
        ile += 1

print(ile)
quit()