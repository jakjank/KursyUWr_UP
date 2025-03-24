from collections import defaultdict as dd
from itertools import permutations

def przypisz(slownik , wart):
    for e , i in zip(slownik , range(len(wart))):
        slownik[e] = wart[i]
    return slownik

def oblicz(slownik , napis):
    wynik = 0
    for litera in napis:
        wynik = wynik*10 + slownik[litera]
    return wynik

def sprawdz(slownik):
    if oblicz(slownik , A) + oblicz(slownik , B) == oblicz(slownik , C):
        return True
    return False

def zagadka():
    wynik = dd(int)
    for e in A:
        wynik[e] = 0
    for e in B:
        wynik[e] = 0
    for e in C:
        wynik[e] = 0
    
    wartosciowania = permutations([1,2,3,4,5,6,7,8,9,0] , len(wynik))

    for wart in list(wartosciowania):
        wynik = przypisz(wynik , wart)
        if sprawdz(wynik):
            return wynik

    return 'brak rozwiazan'


A = input('podaj pierwsze slowo: ')
B = input('podaj drugie slowo: ')
C = input('podaj trzecie slowo: ')
print(zagadka())