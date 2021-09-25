n = input()
ile = 0
wyjscie = 0

for i in range(len(n)):
    if n[i] == 'a':
        wyjscie += 1
    if n[i] == 'b':
        wyjscie += 2
    if n[i] == 'c':
        wyjscie += 3
    if n[i] == 'd':
        wyjscie += 4
    if n[i] == 'e':
        wyjscie += 5
    if n[i] == 'f':
        wyjscie += 6
    if n[i] == 'g':
        wyjscie += 7
    if n[i] == 'h':
        wyjscie += 8
    if n[i] == 'i':
        wyjscie += 9
    if n[i] == 'k':
        wyjscie += 10
    if n[i] == 'l':
        wyjscie += 20
    if n[i] == 'm':
        wyjscie += 30
    if n[i] == 'n':
        wyjscie += 40
    if n[i] == 'o':
        wyjscie += 50
    if n[i] == 'p':
        wyjscie += 60
    if n[i] == 'q':
        wyjscie += 70
    if n[i] == 'r':
        wyjscie += 80
    if n[i] == 's':
        wyjscie += 90
    if n[i] == 't':
        wyjscie += 100
    if n[i] == 'v':
        wyjscie += 200
    if n[i] == 'x':
        wyjscie += 300
    if n[i] == 'y':
        wyjscie += 400
    if n[i] == 'z':
        wyjscie += 500

print(wyjscie)
quit()