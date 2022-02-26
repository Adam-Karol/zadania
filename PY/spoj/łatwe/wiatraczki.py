def ab(a):
    if a > 0:
        return a
    else:
        return -a


wiatraczek1 = []
wiatraczek2 = []
for i in range(401):
    wiatraczek1.append(0)
for i in range(401):
    wiatraczek2.append(0)

n, k, j = 0, 0, 0
while True:
    n = int(input())
    if n == 0:
        break
    for i in range(2 * ab(n)):
        for j in range(2 * ab(n)):
            wiatraczek1[i] = '.'
            wiatraczek2[j] = '.'
    if n > 0:
        for i in range(2 * n):
            if i < n:
                k = i + 1
                j = 0
            else:
                k = 2 * n - i
                j = -(2 * n - 1)

            while k:
                wiatraczek1[i] = '*'
                wiatraczek2[ab(j)] = '*'
                k -= 1
                j += 1
        for i in range(2 * n):
            if i < n:
                k = n - i
                j = n
            else:
                k = i - n + 1
                j = -n + 1
            while k:
                wiatraczek1[i] = '*'
                wiatraczek2[ab(j)] = '*'
                k -= 1
                j += 1
    else:
        n = ab(n)
        for i in range(2 * n):
            if i < n:
                k = n - i
                j = n - 1
            else:
                k = i - n + 1
                j = -n
            while k:
                wiatraczek1[i] = '*'
                wiatraczek2[ab(j)] = '*'
                k -= 1
                j -= 1

        for i in range(2 * n):
            if i < n:
                k = i + 1
                j = 2 * n - 1
            else:
                k = 2 * n - i
                j = 0
            while k:
                wiatraczek1[i] = '*'
                wiatraczek2[ab(j)] = '*'
                k -= 1
                j -= 1
    for i in range(2 * n):
        for i in range(2 * n):
            print(wiatraczek1[i], end="")
            print(wiatraczek1[j], end="")
        print()
