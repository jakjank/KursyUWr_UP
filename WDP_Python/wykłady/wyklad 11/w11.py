######################################
#  animowana_rozeta.py
######################################

####################################
# Program:  animacja.py
####################################

from turtle import *
import time

tracer(0,0)
FRAME_RATE = 1/30

pensize(3)

def kwadrat(bok):
    for i in range(4):
        fd(bok)
        rt(90)

def rozeta(N, kat):
    for i in range(N): 
        fd(70)
        rt(kat)
        kwadrat(30)
        lt(kat)
        bk(70)
        rt(360 / N)


D1 = 5
D2 = 6
kat = 0

while True:
    t0 = time.time()
    clear()
    rozeta(10, kat)
    kat += D2
    rt(D1)
    update()
    delta = time.time() - t0
    if delta < FRAME_RATE:
        time.sleep(FRAME_RATE - delta)
        
#time.sleep(seconds)

input()
######################################
#  hash_demo.py
######################################

import random

litery = 'abcdefghijklmnopqrstuvwzyz'

def napis():
    wynik = []
    while True:
        if random.randint(0,30) == 0:
            return ''.join(wynik)
        wynik.append(random.choice(litery))


slowa = set()

while len(slowa) < 10000:
    slowa.add(napis())
            
print (len(slowa)) 

czestosci = 100 * [0]

for s in slowa:
    h = hash(s) % 100
    czestosci[h] += 1
    
print (czestosci)       
   
######################################
#  jedynka.py
######################################

EPSILON = 0.000000000001

def jedynka(N):
    s = 0.0
    for i in range(N):
        s += 1/N
    return s
    
for i in range(1,65):
    print (i, jedynka(i)==1, abs(jedynka(i) - 1) < EPSILON)
######################################
#  nasz_zbior.py
######################################

def in_tree(tree, e):
    if tree == []:
        return False
    n, left, right = tree
    if n == e:
        return True
    if e < n:
        return in_tree(left, e)
    return in_tree(right, e)

def tree_to_list(tree):
    if tree == []:
        return []
    n, left, right = tree
    return tree_to_list(left) + [n] + tree_to_list(right)

def add_to_tree(e, tree):
    if tree == []:
        tree += [e, [], []]
        return
    x, left, right = tree
    if e < x:
        add_to_tree(e, left)
    elif e > x:
        add_to_tree(e, right)
       


#############################################################
#TODO: contains, or, str, 


class Set:
    def __init__(self, *elems):
        self.tree = []
        for e in elems:
            self.add(e)
            
    def add(self, e):
        add_to_tree(e, self.tree)    
        
    def __contains__(self, e):
        return in_tree(self.tree, e) 
        
    def __str__(self):
        return f'Set({tree_to_list(self.tree)})'    
        
    def __or__(self, other):
        new = Set(*tree_to_list(self.tree))
        for e in tree_to_list(other.tree):
            new.add(e)
        return new    
        
zbior = Set(1,4,5,3,3,5,1,1,1,8) 

print(zbior)

for i in range(7):
    print (i, i in zbior)       
        
print (Set(1,2,3,4,4,4) | Set(3,44,4,4,5))

######################################
#  oneliners.py
######################################

#TODO: silnia, is_prime, functools.reduce, any, all
######################################
#  osoby.py
######################################

#to define: init, str, repr, hash, eq

class Osoba:
    def __init__(self, im, naz, w):
        self.imie = im
        self.nazwisko = naz
        self.wiek = w  
        
    def plynie_czas(self):
        self.wiek += 1      
        
    def __str__(self):
        return f'osoba({self.imie}, {self.nazwisko})'  
        
    def __repr__(self):
        return f'Osoba("{self.imie}", "{self.nazwisko}", {self.wiek})'  
        
    def __hash__(self):
        return hash(  (self.imie, self.nazwisko, self.wiek) )
        
    def __eq__(self, other):
        return self.imie == other.imie and self.nazwisko == other.nazwisko and self.wiek == other.wiek       
                   
 
        
janek = Osoba('Jan', 'Kowalski', 34)
ala = Osoba('Alicja', 'Nowak', 22)
basia = Osoba('Barbara', 'Pisarska', 12)    

osoby = [janek, ala, basia]

print ('Raport 1')
for o in osoby:
    print (o.imie, o.nazwisko, 'ma', o.wiek, 'lat')
print ()    

for o in osoby:
    o.plynie_czas()
    
print ('Raport 2')
for o in osoby:
    print (o, o.__str__())
print ()   

print (osoby) 

dziewczyny = {ala, basia}
dziewczyny.add(Osoba('Celina', 'Nowak', 20))

print (dziewczyny, ala in dziewczyny)
print (len({Osoba('Alicja', 'Nowak', 22), ala}))


