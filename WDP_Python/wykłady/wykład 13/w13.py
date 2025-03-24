######################################
#  complex.py
######################################

# liczby zespolone: magic methods == dunder methods
# 

class Complex:
    def __init__(self, re, im):
        self.re = re
        self.im = im
        
    def __str__(self):
        return f'({self.re}+{self.im}i)'
        
    def __add__(self, other):
        if type(other) == float or type(other) == int:
            other = Complex(other, 0)
        return Complex(self.re + other.re, self.im + other.im)
    
    def __radd__(self, other):
        return self + other
    
    def __rmul__(self, other):
        return self * other
                
    def __mul__(self, other):
        re_part = self.re * other.re - self.im * other.im
        im_part = self.re * other.im + self.im * other.re
        
        return Complex(re_part, im_part)
        
c1 = Complex(2,0)
c2 = Complex(0,1)

print (c1, c2, c1+c2, c1*c2, c2+20, 20+c2)  
print (c1 * c2 + c1 * (c1+c1*c2))      
        
        
######################################
#  float1.py
######################################

# kiedy x + 1 == x?

x = 1.0

for i in range(40):
    if x == x + 1:
        print ('Stało się', i)
    else:
        print ('Wszystko zgodnie z przypuszczeniami.', i)
    x *= 10.0    
    
    
    
######################################
#  float2.py
######################################

import math

# Kiedy 1/(n!) == 0

n = 0
while (x := 1/math.factorial(n)) != 0:
    print (x)
    n += 1
    
print ('Pod koniec x=', x)    



######################################
#  search.py
######################################

from turtle import *
import random
from collections import defaultdict as dd

D = 45
R = 6

tracer(0,1)            


def points(K):
    res = set()
    for i in range(K):
        x = random.randint(-300, 300)
        y = random.randint(-200, 200)
        res.add( (x, y) )
        
    return list(res)
       
def my_circle(x, y, r, c):
    pu()
    goto(x, y - r)
    pd()
    fillcolor(c)
    begin_fill()
    circle(r)
    end_fill()
    
def draw_points(G, color):
    for x,y in G:
        my_circle(x, y, R, color)
    update()    

def dist(a, b):
    xa, ya = a
    xb, yb = b
    return ((xa-xb) ** 2 + (ya-yb) ** 2) ** 0.5
    
THR = 40
THR = 34

    
def make_graph(ps):
    G = dd(list)
    for a in ps:
        for b in ps:
            if a != b and dist(a, b) < THR:
                 G[a].append(b)   
    return G
    
    
def draw_graph(G, color):
    for a in G:
        for b in G[a]:
            pu()
            goto(*a)
            pd()
            goto(*b)
    draw_points(G, color)        
    update()   
    
def show_path(start, end, path):
    pu()
    
    goto(*start)
    pencolor('orange')
    pensize(2)
    pd()
    for p in path:
        goto(*p)
    pensize(1)
    my_circle(*start, R + 3, 'blue')
    my_circle(*end, R + 3, 'blue')

    update()      


def random_walk(G, a, b):
    path = [a]
    while path[-1] != b:
        n = random.choice(G[path[-1]])
        path.append(n)
    return path
    

def dfs(G, a, b):
    visited = set()
    def dfs0(a):
        if a == b:
            return [a]
        if a not in G or len(G[a]) == 0:
            return []
        if a in visited:
            return []    
        
        visited.add(a)        
        for n in G[a]:
            path = dfs0(n)
            if path:
                return [a] + path         
        return []
    return dfs0(a)    
    
    
villages = points(300)
G = make_graph(villages)
draw_graph(G, 'gray')

start = random.choice(villages)
end   = random.choice(villages)

#path = random_walk(G, start, end)

path = dfs(G, start, end)
show_path(start, end, path)
 
input()
