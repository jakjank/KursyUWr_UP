from duze_cyfry import daj_cyfre
from turtle import *
import random

def move(x,y):
    penup()
    fd(x)
    lt(90)
    fd(y)
    rt(90)
    pendown()

def kwadracik(bok , kolor):
    color(kolor)
    begin_fill()
    fillcolor(kolor)
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()
        
def rysuj(bok , wzor):
    kolor1 = [1,1,1]
    kolor2 = [random.random(),random.random(),random.random(),]
    for i in range(5):
        for j in  range(5):
            if wzor[i][j] == '#':
                kwadracik(bok , kolor2)
                fd(bok)
            else:
                kwadracik(bok , kolor1)
                fd(bok)
        move(-5*bok , -bok)

def przejscie(bok):
    kolor = [1,1,1]
    move(5*bok,bok)
    for i in range(4):
        kwadracik(bok , kolor)
        move(0,bok)
    kwadracik(bok , kolor)
    fd(bok)

n = str(input("Podaj liczbe do wypisania: "))
bok = 20
move(-350 , 50)
t=[]
speed('fastest')

for i in range(len(n)):
    if n[i] in ['0','1','2','3','4','5','6','7','8','9']:
        t.append(daj_cyfre(int(n[i])))
    else:
        t.append(daj_cyfre(10))

przejscie(bok)
for i in range(len(t)):
    rysuj(bok , t[i])
    przejscie(bok)

input()
