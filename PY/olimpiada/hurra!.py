for i in range(1, int(input())+1):
    if i % 7 == 0:
        if i % 11 == 0:
            print("Wiwat!")
        else:
            print("Hurra!")
    elif i % 11 == 0:
        print("Super!")
    else:
        print(i)
