from collections import defaultdict as dd
from itertools import permutations
import random

cyfry = [1,2,3,4,5,6,7,8,9,0]

def perm_post1(s):
    slownik = dd(int)
    for litera in s:
        slownik[litera] = 0
    wartosciowanie = permutations(cyfry, len(slownik))
    wart = []
    for e in wartosciowanie:
        wart.append(e)
    uzywamy = wart[random.randint(0,len(wart)-1)]
    for litera,liczba in zip(slownik,uzywamy):
        slownik[litera]=liczba
    
    wynik = ''
    for litera in s:
        wynik = wynik + f'{slownik[litera]}-'

    return wynik

def perm_post2(s):
    wynik = ''
    for litera in s:
        wynik = wynik + f'{cyfry[random.randint(0,9)]}-'
    return(wynik)

print(perm_post1('indianin'))