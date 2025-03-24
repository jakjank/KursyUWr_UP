from turtle import *
import random

def losowanie_szczytow(t):
    ile = random.randint(2 , 5)
    for i in range(ile):              
        wiersz =random.randint(20,80)
        kolumna = random.randint(20,80)
        tmp = random.choice([3,4,5])
        t[wiersz][kolumna] = tmp
        k =random.randint(2 ,4)
        l = random.randint(2,4)
        for i in range(-k+1,k):
            for j in range(-l+1,l):
                czy = random.choice([True , False])
                if czy:
                    if wiersz+i<100 and kolumna+j<100:
                        t[wiersz+i][kolumna+j]=tmp
    return t
        
def kwadracik(kolor):
    begin_fill()
    color(kolor)
    fillcolor(kolor)
    for i in range(4):
        fd(bok)
        rt(90)
    fd(bok)
    end_fill()

def wysokosc(t , wiersz , kolumna):
    wysokosc = 0
    ile = 1
    for i in range(-1 , 2):
        for j in range(-1 ,2):
            if wiersz+i < 100 and kolumna+j < 100:
                if t[wiersz+i][kolumna+j] > 0:
                    wysokosc = wysokosc + t[wiersz+i][kolumna+j]
                    ile +=1
    return wysokosc/(ile-0.9)

def wartosciowanie(t):
    t = losowanie_szczytow(t)
    for i in range(140_000):
        wiersz =random.randint(0,99)
        kolumna = random.randint(0,99)
        t[wiersz][kolumna] = wysokosc(t , wiersz , kolumna)
    return(t)

def rysuj(t):
    for wiersz in  t:
        for e in wiersz:
            kolor = kolory[min(round(e) , 5)]
            kwadracik(kolor)
        rt(90)
        fd(bok)
        rt(90)
        fd(100*bok)
        rt(180)


bok = 5
kolory = ['green', (0.5, 1, 0) , 'yellow', 'orange', 'red', (0.5, 0,0) ]
n = 100
t = [ [0 for i in range(n)] for j in range(n)]
t = wartosciowanie(t)
tracer(0,0)
penup()
bk(250)
lt(90)
fd(250)
rt(90)
pendown()
rysuj(t)
update()
input()

