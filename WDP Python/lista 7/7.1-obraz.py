from turtle import *


kolory = open("lista 7\kolory.txt" ).readlines()

def kwadracik(bok , kolor):
    begin_fill()
    fillcolor(kolor)
    for i in range(4):
        fd(bok)
        rt(90)
    fd(bok)
    end_fill()

lista = []
bok = 7
penup()
goto(-200,200)
pendown()

tracer(0,1)
for wiersz in kolory:
    lista_kolorow = wiersz.split(' ')
    for kolor in lista_kolorow:
        tmp = eval(kolor)
        for i in tmp:
            i = i/256
            lista.append(i)
        kwadracik(bok , lista)
        lista = []
    rt(90)
    fd(bok)
    rt(90)
    fd(len(lista_kolorow) * bok)
    rt(180)
update()
input()