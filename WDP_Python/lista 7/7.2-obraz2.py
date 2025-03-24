from turtle import *
import random

kolory = open("lista 7\kolory.txt" ).readlines()

def kwadracik(kolor):
    begin_fill()
    fillcolor(kolor)
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()

def do_kwadracika(w , k):
    penup()
    rt(90)
    fd(w*bok)
    lt(90)
    fd(k*bok)
    pendown()

def od_kwadracika(w , k):
     penup()
     bk(k*bok)
     lt(90)
     fd(w*bok)
     rt(90)
     pendown()


def rysuj(kolory2):
    bylo = set()
    while(len(bylo)<len(kolory2)):
        ktory = random.randint(0 , len(kolory2))
        wiersz = ktory//dl_wiersza
        kolumna = ktory%dl_wiersza
        do_kwadracika(wiersz , kolumna)
        kwadracik(kolory2[ktory])
        od_kwadracika(wiersz , kolumna)


lista = []
bok = 7
dl_wiersza = len(kolory[0].split(' '))
penup()
goto(-200,200)
pendown()

tmp2 = []
kolory2 = []
for wiersz in kolory:
    wiersz_kolorow = wiersz.split(' ')
    for kolor in wiersz_kolorow:
        tmp = eval(kolor)
        for i in tmp:
            i = i/256
            tmp2.append(i)
        kolory2.append(tmp2)
        tmp2 = []

#print(kolory2)
print(len(kolory2))
print(dl_wiersza)
speed('fastest')
rysuj(kolory2)
input()

