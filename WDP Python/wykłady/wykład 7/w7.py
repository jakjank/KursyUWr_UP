######################################
#  perm.py
######################################

import random
import math

zliczanie = {}

    
def permutacja(L):
    L = L[:]
    random.shuffle(L)
    return tuple(L)

def permutacja(L):
    L = L[:]
    for n in range(2*len(L)):
        i = random.randint(0, len(L)-1)
        j = random.randint(0, len(L)-1)
        L[i], L[j] = L[j], L[i]
    return tuple(L)

        
    
N = 4    
liczba_eksperymentow = 100_000
oczekiwana_wartosc = liczba_eksperymentow / math.factorial(N)

oryginal = list(range(N))    


for i in range(liczba_eksperymentow):
    p = permutacja(oryginal)
    if p not in zliczanie:
        zliczanie[p] = 0
    zliczanie[p] += 1

for p in sorted(zliczanie, key=zliczanie.get, reverse=True):
    print (p, zliczanie[p]/oczekiwana_wartosc)

"""
for i in range(10):
    print (permutacja(oryginal))    
"""


####################################
# Program:  pol_ang.py [2]
# wersja z wieloma tłumaczEniami
###################################
import random

pol_ang = {}

for x in open('pol_ang.txt'):
    x = x.strip()
    L = x.split('=')
    if len(L) != 2:
        continue
    pol, ang = L
    if pol not in pol_ang:
        pol_ang[pol] = []
    pol_ang[pol].append(ang)

    
def tlumacz(polskie):
    wynik = []
    for p in polskie:
        if p in pol_ang:
            wynik.append(random.choice(pol_ang[p]))
        else:
            wynik.append('[*]')
    return ' '.join(wynik)        
    
zdanie = 'chłopiec z dziewczyna pójść do kino'.split()
zdanie = 'wykład z programowanie
for i in range(10):
    print (tlumacz(zdanie))  


####################################
# Program:  pol_ang.py [3]
# wersja z wieloma tłumaczeniami i słownikiem domyślnym
###################################

import random
from collections import defaultdict as dd

pol_ang = dd(list)

for x in open('pol_ang.txt'):
    x = x.strip()
    L = x.split('=')
    if len(L) != 2:
        continue
    pol, ang = L
    pol_ang[pol].append(ang)

    
def tlumacz(polskie):
    wynik = []
    for p in polskie:
        if p in pol_ang:
            wynik.append(random.choice(pol_ang[p]))
        else:
            wynik.append('[*]')
    return ' '.join(wynik)        
    
zdanie = 'chłopiec z dziewczyna pójść do kino'.split()
zdanie = 'wykład z programowanie znaczyć dużo dla student'.split()
for i in range(10):
    print (tlumacz(zdanie))  


####################################
# Program:  pol_ang.py
####################################

pol_ang = {}

for x in open('pol_ang.txt'):
    x = x.strip()
    L = x.split('=')
    if len(L) != 2:
        continue
    pol, ang = L
    pol_ang[pol] = ang

    
def tlumacz(polskie):
    wynik = []
    for p in polskie:
        if p in pol_ang:
            wynik.append(pol_ang[p])
        else:
            wynik.append('[*]')
    return ' '.join(wynik)        
    
zdanie = 'chłopiec z dziewczyna pójść do kino'.split()

print (tlumacz(zdanie))  


####################################
# Program:  pol_ang.py [3]
# wersja z wieloma tłumaczeniami i słownikiem domyślnym (ZŁY!)
###################################
import random
from collections import defaultdict as dd

pusta_lista = []

pol_ang = dd(lambda : pusta_lista)   # list    lambda:[]   

for x in open('pol_ang.txt'):
    x = x.strip()
    L = x.split('=')
    if len(L) != 2:
        continue
    pol, ang = L
    pol_ang[pol].append(ang)

    
def tlumacz(polskie):
    wynik = []
    for p in polskie:
        if p in pol_ang:
            wynik.append(random.choice(pol_ang[p]))
        else:
            wynik.append('[*]')
    return ' '.join(wynik)        
    
zdanie = 'chłopiec z dziewczyna pójść do kino'.split()

for i in range(10):
    print (tlumacz(zdanie))  
    
    

####################################
# Program:  wyjatki.py
####################################

import random

try:
    for i in range(10):
        x = random.randint(0, 10)
        print (f'1 / {x} == {1/x}')
except ZeroDivisionError:
    print ('Zdażyło się dzielenie przez zero, ojej')
    
    
print()

for i in range(10):
    x = random.randint(1, 10)
    try:
        print (f'1 / {x} == {1/xyz}')
    except:
        print('Dzielenie przez zero?')  # jednak nie zawsze!
        
print()
          
for i in range(10):
    x = random.randint(1, 10)
    try:
        print (f'1 / {x} == {1/xyz}')
    except ZeroDivisionError:
        print('Dzielenie przez zero?')
    except NameError:
        print ('Zła nazwa')       



####################################
# Program:  wykresy.py
####################################

import math
from turtle import *

speed('fastest')
    
SX = -200
D = 2
A, B = -10, 10
N = 200

def tworz_wykres(f, a, b):
    g = []
    
    delta = (b-a) / N
    for i in range(N+1):
        x = a + i * delta
        g.append( eval(f, {'x' : x, 'sin' : math.sin, 'cos' : math.cos}))
    return g    
        
    
def rysuj_wykres(g, skala, kolor):
    pu()
    goto(SX, skala * g[0])
    pd()
    pencolor(kolor)
    pensize(2)
    
    x = SX + D
    
    for y in g[1:]:
        goto(x, skala * y)
        x += D    
    
for wiersz in open('wykresy.txt'):
    L = wiersz.split()  
    if len(L) < 2:
        continue
    if '#' in L[0]:
        continue
        
    kolor = L[0]
    wzor = ' '.join(L[1:])
    try:
        rysuj_wykres(tworz_wykres(wzor, A, B), 40, kolor)
    except:
        print ('Jakis problem z', L)         
    
input()      


######################################
#  wykresy.txt
######################################
# Format: kolor wzór (f(x))
green    sin(x) + 0.1 * x
orange   0.3 * x * cos(x) - 0.01 * x**2
red      cos(x) ** 2 + sin(x) ** 3
pink    0.1 * x 
yellow  jakas_bzdura
blue  sin(0.1 * x * x) + 0.1 * x


