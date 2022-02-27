wiatraczek_rzedu1 = [
    ['*', '*'],
    ['*', '*']
]

def wyswietl(wiatraczek):
    for w in wiatraczek:
        print(*w, sep='')
    print()


def wklej(wiatraczek, wiatraczek_rzedu1):
    śr = (len(wiatraczek) // 2) - 1
    wiatraczek[śr][śr] = wiatraczek_rzedu1[0][0]
    wiatraczek[śr][śr + 1] = wiatraczek_rzedu1[0][1]
    wiatraczek[śr + 1][śr] = wiatraczek_rzedu1[1][0]
    wiatraczek[śr + 1][śr + 1] = wiatraczek_rzedu1[1][1]


def narożniki(wiatraczek):
    i_max = len(wiatraczek) - 1
    wiatraczek[0][0] = "*"
    wiatraczek[i_max][0] = "*"
    wiatraczek[0][i_max] = "*"
    wiatraczek[i_max][i_max] = "*"


def zapełnienie_wzdłuż_krawędzi(wiatraczek, m):
    pass


def zrób_wiatraczek_rzędu(n):
    wiatraczek = [0 for _ in range(2*n)]
    for w in range(len(wiatraczek)):
        wiatraczek[w] = ['?' for _ in range(2*n)]

    wyswietl(wiatraczek)

    if n == 1:
        return wiatraczek_rzedu1
    else:
        wklej(wiatraczek, wiatraczek_rzedu1)
        wyswietl(wiatraczek)
        narożniki(wiatraczek)
        wyswietl(wiatraczek)
        zapełnienie_wzdłuż_krawędzi(wiatraczek)
        return wiatraczek



wyswietl(zrób_wiatraczek_rzędu(2))

# while True:
#     n = int(input())
#     if n == 0:
#         break
#     else:
#         wyswietl(zrób_wiatraczek_rzędu(n))


#
# wiatraczek1 = [0 for i in range(401)]
# wiatraczek2 = [0 for i in range(401)]
#
# n, k, j = 0, 0, 0
# while True:
#     n = int(input())
#     if n == 0:
#         break
#     for i in range(2 * abs(n)):
#         for j in range(2 * abs(n)):
#             wiatraczek1[i] = '.'
#             wiatraczek2[j] = '.'
#     if n > 0:
#         for i in range(2 * n):
#             if i < n:
#                 k = i + 1
#                 j = 0
#             else:
#                 k = 2 * n - i
#                 j = -(2 * n - 1)
#
#             while k:
#                 wiatraczek1[i] = '*'
#                 wiatraczek2[abs(j)] = '*'
#                 k -= 1
#                 j += 1
#         for i in range(2 * n):
#             if i < n:
#                 k = n - i
#                 j = n
#             else:
#                 k = i - n + 1
#                 j = -n + 1
#             while k:
#                 wiatraczek1[i] = '*'
#                 wiatraczek2[abs(j)] = '*'
#                 k -= 1
#                 j += 1
#     else:
#         n = abs(n)
#         for i in range(2 * n):
#             if i < n:
#                 k = n - i
#                 j = n - 1
#             else:
#                 k = i - n + 1
#                 j = -n
#             while k:
#                 wiatraczek1[i] = '*'
#                 wiatraczek2[abs(j)] = '*'
#                 k -= 1
#                 j -= 1
#
#         for i in range(2 * n):
#             if i < n:
#                 k = i + 1
#                 j = 2 * n - 1
#             else:
#                 k = 2 * n - i
#                 j = 0
#             while k:
#                 wiatraczek1[i] = '*'
#                 wiatraczek2[abs(j)] = '*'
#                 k -= 1
#                 j -= 1
#     for i in range(2 * n):
#         for i in range(2 * n):
#             print(wiatraczek1[i], end="")
#             print(wiatraczek1[j], end="")
#         print()
