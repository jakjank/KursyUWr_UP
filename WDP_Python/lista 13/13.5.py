#ostatnie zadanie (5) z kolokwium z 2016

def jednaWartosc(L):
    return all([L[i-1] == L[i] for i in range(1 , len(L))])

def najwiekszaRoznica(L):
    return sorted([abs(L[i-1]-L[i]) for i in range(1 , len(L))])[-1]

def silnia(n): #???
    x = 1
    i = 1
    while i < n:
        x = x*i
        i += 1
    return x 

def sumaPodzielnychKwadratow(n , k):
    return sum([x**2 for x in range(1 , n) if x**2 % k == 0])

def ukladalne(S):
    return {a+b for a in S for b in S if a+b in S and a!= b}

def posortowaneLeksykograficznie(L):
    return [int(x) for x in sorted([str(e) for e in L])]



