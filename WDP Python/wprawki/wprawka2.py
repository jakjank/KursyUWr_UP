from turtle import *

colors = {
   'r' : 'red', 
   'g' : 'green', 
   'b' : 'blue',
   'y' : 'yellow',
   'o' : 'orange', 
}

BOK = 35

dane_o_rysunku = ['bobby' + 'bobby'+ 'bobby', 'rybogryby', 'grrrrrry', 'yo' * 10] * 2

def kwadracik(BOK , kolor):
    pendown()
    begin_fill()
    fillcolor(colors[kolor])
    for i in range(4):
        fd(BOK)
        rt(90)
    end_fill()
    penup()

def obrazek(kolory):
    for i in range(len(kolory)):
        rt(i*(360/len(kolory)))
        fd(50)
        kwadracik(BOK , kolory[i])
        fd(-50)
        lt(i*(360/len(kolory)))



def rysuj(dane_o_rysunku):
    for i in range(len(dane_o_rysunku)):
        penup()
        rt(i*(360/len(dane_o_rysunku)))
        fd(250)
        obrazek(dane_o_rysunku[i])
        fd(-250)
        lt(i*(360/len(dane_o_rysunku)))

tracer(0,0)
rysuj(dane_o_rysunku)
update()
input()
