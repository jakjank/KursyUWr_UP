def suma_podzbiorow(L):
    def sumuj(z):
        wynik = 0
        for e in z:
            wynik = wynik+e
        return(wynik)
    
    if len(L) == 1:
        return [L[0]]

    tmp = [sumuj(L[0:i]) for i in range(1, len(L)+1)] + ([L[0]+e for e in L[1:]]) + (suma_podzbiorow(L[1:]))

    return tmp


z = [1,2,3,100]
print(set(suma_podzbiorow(z)))  #wypisuje z powtorzeniami
'''
def podciagi_malejace(A,B,N):
    if N == 0:
        return[[]]
    t = [x for x in range(A,B+1)]
    tmp = podciagi_malejace(A,B,N-1)
    print(tmp)

    return [[e] + tmp for e in t]

def perm(L):
    if len(L) == 0:
        return [ [] ]  # a co gdyby: []
    ps = perm(L[1:]) 
    e = L[0]
    return [ p[:i] + [e] + p[i:] for p in ps for i in range(len(p)+1) ] 

#print(perm([1,2,3]))

(podciagi_malejace(3,5,3))
'''