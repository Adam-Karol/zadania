max_dlugosc = int(input())
nazwa1 = input()

if len(nazwa1) <= max_dlugosc:
    print(nazwa1)
    quit()

nazwa1 = list(nazwa1)
for i in range(len(nazwa1)-1, 0, -1):
    if len(nazwa1) == max_dlugosc:
        break
    if not nazwa1[i].isalnum():
        nazwa1.pop(i)

if len(nazwa1) <= max_dlugosc:
    print("".join(nazwa1))
    quit()

for i in range(len(nazwa1)-1, 0, -1):
    if len(nazwa1) == max_dlugosc:
        break
    if nazwa1[i].isnumeric():
        nazwa1.pop(i)

if len(nazwa1) <= max_dlugosc:
    print("".join(nazwa1))
    quit()

samogloski = ["a", "e", "i", "o", "u", "y"]

index_samogloska = 0
for i in nazwa1:
    if i in samogloski:
        index_samogloska = nazwa1.index(i)
        break

for i in range(len(nazwa1)-1, 0, -1):
    if len(nazwa1) == max_dlugosc:
        break
    if nazwa1[i].lower() in samogloski and i != index_samogloska:
        nazwa1.pop(i)

if len(nazwa1) <= max_dlugosc:
    print("".join(nazwa1))
    quit()

for i in range(len(nazwa1)-2, 0, -1):
    if len(nazwa1) == max_dlugosc:
        break
    nazwa1.pop(i)

print("".join(nazwa1))
