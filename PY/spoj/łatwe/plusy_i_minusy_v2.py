class Stack:
    def __init__(self):
        self.stack = list()

    def isEmpty(self):
        return len(self.stack) <= 0

    def oproznij(self):
        self.stack = list()

    def __len__(self):
        return len(self.stack)

    def push(self, item):
        self.stack.append(item)

    def pop(self):
        if self.isEmpty():
            return None
        else:
            return self.stack.pop()

    def peek(self):
        if self.isEmpty():
            return None
        else:
            return self.stack[len(self.stack) - 1]

    def __str__(self):
        return str(self.stack)


def main():
    plusy_i_minusy = list(input())
    stos = Stack()
    out = []

    for i in plusy_i_minusy:
        if i == "+":
            if stos.peek() == "-":
                stos.pop()
            else:
                stos.push("+")
        else:
            if stos.peek() == "+":
                stos.pop()
            else:
                stos.push("-")

        if len(stos) == 3:
            if stos.peek() == "+":
                out.append(5)
            else:
                out.append(1)
            stos.oproznij()

    if len(out) == 0:
        print("BRAK")
    else:
        print(*out)


main()
