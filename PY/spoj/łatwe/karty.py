jasio = list(input())
stasio = list(input())

jasio_wynik = 0
for i in jasio:
    if i.isnumeric():
        jasio_wynik += int(i)
    elif i == "T":
        jasio_wynik += 10
    elif i == "J":
        jasio_wynik += 11
    elif i == "Q":
        jasio_wynik += 12
    elif i == "K":
        jasio_wynik += 13
    elif i == "A":
        jasio_wynik += 14


stasio_wynik = 0
for i in stasio:
    if i.isnumeric():
        stasio_wynik += int(i)
    elif i == "T":
        stasio_wynik += 10
    elif i == "J":
        stasio_wynik += 11
    elif i == "Q":
        stasio_wynik += 12
    elif i == "K":
        stasio_wynik += 13
    elif i == "A":
        stasio_wynik += 14


if jasio_wynik > stasio_wynik:
    print("JASIO")
elif stasio_wynik > jasio_wynik:
    print("STASIO")
else:
    print("REMIS")
