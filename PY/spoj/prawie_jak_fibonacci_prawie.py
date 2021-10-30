n = int(input())
ile = 0

wejscie = input().split()
for i in range(n-2):
    if int(wejscie[i+2]) == (int(wejscie[i+1]) + int(wejscie[i])):
        ile += 1

print(ile)
quit()