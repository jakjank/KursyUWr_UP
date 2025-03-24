from turtle import *
import random

kolory = [ 'orange', 'red', 'green', 'lightgreen', 'cyan', 'blue', 'yellow', 'brown' ]
skret = [1 , 0]

def kwadracik(bok):
    begin_fill()
    fillcolor(random.choice(kolory))
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()
    fd(bok)

def trojkacik(bok):
    begin_fill()
    fillcolor(random.choice(kolory))
    rt(30)
    for i in range(3):
        fd(bok)
        rt(120)
    end_fill()
    fd(bok)
    rt(30)


def kawalek(bok):
    kwadracik(bok)
    trojkacik(bok)
    if random.choice(skret) == 1:
        lt(210)
        fd(bok)
        rt(90)
    kwadracik(bok)
    trojkacik(bok)


bok = 15

for i in range(50):
    speed('fastest')
    kawalek(bok)

z = input()