n = int(input())
deski = input().split(" ")

if len(deski) < 4:
    print(0)
    quit()

for i in range(len(deski)):
    deski[i] = int(deski[i])

deski = sorted(deski)
print(deski[-4]**2)
