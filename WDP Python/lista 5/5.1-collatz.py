def F(n):
    if n % 2 == 0:
        return n/2
    else:
        return n*3 + 1

def collatz(n):
    wynik = []
    stop = 1
    while stop>0:
        wynik.append(n)
        n = int(F(n))
        if n == 1:
            wynik.append(n)
            stop = 0
    return wynik

def avg(dlugosci , a , b):
    wynik = 0
    for e in  dlugosci:
        wynik = wynik + e
    wynik = wynik / ((b+1)-a)
    return wynik

def med(dlugosci , a, b):
    dlugosci = sorted(dlugosci)
    if len(dlugosci)%2 == 0:
        wynik = (dlugosci[len(dlugosci)//2] + dlugosci[len(dlugosci)//2 - 1])/2
    else:
        wynik = dlugosci[len(dlugosci)//2]
    return wynik

def analiza_collatza(a , b):
    ciagi = []
    for i in range(a , b+1):
        ciagi.append(collatz(i))
    
    print(ciagi)

    dlugosci = []
    for e in ciagi:
        dlugosci.append(len(e))
    
    srednia = avg(dlugosci , a ,b)
    mediana = med(dlugosci , a , b)
    mini = min(dlugosci)
    maxi = max(dlugosci)
    print('srednia energia wynosi' , srednia)
    print('mediana energii wynosi' , mediana)
    print('najmniejsza energia to' , mini , 'a najwieksza energia wynosi' , maxi)

a = int(input('Podaj a: '))
b = int(input('Podaj b: '))
analiza_collatza(a , b)

        

