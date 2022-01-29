import sys

lines = []
program = sys.stdin.read()  # kliknac ctrl + d aby zatrzymac input

wyjscie = ""

trojznaki = ["=", "/", "'", "(", ")", "!", "<", ">", "-"]
trojznaki_def = ["#", "\\", "^", "[", "]", "|", "{", "}", "~"]

czy = False
czy_ile = 2
for i in range(len(program)):
    if czy and czy_ile != 0:
        czy_ile -= 1
        continue
    if program[i] == "?" and program[i+1] == "?" and program[i+2] in trojznaki:
        wyjscie += trojznaki_def[trojznaki.index(program[i+2])]
        czy = True
        czy_ile = 2
    else:
        wyjscie += program[i]

print(wyjscie)

