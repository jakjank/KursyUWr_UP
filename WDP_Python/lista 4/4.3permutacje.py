import random

def randperm(n):
    zrodlo = []
    bylo = set()
    wynik = []

    for i in range(n):
        zrodlo.append(i)

    for i in  range(n):
        indeks = random.randint(0 , n-1)
        tmp = zrodlo[i]
        zrodlo[i] = zrodlo[indeks]
        zrodlo[indeks] = tmp

    print('done')
    #print(zrodlo)

randperm(10**6)
