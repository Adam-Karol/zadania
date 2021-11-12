n = int(input())
ns = 0  # negative split
ns_rel = 0  # zawodnicy ktorzy zrealizowali plan ns
nns = 0  # nie negative split
nns_rel = 0  # zawodnicy ktorzy zrealizowali plan nns
for i in range(n):
    czasy = input().split(" ")
    for j in range(len(czasy)):
        c = czasy[j].split(":")
        temp = 0
        for k in range(len(c)):
            if k == 0:
                temp += int(c[k]) * 3600
            elif k == 1:
                temp += int(c[k]) * 60
            else:
                temp += int(c[k])
        czasy[j] = temp
    if czasy[0] > (czasy[1] - czasy[0]) > (czasy[2] - (czasy[1] + czasy[0])) > (czasy[3] - (czasy[2] + czasy[1] + czasy[0])):
        ns += 1
        if czasy[4] <= czasy[5]:
            ns_rel += 1
    else:
        nns += 1
        if czasy[4] <= czasy[5]:
            nns_rel += 1

print(ns_rel, end="")
print("/", end="")
print(ns, end=" ")
print(nns_rel, end="")
print("/", end="")
print(nns, end="")
