n = int(input())
parzystocyfrowe = []

for i in range(1000000):
    czy = True
    for j in str(i):
        if int(j) % 2 != 0:
            czy = False
    if czy:
        parzystocyfrowe.append(i)

print(parzystocyfrowe[n])
