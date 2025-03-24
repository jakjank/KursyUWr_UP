import sys

def pierwsza(n):
    if n%2 == 0:
        return False
    i = 3
    while i*i <= n:
        if n % i == 0:
            return False
        i = i + 2
    return True

n = int(input("ile cyfr maja miec sprawdzane liczby: "))
k = int(input("ile '7' pod rzad maja miec sprawdzane liczby: "))

if k>n:
    print("głupiś...")
    sys.exit(0)

t = k*'7'
cobylo = []             #lepiej na zbior  cobylo = set()

for i in range(10**(n-k)):
    if k + len(str(i)) == n and i != 0:
        t = k*'7'
        t = str(i) + t
        if (t in cobylo) == False:
            if pierwsza(int(t)):
                cobylo.append(t)
                #print(t)
    else:
        for j in range(10**(n-k)):
            t = k*'7'
            if i == 0:
                t = t + (abs(n-k-len(str(j))))*'0' + str(j)
            else:
                t = str(i) + t + (abs(n-k-len(str(i))-len(str(j))))*'0' + str(j)
            if len(t) == n:
                if (t in cobylo) == False:
                    if pierwsza(int(t)):
                        cobylo.append(t)
                        #print(t)

print(len(cobylo))