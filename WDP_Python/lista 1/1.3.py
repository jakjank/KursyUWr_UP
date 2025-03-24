n = int(input('podaj n: '))

line=""
line2=""

for i in range(2*n):
    if(i<n):
        line = line + ' '
    else:
        line = line + '*'

for i in range(n):
    print(line)

for i in range(3*n):
    line2 = line2 + '*'

for i in range(n):
    print(line2)

for i in range(n):
    print(line)
