
####################################
# Program:  fib.py
####################################

# Fi = (1 1 2 3 5 8 13 21 ...)


def fib(n):
    if n <= 1:
        return 1
    return fib(n-1) + fib(n-2)
    
for i in range(40):
    print (fib(i)) 
    
# F(5) == F(4) + F(3) == (F(3) + F(2)) + (F(2) + F(1))  == (F(3) + F(2)) + (F(2) + F(1))       



#################################################
# kwadrat.py
#################################################
                                 
from turtle import *

BOK = 15
SX = -100
SY = 0

def kwadrat(x, y, kolor):
    fillcolor(kolor)
    pu()
    goto(SX + x * BOK, SY + y * BOK)
    pd()
    begin_fill()
    for i in range(4):
        fd(BOK)
        rt(90)
    end_fill() 

tracer(0,1)
print ('Zmienna __name__ =', __name__)    

if __name__ == '__main__':
    speed('fastest')    
    kolory = ['red', 'green', 'blue']
        
    for i in range(10):
        kwadrat(i,i, kolory[i % 3])    

    
    input()    




####################################
# Program:  perm.py
####################################

# generowanie permutacji: [1,2,3] --> [ [1,2,3], [3,2,1], [1,3,2], ... ]


def perm(L):
    if len(L) == 0:
        return [ [] ]  # a co gdyby: []
    ps = perm(L[1:]) 
    e = L[0]
    return [ p[:i] + [e] + p[i:]  for p in ps for i in range(len(p)+1) ]

# ps = [ (2, 3), (3, 2) ]
# e = 1

print (perm([1,2,3]))
print (len(perm(list(range(7)))))


######################################
#  rev.py
######################################

def rev(L):
    if L == []:
        return []
        
    head = L[0]
    tail = L[1:]
    
    return rev(tail) + [head]
    
print (rev([1,2,3,4]))


######################################
#  studniowka.py
######################################

import random

chłopcy = ['Janek', 'Piotr', 'Adaś', 'Brajan', 'Artur']
dziewczyny = ['Ania', 'Basia', 'Celina', 'Dżessika', 'Ewelina', 'Nikol']
czapeczki = ['melonik', 'beret', 'bejsbolówka', 'kaszkiet']  # brakuje jednej czapki!

def narzednik(x):
    if x[-1] == 'a':
       return x[:-1] + 'ą'
    return x
    
            
random.shuffle(chłopcy)
random.shuffle(dziewczyny)

for c,d,cz in zip(chłopcy, dziewczyny,czapeczki):
    print (f'{c} będzie tańczyć poloneza z {narzednik(d)}, a na głowie {cz}.')



######################################
#  subsets.py
######################################


# Zadanie: obliczyć listę podzbiorów listy różnych elementów L

def subsets(L):
    if len(L) == 0:
        return [set()]
    
    ss = subsets(L[1:])     
    return ss + [{L[0]} | s for s in ss]
    
        
print (subsets([1,2,3]))
print (len(subsets(list(range(10)))))    



####################################
# Program:  wykresy_czasow.py
####################################

import sys
import random
import time
import matplotlib.pyplot as plt

sys.setrecursionlimit(10000)
        
def rev1(L):
    if len(L) == 0:
        return []
    return rev1(L[1:]) + [L[0]]

def rev2(L):
    wynik = []
    for i in range(len(L)):
        wynik.append(L[-i-1])
    return wynik

dane1 = []
dane2 = []
K = 5

for d in range(0, 1000, 3):
    L = list(range(d))
    
    ts = []
    for i in range(5):
        t0 = time.time()
        rev1(L)
        dt = time.time() - t0
        ts.append(dt)
        
    dane1.append( (d, min(ts)) )

    t0 = time.time()
    for i in range(10):
        rev2(L)
    dt = time.time() - t0
    dane2.append( (d, dt) )


    
# tablica ygreków i x-ów z danych

xs1 = [ d[0] for d in dane1]
ys1 = [ d[1] for d in dane1]

xs2 = [ d[0] for d in dane2]
ys2 = [ d[1] for d in dane2]



plt.plot(xs1, ys1, color='blue')
plt.plot(xs2, ys2, color='red')

plt.show()
    
######################################
#  zmienne_lokalne.py
######################################

x = 12
y = 'Jakiś napis'
z = ['Pewna', 'lista']

def f(a, b, c):
    a += 1
    b += '!'
    c = c + ['!']  #inaczej niż c.append('!'), c+= ['!']
    print ('Lokalne', a, b, c)
    
f(x, y, z)
print ('Globalne', x, y, z)    

def g():
    global x
    x = x + 1000

g()    
print ('x=', x)
    


####################################
# Program:  zycie.py
####################################

#wersja ze stopem, jak coś się powtarza

from kwadrat import kwadrat
from turtle import update, clear
import random
import sys
import time


txt = """
......................
......................
..............###.....
......................
......................
..............##......
..............##......
..###.................
....#.................
...#...........##.....
......................
"""

txt = """
......................
...............###....
..............##......
..............##......
......................
...............###....
..............##......
..............##......
......................
......................
......................
....###...............
......#...............
.....#................
......................
......................
..###.................
....#.................
...#...........##.....
......................
"""


tab = [list(wiersz) for wiersz in txt.split()]
tab.reverse()

MY = len(tab)
MX = len(tab[0])

def rysuj_plansze(tab):
    clear()
    for y in range(MY):
        for x in range(MX):
            if tab[y][x] == '#':
                kolor = 'green'
            else:
                kolor = 'lightgreen'
            kwadrat(x, y, kolor)
            
            
    update() 
    
rysuj_plansze(tab)


KIERUNKI = [ (1,0), (0,1), (-1, 0), (0, -1), (1,1), (-1,1), (1,-1), (-1,-1)]

def liczba_sasiadow(x, y):
    ls = 0  
    for dx, dy in KIERUNKI:
        nx = (x + dx) % MX
        ny = (y + dy) % MY
        if tab[ny][nx] == '#':
            ls += 1
    return ls
   
def pusta_plansza():
    return [ MX * ['.']  for y in range(MY)]
            
# reguły gry w życie:
# jeżeli komórka pełna ma 2 lub 3 sąsiadów przeżywa, wpp ginie
# jeżeli komórka pusta ma 3 sąsiadów, to rodzi się nowa
#
#

historia = set()

while True:
    
    
    rysuj_plansze(tab)
    
    r = tuple(tuple(wiersz) for wiersz in tab)
    r = str(tab) # też dobra opcja, jak poprzednie
    if r in historia:
        print ('Powtórzony stan!')
        break
        
    historia.add(r)
        
    nowa = pusta_plansza()
    
    for x in range(MX):
        for y in range(MY):
            ls = liczba_sasiadow(x, y)
            if tab[y][x] == '.' and ls == 3:
                nowa[y][x] = '#'
            if tab[y][x] == '#' and ls in [2,3]:
                nowa[y][x] = '#'
    
    if tab == nowa:
        break                
    tab = nowa 
    
     
    time.sleep(0.03)         
    
print ('Koniec')
input()
