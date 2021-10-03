wejscie = list(input())
suma = 0
for i in range(len(wejscie)):
    if wejscie[i].isnumeric():
        suma += int(wejscie[i]) * 16**i
    else:
        if wejscie[i] == 'A':
            suma += 10*16**i
        elif wejscie[i] == 'B':
            suma += 11*16**i
        elif wejscie[i] == 'C':
            suma += 12*16**i
        elif wejscie[i] == 'D':
            suma += 13*16**i
        elif wejscie[i] == 'E':
            suma += 14*16**i
        elif wejscie[i] == 'F':
            suma += 15*16**i

print(suma)